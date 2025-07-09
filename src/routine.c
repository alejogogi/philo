/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 19:04:45 by alejogogi        ###   ########.fr       */
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
	pthread_mutex_lock(philo->last_meal);
	philo->last_meal = timestamp_now(philo->data);
	pthread_mutex_unlock(philo->last_meal);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_die, philo->data);
	pthread_mutex_lock(philo->meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meals_eaten);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}