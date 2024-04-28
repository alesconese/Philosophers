/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:34:30 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/20 18:34:32 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_join_threads(t_data *data, int n)
{
	int	i;
	
	i = 0;
	while(i <= n)
	{
		pthread_join(data->philos[i].thid, NULL);
		i++;
	}
}

void	ft_cleanup(t_data *data)
{
	ft_join_threads(data, data->n_philos);

	pthread_mutex_destroy(&data->print_mtx);
	free(data->philos);
	free(data->forks_mtx);
	free (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Wrong arguments. Corrrect format is {./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (OPT)[number_of_times_each_philosopher_must_eat]}\n");
		return(1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(1);
	memset(data, 0, sizeof(t_data));
	if (data_init(data, argv))
		return (ft_cleanup(data), 1);
	monitor_loop(data);
	ft_cleanup(data);
	return (0);
}
