/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:31 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/12 18:33:18 by jihyukim         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	long long		t_last_eat;
	int				n_eat;
}				t_philo;

typedef struct s_info
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long long		t_start;
}				t_info;

int	print_err(char *str, int err_code);
int	ft_isdigit(int c);
int	check_digit(char *argv[]);
int	ft_atoi(const char *str);
int	get_time(void);

int	set_info(t_info *info, char *argv[]);
int	set_philo(t_info *info, t_philo **philo);

#endif