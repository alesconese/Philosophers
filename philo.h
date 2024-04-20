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

# define MALLOC_ERROR 1

typedef struct	s_fork
{
	int	id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct	s_philo
{

}	t_philo;

typedef struct 	s_data
{
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_meals;
	t_philo	*philos;

}	t_data;

#endif