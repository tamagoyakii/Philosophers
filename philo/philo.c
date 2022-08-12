/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/12 18:37:33 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_info(t_info *info, char *argv[])
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_must_eat = 0;
	if (argv[5])
		info->n_must_eat = ft_atoi(argv[5]);
	if (info->n_philo < 0 || info->t_die < 0 || info->t_eat < 0
		|| info->t_sleep < 0 || info->n_must_eat < 0)
		return (1);
	info->t_start = get_time();
	return (0);
}

int	set_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * (info->n_philo + 1));
	if (!philo)
		return (1);
	i = -1;
	while (++i < info->n_philo)
	{
		philo[i]->id = i;
		philo[i]->left = i;
		philo[i]->right = i + 1;
		if (i + 1 == info->n_philo)
			philo[i]->right = 0;
		philo[i]->t_last_eat = get_time();
		philo[i]->n_eat = 0;
		printf("%d : %lld\n", i, philo[i]->t_last_eat);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;
	int		err;

	err = 0;
	if (argc != 5 && argc != 6)
		return (print_err("wrong parameters\n", err));
	err = check_digit(argv);
	if (err != 0)
		return (print_err("invalid parameters\n", err));
	err = set_info(&info, argv);
	if (err != 0)
		return (print_err("set_info failed\n", err));
	err = set_philo(&info, &philo);
	return (0);
}