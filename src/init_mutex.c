/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:38:29 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/07 20:24:05 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}

int	check_death(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->death_lock);
	status = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (status);
}

void	inside_args_data(t_data *data, char **arg)
{
	data->n_philo = ft_atoi_safe(arg[1]);
	data->time_die = ft_atoi_safe(arg[2]);
	data->time_eat = ft_atoi_safe(arg[3]);
	data->time_sleep = ft_atoi_safe(arg[4]);
	if (arg[5])
		data->time_count = ft_atoi_safe(arg[5]);
	else
		data->time_count = -1;
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		aux_exit(data);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			destroy_forks(data, i);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		destroy_forks(data, data->n_philo);
	else if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		destroy_forks(data, data->n_philo);
		aux_exit(data);
	}
	data->someone_died = 0;
}
