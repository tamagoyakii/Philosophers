/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:15:34 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/15 15:16:56 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_info(t_info *info, char *argv[])
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->n_philo < 0 || info->t_die < 0 || info->t_eat < 0
		|| info->t_sleep < 0)
		return (1);
	info->t_start = get_time();
	info->is_dead = 0;
	if (argv[5])
	{
		info->n_must_eat = ft_atoi(argv[5]);
		if (info->n_must_eat < 0)
			return (1);
	}
	else
		info->n_must_eat = -1;
	return (0);
}

int	set_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		philo[i].id = i;
		philo[i].left = i;
		philo[i].right = i + 1;
		if (i + 1 == info->n_philo)
			philo[i].right = 0;
		philo[i].t_last_eat = get_time();
		philo[i].n_eat = 0;
		philo[i].info = info;
		if (pthread_mutex_init(&info->fork[i], 0) != 0)
			return (1);
	}
	return (0);
}
