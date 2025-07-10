/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:39:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 21:51:43 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, monitor, data) != 0)
	{
		philo_death(data);
		return ;
	}
}

void	check_onephilo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	philo_death(philo->data);
	pthread_mutex_unlock(philo->left_fork);
	usleep(200000);
	printf("%ld %d %s\n",timestamp_now(data),philo->id + 1, "philo dead");
	destroy_meals(philo, data->n_philo);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(philo);
	free(data->threads);
	destroy_forks(data, data->n_philo);
	free(data);
	exit(1);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0) 
		usleep(1000);
	while (!check_death(philo->data))
	{
		print_action(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep, philo->data);
	}
	return (NULL);
}

void	aux_init_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = &philo->data->forks[i];
		philo[i].right_fork = &philo->data->forks[(i + 1) % philo->data->n_philo];	
		philo[i].last_meal = timestamp_now(philo[i].data); //get_timestamp();
		philo[i].meals_eaten = 0;
		philo[i].data = philo->data;
		i++;	
	}	
}

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->threads)
		philo_free(philo, data);
	aux_init_philo(philo);
	i = 0;
	if (philo->data->n_philo == 1)
		check_onephilo(philo, data);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL, routine, &philo[i]) != 0)
		{
			destroy_threads(data, i);
			philo_free(philo, data);
		}
		i++;
	}
}
