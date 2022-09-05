/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:06:00 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/05 18:50:25 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*get_sem(char *label, int num)
{
	sem_t	*sem;

	sem = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	if (sem == SEM_FAILED)
	{
		sem_unlink(label);
		sem = sem_open(label, O_CREAT | O_EXCL, 0644, (unsigned int)num);
	}
	return (sem);
}

int	set_sem(t_info *info)
{
	info->fork = get_sem("fork", info->n_philo);
	if (info->fork == SEM_FAILED)
		return (1);
	info->print = get_sem("print", 1);
	if (info->print == SEM_FAILED)
		return (1);
	info->check = get_sem("check", 1);
	if (info->check == SEM_FAILED)
		return (1);
	return (0);
}

int	free_all(t_info *info)
{
	sem_close(info->fork);
	sem_unlink("fork");
	sem_close(info->print);
	sem_unlink("print");
	sem_close(info->check);
	sem_unlink("check");
	free(info->pid);
	return (0);
}
