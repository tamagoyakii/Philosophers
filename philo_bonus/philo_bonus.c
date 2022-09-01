/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/01 17:05:47 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	t_info *info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (1)
	{
		sem_wait(info->check_death);
		if (get_time() - philo->t_last_eat >= info->t_die)
		{
			sem_post(info->check_death);
			exit(1);
		}
		sem_post(info->check_death);
		// usleep(100);
	}
	return (0);
}

int	philo_start(t_philo *philo)
{
	pthread_t	thread;
	
	philo->t_last_eat = get_time();
	if (pthread_create(&thread, 0, &check_death, philo))
		return (1);
	pthread_join(thread, 0);
	philo_act(philo);
}
