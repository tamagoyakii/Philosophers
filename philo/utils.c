/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:44:11 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/12 17:57:07 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_err(char *str, int err_code)
{
	printf("%s", str);
	return (err_code);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	check_digit(char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+')
				return (1);
			if ((argv[i][j] == '+') && !ft_isdigit(argv[i][j + 1]))
				return (1);
			if ((argv[i][j] == '+') && j != 0)
				return (1);
		}
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	ret;

	sign = 1;
	ret = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str && ((*str == '-') || (*str == '+')))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - 48);
		if (ret * sign > 2147483647)
			return (-1);
		else if (ret * sign < -2147483648)
			return (0);
		str++;
	}
	return (ret * sign);
}

int	get_time(void)
{
	struct	timeval	time;

	if (gettimeofday(&time, 0) == -1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
