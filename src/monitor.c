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

void	monitor_loop(t_data *data)
{
	int	i;
	size_t	t_died;//debug


	i = 0;
	while (!data->dead)	
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&data->meals_mtx);
			t_died = time_elapsed_ms(data->start_time) - data->philos[i].last_meal;//debug
			pthread_mutex_unlock(&data->meals_mtx);
			if (t_died > data->t2die)
			{
				pthread_mutex_lock(&data->print_mtx);
				printf ("%zu %d", time_elapsed_ms(data->start_time), data->philos[i].id);
				printf (" has died\n");
				pthread_mutex_unlock(&data->print_mtx);
				pthread_mutex_lock(&data->death_mtx);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mtx);
				return ;
			}
			i++;
		}
	}
}
