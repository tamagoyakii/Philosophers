/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/18 15:01:26 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->info->is_dead)
		return (1);
	else if (philo->info->t_die < get_time() - philo->t_last_eat)
	{
		prints(philo->info, get_time() - philo->info->t_start, philo->id, DIE);
		philo->info->is_dead = 1;
		return (1);
	}
	return (0);
}

void	psleep(long long t_sleep)
{
	long long	t_start;
	long long	t_now;

	t_start = get_time();
	while (1)
	{
		t_now = get_time();
		if (t_now - t_start >= t_sleep)
			break ;
		usleep(100);
	}
}

int	philo_eat(t_info *info, t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&info->fork[philo->left]);
	prints(info, get_time() - info->t_start, philo->id, FORK);
	pthread_mutex_lock(&info->fork[philo->right]);
	prints(info, get_time() - info->t_start, philo->id, FORK);
	prints(info, get_time() - info->t_start, philo->id, EAT);
	philo->t_last_eat = get_time();
	philo->n_eat += 1;
	psleep(info->t_eat);
	pthread_mutex_unlock(&(info->fork[philo->right]));
	pthread_mutex_unlock(&(info->fork[philo->left]));
	return (0);
}

void	*philo_act(void *philo)
{
	t_philo	*tmp_philo;
	t_info	*tmp_info;

	tmp_philo = philo;
	tmp_info = tmp_philo->info;
	if (tmp_philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		if (tmp_philo->n_eat == tmp_philo->info->n_must_eat)
			break ;
		if (philo_eat(tmp_info, tmp_philo))
			break ;
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, SLEEP);
		psleep(tmp_info->t_sleep);
		if (is_dead(tmp_philo))
			break ;
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, THINK);
	}
	return (0);
}

int	philo_start(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		philo[i].t_last_eat = get_time();
		if (pthread_create(&philo[i].thread, 0, philo_act, &philo[i]))
			return (1);
	}
	i = -1;
	while (++i < info->n_philo)
		pthread_join(philo[i].thread, 0);
	pthread_mutex_destroy(&(info->print));
	i = -1;
	while (++i < info->n_philo)
		pthread_mutex_destroy(&(info->fork[i]));
	free(info->fork);
	free(philo);
	return (0);
}
