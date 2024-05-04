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
	while (i < n)
	{
		pthread_join(data->philos[i].thid, NULL);
		i++;
	}
	ft_mutex_destroyer(data, 4, data->n_philos);
}

void	ft_mutex_destroyer(t_data *data, int step, int iters)
{
	int	i;

	i = -1;
	if (step >= 1)
		pthread_mutex_destroy(&data->print_mtx);
	if (step >= 2)
		pthread_mutex_destroy(&data->death_mtx);
	if (step == 3)
		while (++i < iters)
			pthread_mutex_destroy(&data->forks_mtx[i]);
	if (step == 4)
	{
		while (++i < data->n_philos)
			pthread_mutex_destroy(&data->forks_mtx[i]);
		i = 0;
		while (++i < iters)
			pthread_mutex_destroy(&data->philos[i].philo_mtx);
	}
}

static void	ft_cleanup(t_data *data)
{
	ft_join_threads(data, data->n_philos);
	free(data->philos);
	free(data->forks_mtx);
	free (data);
}

static void	ft_lonely_philo(t_data *data)
{
	printf("0\t1 has taken fork 0\n");
	ft_sleep_ms(data->t2die);
	printf("%zu\t1 died\n", data->t2die);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (ft_error(ARGS), 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	memset(data, 0, sizeof(t_data));
	if (ft_data_init(data, argv))
		return (free(data), 1);
	if (data->n_philos == 1)
		return (ft_lonely_philo(data), free(data->philos), \
		free(data->forks_mtx), free(data), 1);
	if (ft_mutex_thread_init(data))
		return (free(data->philos), free(data->forks_mtx), free(data), 1);
	pthread_mutex_lock(&data->death_mtx);
	data->all_ready = 1;
	pthread_mutex_unlock(&data->death_mtx);
	ft_monitor_loop(data);
	ft_cleanup(data);
	return (0);
}
