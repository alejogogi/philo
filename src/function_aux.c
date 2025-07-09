/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:43:00 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 18:29:45 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!check_death(philo->data))
	{
		timestamp = timestamp_now(philo->data);
		printf("%ld %d %s\n", timestamp, philo->id + 1, action);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}// hacer la funcion de imprimir, y poner dentro el detector de muerte.

void	philo_death(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}// esta se usa para marcar al philo como muerto. se pone si se cumple una condicion para que se muera

int	check_death(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->death_lock);
	status = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (status);
}// esta revisa si el philo sigue con vida, de no estar con vida se destruye el programa y los hilos.

long	timestamp_now(t_data *data)
{
	return (get_timestamp() - data->start_time);
} //esta funcion me da el tiempo actual que lleva el programa, porque la variable start_time ya tiene el tiempo.

long	get_timestamp(void)
{
	struct timeval tv;
	long	miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}
