/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:43:25 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/10 21:47:09 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_count;
	int				someone_died;
	long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_t	*threads;
	pthread_t	monitor;
}					t_data;

typedef struct s_philo
{
	int	id;
	int	meals_eaten;
	long	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t *meal_lock;
	pthread_t		thread;
	t_data			*data;

}					t_philo;

// functions_aux:
int					ft_atoi_safe(char *str);

// free_mem:
void				exit_error(void);
void				aux_exit(t_data *data, int n);
void				destroy_forks(t_data *data, int n);
void				free_all(t_data *data, t_philo *philos);
void				destroy_threads(t_data *data, int n);
void				destroy_meals(t_philo *philo, int n);
void				philo_free(t_philo *philo, t_data *data);
void				free_end(t_philo *philo, t_data *data);

// init_mutex:
void				init_mutex(t_data *data);
void				inside_args_data(t_data *data, char **arg);
void				init_mutex_philo(t_philo *philos, t_data *data, int n);
void				wait_threads(t_data *data, t_philo *philo);

// init_philo:
void				init_philo(t_philo *philo, t_data *data);
void				aux_init_philo(t_philo *philo);
void				*routine(void *arg);
void				check_onephilo(t_philo *philo, t_data *data);
void				init_monitor(t_data *data);

// function_philo_aux:
int					check_death(t_data *data);
long		timestamp_now(t_data *data);
long		get_timestamp(void);
void				philo_death(t_data *data);
void				print_action(t_philo *philo, char *action);

//routine
void				ft_usleep(int time_die, t_data *data);
void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				drop_forks(t_philo *philo);
void				*monitor(void *arg);

#endif