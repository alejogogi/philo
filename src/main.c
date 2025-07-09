/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:33:56 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 19:06:32 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int ac, char **arg)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		exit_error();
	while (i < ac)
	{
		if (ft_atoi_safe(arg[i]) == 0)
			exit_error();
		i++;
	}
}

int	ft_atoi_safe(char *str)
{
	long	num;

	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '\0')
		exit_error();
	else if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			exit_error();
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10;
		num = num + *str - '0';
		str++;
	}
	if (*str != '\0')
		exit_error();
	else if (num > INT_MAX)
		exit_error();
	return ((int)num);
}

int	main(int ac, char **arg)
{
	t_data	*data;
	t_philo *philo;

	check_args(ac, arg);
	data = malloc(sizeof(t_data));
	if (!data)
		exit_error();
	inside_args_data(data, arg);
	init_mutex(data);
	philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!philo)
	{
		free_all(data);
		exit_error();
	}
	init_philo(philo, data);
	free_end(philo);
	return (0);
}
