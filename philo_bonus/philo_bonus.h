/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:31 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/06 14:01:02 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>		/* printf()					*/
# include <unistd.h>	/* fork(), usleep()			*/
# include <stdlib.h>	/* malloc(), free(), exit() */
# include <signal.h>	/* kill()					*/
# include <sys/time.h>	/* gettimeofday()			*/
# include <sys/types.h>	/* sem_t, pid_t      		*/
# include <pthread.h>	/* pthread_create()...		*/
# include <semaphore.h>	/* sem_open()...			*/
# include <fcntl.h> 	/* O_CREAT, O_EXEC			*/
# include <sys/stat.h>	/* mode_t					*/

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define FULL 6

typedef struct s_info
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_must_eat;
	int			n_full_philo;
	long long	t_start;
	pid_t		*pid;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*check;
}				t_info;

typedef struct s_philo
{
	int			id;
	long long	t_last_eat;
	int			n_eat;
	t_info		*info;
}				t_philo;

/* utils_bonus.c */
void	prints(t_info *info, int id, int status);
void	psleep(long long t_sleep);
int		get_time(void);
int		check_digit(char *argv[]);
int		ft_atoi(const char *str);

/* philo_bonus.c */
void	*check_death(void *arg);
int		philo_eat(t_info *info, t_philo *philo);
void	philo_act(t_philo *philo);
void	philo_start(t_philo *philo);

/* process_bonus.c */
void	close_pids(t_info *info, int id);
void	make_process(t_info *info, t_philo **philo);
void	end_process(t_info *info);

/* sem_bonus.c */
sem_t	*get_sem(char *label, int num);
int		set_sem(t_info *info);

/* main_bonus.c */
void	error_exit(char *str);
void	set_info(t_info *info, char *argv[]);
void	set_philo(t_info *info, t_philo **philo);
int		free_all(t_info *info, t_philo **philo);

#endif