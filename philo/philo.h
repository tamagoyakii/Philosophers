/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:31 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/22 15:25:20 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_info
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long long		t_start;
	int				is_dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	check_death;
}				t_info;

typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	long long	t_last_eat;
	int			n_eat;
	t_info		*info;
	pthread_t	thread;
}				t_philo;

/* utils.c */
int		prints(t_info *info, long long t_act, int id, int status);
void	psleep(long long t_sleep);
int		get_time(void);
int		check_digit(char *argv[]);
int		ft_atoi(const char *str);

/* philo.c */
int		is_dead(t_philo *philo);
int		philo_eat(t_info *info, t_philo *philo);
void	*philo_act(void *philo);
int		philo_start(t_info *info, t_philo *philo);

/* main.c */
int		set_info(t_info *info, char *argv[]);
int		set_philo(t_info *info, t_philo *philo);

#endif