/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:39:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/08 19:19:21 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_now(t_data *data)
{
	return (get_timestamp() - data->start_time);
} //el timestamp_now se usa cuando se vaya a imprimir algo en pantalla para el tiempo

long	get_timestamp(void)
{
	struct timeval tv;
	long	miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
} //cuenta cuantos milisegundos tiene el programa corriendo.

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
		ft_usleep(philo->data->time_sleep);
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
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % philo->data->n_philo;
		philo[i].last_meal = get_timestamp();
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
	{
		free_all(data);
		exit_error();
	}
	aux_init_philo(philo); //iniciamos la rutina de los filosofos aqui.
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL, routine, &philo[i]) != 0)
		{
			pthread_mutex_destroy(&data->print_lock);
			destroy_forks(data, data->n_philo);
			aux_exit(data);
		}
		i++;
	}
} //revisar la liberacion del codigo fugas de memoria en esta parte.
