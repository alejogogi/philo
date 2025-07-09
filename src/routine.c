/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 22:52:46 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_die, t_data *data)
{
	long	start;

	start = get_timestamp();
	while (!check_death(data) && timestamp_now(data) < time_die)
		usleep(100);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has take a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has take a fork");		
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = timestamp_now(philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_eat, philo->data);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// void *monitor(void *arg)
// {
// 	t_philo *philos = (t_philo *)arg;
// 	t_data *data = philos[0].data;

// 	while (1)
// 	{
// 		for (int i = 0; i < data->n_philo; i++)
// 		{
// 			long now = get_time();
// 			long since_meal = now - philos[i].last_meal;

// 			if (since_meal > data->time_die)
// 			{
// 				pthread_mutex_lock(&data->death_lock);
// 				if (!data->someone_died)
// 				{
// 					data->someone_died = 1;
// 					pthread_mutex_lock(&data->print_lock);
// 					printf("%ld %d died\n", now - data->start_time, philos[i].id);
// 					pthread_mutex_unlock(&data->print_lock);
// 				}
// 				pthread_mutex_unlock(&data->death_lock);
// 				return NULL;
// 			}
// 		}
// 		usleep(1000); // chequeo frecuente
// 	}
// 	return NULL;
// } // revisar bien y hacer pruebas.
