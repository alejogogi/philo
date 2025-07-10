/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:06:45 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 17:51:12 by alejogogi        ###   ########.fr       */
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
		free(philo[i].meal_lock);
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
	free(data->threads);
}

void	aux_exit(t_data *data, int n)
{
	destroy_forks(data, n);
	free(data);
	exit_error();
}//segundo.

void	exit_error(void)
{
	printf("Error\n");
	exit(1);
}//primero

void	free_all(t_data *data, t_philo *philo)
{
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	if (philo)
		free(philo);
	aux_exit(data, data->n_philo);
}// tercero

void	philo_free(t_philo *philo, t_data *data)
{
	destroy_meals(philo, data->n_philo);
	free(data->threads);
	free_all(data, philo);
}//cuarto.