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

void	ft_printaction_mtx(t_philo philo, t_action action, int fork)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo.data->death_mtx);
	if (philo.data->end)
	{
		pthread_mutex_unlock(&philo.data->death_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo.data->death_mtx);
	pthread_mutex_lock(&philo.data->print_mtx);
	timestamp = ft_elapsedtime_ms(philo.data->start_time);
	if (action == FORK)
		printf("%zu\t%d has taken fork %d\n", timestamp, philo.id, fork);
	else if (action == EAT)
		printf("%zu\t%d is eating\n", timestamp, philo.id);
	else if (action == SLEEP)
		printf("%zu\t%d is sleeping\n", timestamp, philo.id);
	else if (action == THINK)
		printf("%zu\t%d is thinking\n", timestamp, philo.id);
	else if (action == DIE)
		printf("%zu\t%d died\n", timestamp, philo.id);
	pthread_mutex_unlock(&philo.data->print_mtx);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mtx[philo->id - 1]);
	ft_printaction_mtx(*philo, FORK, philo->id - 1);
	if (philo->id == philo->data->n_philos)
	{
		pthread_mutex_lock(&philo->data->forks_mtx[0]);
		ft_printaction_mtx(*philo, FORK, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks_mtx[philo->id]);
		ft_printaction_mtx(*philo, FORK, philo->id);
	}
	ft_printaction_mtx(*philo, EAT, 0);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal = ft_elapsedtime_ms(philo->data->start_time);
	philo->meals++;
	pthread_mutex_unlock(&philo->philo_mtx);
	ft_sleep_ms(philo->data->t2eat);
	pthread_mutex_unlock(&philo->data->forks_mtx[philo->id - 1]);
	if (philo->id == philo->data->n_philos)
		pthread_mutex_unlock(&philo->data->forks_mtx[0]);
	else
		pthread_mutex_unlock(&philo->data->forks_mtx[philo->id]);
}

void	*ft_philo_loop(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->id % 2 == 0)
		ft_sleep_ms(30);
	while (123)
	{
		pthread_mutex_lock(&philo->data->death_mtx);
		if (philo->data->end)
		{
			pthread_mutex_unlock(&philo->data->death_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death_mtx);
		ft_eat(philo);
		if (philo->meals == philo->data->req_meals)
			break ;
		ft_printaction_mtx(*philo, SLEEP, 0);
		ft_sleep_ms(philo->data->t2sleep);
		ft_printaction_mtx(*philo, THINK, 0);
	}
	return (NULL);
}
