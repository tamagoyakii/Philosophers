/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/28 17:20:13 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	morintoring(t_info *info, t_philo **philo)
{
	int	n_full_philo;
	int	i;

	i = -1;
	while (1)
	{
		if (++i >= info->n_philo)
			i = 0;
		pthread_mutex_lock(&(info->check_full));
		n_full_philo = info->n_full_philo;
		pthread_mutex_unlock(&(info->check_full));
		if (n_full_philo == info->n_philo)
			break ;
		if (is_dead(info, &(*philo)[i]))
			break ;
	}
}

int	is_dead(t_info *info, t_philo *philo)
{
	long long	now;
	int			dead;

	dead = 0;
	now = get_time();
	pthread_mutex_lock(&(info->check_last_eat));
	if (info->t_die < now - philo->t_last_eat)
	{
		prints(info, philo->id, DIE);
		pthread_mutex_lock(&(info->check_death));
		info->is_dead = 1;
		pthread_mutex_unlock(&(info->check_death));
		dead = 1;
	}	
	pthread_mutex_unlock(&(info->check_last_eat));
	return (dead);
}

void	philo_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->fork[philo->left]);
	prints(info, philo->id, FORK);
	pthread_mutex_lock(&info->fork[philo->right]);
	prints(info, philo->id, FORK);
	prints(info, philo->id, EAT);
	pthread_mutex_lock(&info->check_last_eat);
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&info->check_last_eat);
	philo->n_eat += 1;
	psleep(info->t_eat);
	pthread_mutex_unlock(&(info->fork[philo->right]));
	pthread_mutex_unlock(&(info->fork[philo->left]));
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		philo_eat(info, philo);
		if (philo->n_eat == info->n_must_eat)
		{
			pthread_mutex_lock(&(info->check_full));
			info->n_full_philo += 1;
			pthread_mutex_unlock(&(info->check_full));
		}
		prints(info, philo->id, SLEEP);
		psleep(info->t_sleep);
		prints(info, philo->id, THINK);
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
	return (0);
}
