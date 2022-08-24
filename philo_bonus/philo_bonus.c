/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/23 15:02:50 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	sem_wait(philo->info->check_death);
	dead = philo->info->is_dead;
	sem_post(philo->info->check_death);
	if (dead)
		exit(0);
	else if (philo->info->t_die < get_time() - philo->t_last_eat)
	{
		prints(philo->info, get_time() - philo->info->t_start, philo->id, DIE);
		sem_wait(philo->info->check_death);
		philo->info->is_dead = 1;
		sem_post(philo->info->check_death);
		exit(0);
	}
	return (0);
}

int	philo_eat(t_info *info, t_philo *philo)
{
	if (is_dead(philo))
		exit(0);
	sem_wait(info->fork);
	prints(info, get_time() - info->t_start, philo->id, FORK);
	if (info->n_philo == 1)
	{
		sem_post(info->fork);
		psleep(info->t_die);
		prints(info, get_time() - info->t_start, philo->id, DIE);
		exit(0);
	}
	sem_wait(info->fork);
	prints(info, get_time() - info->t_start, philo->id, FORK);
	prints(info, get_time() - info->t_start, philo->id, EAT);
	philo->t_last_eat = get_time();
	philo->n_eat += 1;
	psleep(info->t_eat);
	sem_post(info->fork);
	sem_post(info->fork);
	return (0);
}

void	*philo_act(void *philo)
{
	t_philo	*tmp_philo;
	t_info	*tmp_info;
	int		dead;

	tmp_philo = philo;
	tmp_info = tmp_philo->info;
	if (tmp_philo->id % 2 == 1)
		usleep(100);
	dead = 0;
	while (1)
	{
		sem_wait(tmp_info->check_death);
		dead = tmp_info->is_dead;
		sem_post(tmp_info->check_death);
		if (dead)
			break ;
		if (tmp_philo->n_eat == tmp_philo->info->n_must_eat)
			break ;
		if (philo_eat(tmp_info, tmp_philo))
			break ;
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, SLEEP);
		psleep(tmp_info->t_sleep);
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, THINK);
	}
	exit(0);
}

int	philo_start(t_philo *philo)
{
	pthread_t	thread;
	
	philo->t_last_eat = get_time();
	if (pthread_create(&thread, 0, philo_act, philo))
		return (1);
	pthread_join(thread, 0);
	exit(0);
}
