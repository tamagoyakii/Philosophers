/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:12:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/31 19:40:09 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->fork[philo->left]);
	prints(info, philo->id, FORK);
	pthread_mutex_lock(&info->fork[philo->right]);
	prints(info, philo->id, FORK);
	prints(info, philo->id, EAT);
	pthread_mutex_lock(&info->check_last_eat);
	philo->t_last_eat = get_time();
	philo->n_eat += 1;
	pthread_mutex_unlock(&info->check_last_eat);
	psleep(info->t_eat);
	pthread_mutex_unlock(&(info->fork[philo->right]));
	pthread_mutex_unlock(&(info->fork[philo->left]));
	return (0);
}

int	philo_sleep(t_info *info, t_philo *philo)
{
	prints(info, philo->id, SLEEP);
	psleep(info->t_sleep);
	return (0);
}

void	add_full(t_info *info, int n_eat)
{
	if (n_eat == info->n_must_eat)
	{
		pthread_mutex_lock(&(info->check_full));
		info->n_full_philo += 1;
		pthread_mutex_unlock(&(info->check_full));
	}
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
		if (info->n_must_eat != -1 && philo->n_eat >= info->n_must_eat)
			break ;
		if (is_dead(info, philo))
			break ;
		if (philo_eat(info, philo))
			break ;
		if (philo_sleep(info, philo))
			break ;
		prints(info, philo->id, THINK);
	}	
	add_full(info, philo->n_eat);
	return (0);
}
