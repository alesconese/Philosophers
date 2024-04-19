#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct	s_fork
{
	int	id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct	s_philo
