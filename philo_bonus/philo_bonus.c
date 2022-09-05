/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/05 17:02:28 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (1)
	{
		sem_wait(info->check);
		if (get_time() - philo->t_last_eat >= info->t_die)
		{
			prints(info, philo->id, DIE);
			sem_wait(info->print);
			exit(DIE);
		}
		sem_post(info->check);
		usleep(100);
	}
}

int	philo_eat(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	prints(info, philo->id, FORK);
	sem_wait(info->fork);
	prints(info, philo->id, FORK);
	prints(info, philo->id, EAT);
	sem_wait(info->check);
	philo->t_last_eat = get_time();
	sem_post(info->check);
	philo->n_eat += 1;
	psleep(info->t_eat);
	sem_post(info->fork);
	sem_post(info->fork);
	if (philo->n_eat == info->n_must_eat)
		return (1);
	return (0);
}

void	philo_act(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		if (philo_eat(info, philo))
			break ;
		prints(info, philo->id, SLEEP);
		psleep(info->t_sleep);
		prints(info, philo->id, THINK);
	}
	exit(FULL);
}

void	philo_start(t_philo *philo)
{
	pthread_t	thread;
	
	philo->t_last_eat = get_time();
	pthread_create(&thread, 0, &check_death, philo);
	pthread_detach(thread);
	philo_act(philo);
}
