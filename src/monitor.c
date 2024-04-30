/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:30:41 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/28 18:30:42 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_deadorfull(t_philo *philo, int *full_counter)
{
	size_t	t_died;

	pthread_mutex_lock(&philo->philo_mtx);
	t_died = ft_elapsedtime_ms(philo->data->start_time) - philo->last_meal;
	if (philo->meals == philo->data->req_meals)
		(*full_counter)++;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (t_died > philo->data->t2die)
	{
		ft_printaction_mtx(*philo, DIE, 0);
		return (1);
	}
	return (0);
}

void	ft_monitor_loop(t_data *data)
{
	int	i;
	int	full_counter;
	int	philo_dead;

	while (123)
	{
		i = 0;
		full_counter = 0;
		philo_dead = 0;
		while (i < data->n_philos)
		{
			philo_dead = ft_deadorfull(&data->philos[i], &full_counter);
			if (philo_dead || full_counter == data->n_philos)
			{
				pthread_mutex_lock(&data->death_mtx);
				data->end = 1;
				pthread_mutex_unlock(&data->death_mtx);
				return ;
			}
			i++;
		}
	}
}
