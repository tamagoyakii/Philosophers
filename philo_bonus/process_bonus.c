/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:40:52 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/08 14:48:41 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_pids(t_info *info, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill(info->pid[i], SIGINT);
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

void	end_process(t_info *info)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < info->n_philo)
	{
		waitpid(-1, &wstatus, 0);
		if (wstatus >> 8 == DIE)
		{
			close_pids(info, info->n_philo);
			break ;
		}
		else if (wstatus >> 8 == FULL)
		{
			info->n_full_philo += 1;
			sem_post(info->check);
		}
	}
	if (info->n_full_philo == info->n_philo)
		printf("everyone is full!\n");
}
