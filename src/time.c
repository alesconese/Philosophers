/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:35:53 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/28 18:35:54 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	get_current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	time_elapsed_ms(size_t	start)
{
	return (get_current_time_ms() - start);
}

void	sleep_ms(size_t time_ms)
{
	size_t	begin;

	begin = get_current_time_ms();
	while (get_current_time_ms() < begin + time_ms)
		usleep(500);
}
