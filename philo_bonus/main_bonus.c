/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:16:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/23 15:05:47 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_exit(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(1);
}

int	free_all(t_info *info, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
		kill(philos[i].pid, SIGTERM);
	sem_close(info->fork);
	sem_unlink("fork");
	sem_close(info->print);
	sem_unlink("print");
	sem_close(info->check_death);
	sem_unlink("deadcheck");
	free(philos);
	return (0);
}

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

int	set_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * (info->n_philo));
	if (!(*philo))
		error_exit("philo malloc failed\n");
	i = -1;
	while (++i < info->n_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].t_last_eat = get_time();
		(*philo)[i].n_eat = 0;
		(*philo)[i].info = info;
	}
	i = -1;
	while (++i < info->n_philo)
	{
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == 0)
			philo_start(&((*philo)[i]));
		else if ((*philo)[i].pid < 0)
			error_exit("fork() failed\n");
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || check_digit(argv))
		error_exit("wrong parameters\n");
	if (set_info(&info, argv))
		error_exit("set_info failed\n");
	if (set_sem(&info))
		error_exit("semaphore failed\n");
	if (set_philo(&info, &philo))
		error_exit("set_philo failed\n");
	free_all(&info, philo);
	return (0);
}