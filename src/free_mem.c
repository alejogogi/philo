/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:06:45 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 22:22:16 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_meals(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
}

void	destroy_forks(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	destroy_threads(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}

void	aux_exit(t_data *data)
{
	free(data);
	exit_error();
}

void	exit_error(void)
{
	printf("Error\n");
	exit(1);
}

void	free_all(t_data *data)
{
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	destroy_forks(data, data->n_philo);
	free(data);
}

void	free_end(t_philo *philo)
{
	
}