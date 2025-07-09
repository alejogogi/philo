/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/09 17:05:04 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_die)
{
	
}// funcion que hace que el filosofo muera en el tiempo establecido.

void	check_onephilo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	
}

void	take_forks(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		pthre
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		
	}
}