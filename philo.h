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
	int				t2die;
	int				t2eat;
	int				t2sleep;
	int				req_meals;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*forks_mtx;
	t_philo			*philos;
	size_t			start_time;
	int				dead;
};

#endif