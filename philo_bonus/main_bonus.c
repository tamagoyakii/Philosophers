/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:16:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/04 21:15:40 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_exit(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(1);
}

void	close_pids(t_info *info, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill(info->pid[i], SIGINT);
}

void	set_info(t_info *info, char *argv[])
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->n_philo < 0 || info->t_die < 0 || info->t_eat < 0
		|| info->t_sleep < 0)
		error_exit("invalid parameters");
	info->t_start = get_time();
	info->is_dead = 0;
	if (argv[5])
	{
		info->n_must_eat = ft_atoi(argv[5]);
		if (info->n_must_eat < 0)
			error_exit("invalid parameters");
	}
	else
		info->n_must_eat = -1;
	if (set_sem(info))
		error_exit("semaphore failed\n");
}

void	set_philo(t_info *info, t_philo **philo)
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
		(*philo)[i].status = EAT;
		(*philo)[i].info = info;
	}
}

void	make_process(t_info *info, t_philo **philo)
{
	int	i;

	info->pid = malloc(sizeof(pid_t) * info->n_philo);
	if (!(info->pid))
		error_exit("pid malloc failed\n");
	i = -1;
	while (++i < info->n_philo)
	{
		info->pid[i] = fork();
		if (info->pid[i] < 0)
		{
			close_pids(info, i);
			error_exit("fork process failed\n");
		}
		if (info->pid[i] == 0)
			philo_start(&(*philo)[i]);
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || check_digit(argv))
		error_exit("wrong parameters\n");
	set_info(&info, argv);
	set_philo(&info, &philo);
	make_process(&info, philo);
	free_all(&info, philo);
	return (0);
}
