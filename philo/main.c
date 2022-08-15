/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:16:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/15 15:37:44 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || check_digit(argv))
		return (printf("wrong parameters\n"));
	if (set_info(&info, argv))
		return (printf("set_info failed\n"));
	philo = malloc(sizeof(t_philo) * (info.n_philo));
	if (!philo)
		return (printf("philo malloc failed\n"));
	info.fork = malloc(sizeof(pthread_mutex_t) * info.n_philo);
	if (!info.fork)
		return (printf("fork malloc failed\n"));
	if (set_philo(&info, philo))
		return (printf("set_philo failed\n"));
	if (philo_start(&info, philo))
		return (printf("philo_start failed\n"));
	return (0);
}
