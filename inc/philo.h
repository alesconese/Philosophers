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
	t_data			*data;
	int				id;
	pthread_mutex_t	philo_mtx;
	pthread_t		thid;
	size_t			last_meal;
	int				meals;
}	t_philo;

struct s_data
{
	int				n_philos;
	size_t			t2die;
	size_t			t2eat;
	size_t			t2sleep;
	int				req_meals;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	*forks_mtx;
	t_philo			*philos;
	size_t			start_time;
	int				end;
};

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_action;

typedef enum e_error
{
	ARGS,
	CHARS,
	TOOBIG,
}	t_error;

///// TIME /////

size_t	ft_gettime_ms(void);

size_t	ft_elapsedtime_ms(size_t	start);

void	ft_sleep_ms(size_t time_ms);

///// MONITOR /////

void	ft_monitor_loop(t_data *data);

///// INIT /////

int		ft_data_init(t_data *data, char **argv);

int		ft_mutex_thread_init(t_data *data);

void	ft_error(t_error type);

///// PHILO_LOOP /////

void	*ft_philo_loop(void *philo_void);

void	ft_printaction_mtx(t_philo philo, t_action action, int fork);

///// MAIN /////

void	ft_join_threads(t_data *data, int n);

void	ft_mutex_destroyer(t_data *data, int step, int iters);

#endif