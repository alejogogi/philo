/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 16:25:47 by alejogogi        ###   ########.fr       */
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

void	*monitor(void *arg)
{
	t_philo *philo = (t_philo*) arg;
	t_data *data = philo[0].data;
	int	i;
	int	finished_eating;
	long	time_last_meal;

	while (!check_death(data))//revisamos que ninguno este muerto
	{
		i = 0;
		finished_eating = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(philo[i].meal_lock);
			time_last_meal = get_timestamp() - philo->last_meal;
			if (time_last_meal > data->time_die)
			{
				print_action(&philo[i], "died");
				philo_death(data);
				pthread_mutex_unlock(philo[i].meal_lock);
				return (NULL);
			}
			if (data->time_count != -1 && philo[i].meals_eaten >= data->time_count)
				finished_eating++;
			pthread_mutex_unlock(philo[i].meal_lock);
			i++;
		}
		if (data->time_count != -1 && finished_eating == data->n_philo)
		{
			philo_death(data);
			return (NULL);
		}
		usleep(1000);
	}
	return(NULL);
}
