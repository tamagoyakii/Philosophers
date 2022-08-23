/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:31 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/22 21:08:26 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_info
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_must_eat;
	long long	t_start;
	int			is_dead;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*check_death;
}				t_info;

typedef struct s_philo
{
	int			id;
	long long	t_last_eat;
	int			n_eat;
	pid_t		pid;
	t_info		*info;
}				t_philo;

/* utils_bonus.c */
int		prints(t_info *info, long long t_act, int id, int status);
void	psleep(long long t_sleep);
int		get_time(void);
int		check_digit(char *argv[]);
int		ft_atoi(const char *str);

/* philo_bonus.c */
int		is_dead(t_philo *philo);
int		philo_eat(t_info *info, t_philo *philo);
void	*philo_act(void *philo);
int		philo_start(t_info *info, t_philo *philo);

/* main_bonus.c */
int		set_info(t_info *info, char *argv[]);
int		set_philo(t_info *info, t_philo **philo);

#endif