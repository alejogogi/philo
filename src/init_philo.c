/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:39:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 18:06:06 by alejogogi        ###   ########.fr       */
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

void	check_onephilo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	philo_death(philo->data);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->data->n_philo == 1)
	{
		check_onephilo(philo);
		return (NULL);
	}
	else if (philo->id % 2 == 0) //esto retrasa a los filosofos pares para que no todos tomen los tenedores al inicio.
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
	return (NULL); //faltan crear las funciones de las routines
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
		philo[i].last_meal = get_timestamp();
		philo[i].meals_eaten = 0;
		philo[i].data = philo->data;
		i++;	
	}	
}// revisar una condicion en caso de que mi programa unicamente tenga un filosofo.

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->threads)
		philo_free(philo, data);
	aux_init_philo(philo);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL, routine, &philo[i]) != 0)
		{
			destroy_threads(data, i);
			philo_free(philo, data);
		}
		i++;
	}
} //revisar la liberacion del codigo fugas de memoria en esta parte.
