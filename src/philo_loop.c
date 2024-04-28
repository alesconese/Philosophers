/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:25:14 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/28 19:25:15 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//DEBUG FUNCTION. REMOVE!
void	debug(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf ("%zu ", time_elapsed_ms(philo->data->start_time));
	printf("hola soy el filo ");
	printf("%d\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

void	*philo_loop(void *philo_void)
{
	t_philo	*philo;
	int		flag;
	
	philo = (t_philo *)philo_void;
	flag = 0;
	if (philo->data->req_meals >= 0)
		flag = 1;
	//if (philo->id % 2 == 0)
		//ft_usleep(philo->data->t2eat / 2);//TODO
	while (123)
	{
		pthread_mutex_lock(&philo->data->death_mtx);
		if ((flag && (philo->meals >= philo->data->req_meals)) || philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death_mtx);
		//TRY TO LOCK L & R FORKS
		pthread_mutex_lock(&philo->data->forks_mtx[philo->id - 1]);
		if (philo->id == philo->data->n_philos)
			pthread_mutex_lock(&philo->data->forks_mtx[0]);
		else
			pthread_mutex_lock(&philo->data->forks_mtx[philo->id]);
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%zu %d has taken fork %d\n", time_elapsed_ms(philo->data->start_time), philo->id, philo->id - 1);
		if (philo->id == philo->data->n_philos)
			printf("%zu %d has taken fork %d\n", time_elapsed_ms(philo->data->start_time), philo->id, 0);
		else
			printf("%zu %d has taken fork %d\n", time_elapsed_ms(philo->data->start_time), philo->id, philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		//SET last_meal WHEN BOTH FORKS ARE LOCKED
		pthread_mutex_lock(&philo->data->meals_mtx);
		philo->last_meal = time_elapsed_ms(philo->data->start_time);
		pthread_mutex_unlock(&philo->data->meals_mtx);
		//PRINT EATING MSG
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%zu %d is eating\n", time_elapsed_ms(philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		//WAIT FOR t2eat
		sleep_ms(philo->data->t2eat);
		philo->meals++;
		//UNLOCK FORKS
		pthread_mutex_unlock(&philo->data->forks_mtx[philo->id - 1]);
		if (philo->id == philo->data->n_philos)
			pthread_mutex_unlock(&philo->data->forks_mtx[0]);
		else
			pthread_mutex_unlock(&philo->data->forks_mtx[philo->id]);
		//PRINT SLEEPING MSG
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%zu %d is sleeping\n", time_elapsed_ms(philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		//WAIT FOR t2sleep
		sleep_ms(philo->data->t2sleep);
		//PRINT THINKING MSG
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%zu %d is thinking\n", time_elapsed_ms(philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
	return (NULL);
}
