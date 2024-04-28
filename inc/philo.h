/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:34:18 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/20 18:34:20 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define MALLOC_ERROR 1

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	t_data		*data;
	int			meals;
	size_t		last_meal;
	pthread_t	thid;
}	t_philo;

struct s_data
{
	int				n_philos;
	size_t			t2die;
	size_t			t2eat;
	size_t			t2sleep;
	int				req_meals;
	size_t			start_time;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	meals_mtx;
	pthread_mutex_t	*forks_mtx;
	t_philo			*philos;
	int				dead;
};

///// TIME /////

size_t	get_current_time_ms(void);

size_t	time_elapsed_ms(size_t	start);

void	sleep_ms(size_t time_ms);

///// MONITOR /////

void	monitor_loop(t_data *data);

///// INIT /////

int		data_init(t_data *data, char **argv);

///// PHILO_LOOP /////

void	*philo_loop(void *philo_void);

///// MAIN /////

void	ft_cleanup(t_data *data);

#endif