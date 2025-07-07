/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:43:25 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/07 20:36:13 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_count;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}					t_data;

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	meals_eaten;
	long	last_meal;
	pthread_t		thread;
	t_data			*data;

}					t_philo;

// functions aux:
int					ft_atoi_safe(char *str);

// free mem:
void				exit_error(void);
void				aux_exit(t_data *data);
void				destroy_forks(t_data *data, int n);
void				free_all(t_data *data);

// init mutex:
void				init_mutex(t_data *data);
void				inside_args_data(t_data *data, char **arg);
void				philo_death(t_data *data);
int					check_death(t_data *data);

#endif