/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:39:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/07 22:24:18 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
}

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->n_philo;
		philo[i].last_meal = get_timestamp();
		philo[i].meals_eaten = 0;
		philo[i].data = data;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&philo[i], NULL, routine, &philo[i]);
		i++;
	}
}
