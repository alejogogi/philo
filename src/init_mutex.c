/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:38:29 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 17:22:00 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	init_mutex_philo(t_philo *philos, int n)
{
	int	i = 0;

	while (i < n)
	{
		philos[i].meal_lock = malloc(sizeof(pthread_mutex_t));
		if (!philos[i].meal_lock)
		{
			destroy_meals(philos, i);
			free_all(philos->data, philos);
		}
		if (pthread_mutex_init(philos[i].meal_lock, NULL) != 0)
		{
			destroy_meals(philos, i);
			free_all(philos->data, philos);
		}
		i++;
	}
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
		aux_exit(data, 0);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			aux_exit(data, i);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		aux_exit(data, data->n_philo);
	else if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		aux_exit(data, data->n_philo);
	}
	data->someone_died = 0;
}
