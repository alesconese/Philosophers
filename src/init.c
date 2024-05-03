/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:08:00 by ade-tole          #+#    #+#             */
/*   Updated: 2024/04/28 19:08:02 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_error(t_error type)
{
	if (type == ARGS)
		printf("ERROR: Wrong arguments. Corrrect format is {./philo \
		[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
		(OPT)[number_of_times_each_philosopher_must_eat]}\n");
	else if (type == CHARS)
		printf("ERROR: arguments must be numerical AND positive\n");
	else if (type == TOOBIG)
		printf("ERROR: arguments cannot be higher than 2147483647\n");
}

static int	arg_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_error(CHARS), 1);
			j++;
		}
		if (j > 9)
			return (ft_error(TOOBIG), 1);
		i++;
	}
	return (0);
}

static int	ft_atoi(char *str)
{
	long	nbr;

	nbr = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		if (nbr > 2147483647)
			return (ft_error(TOOBIG), -1);
		str++;
	}
	return ((int)nbr);
}

int	ft_data_init(t_data *data, char **argv)
{
	if (arg_checker(argv))
		return (1);
	data->n_philos = ft_atoi(argv[1]);
	data->t2die = ft_atoi(argv[2]);
	data->t2eat = ft_atoi(argv[3]);
	data->t2sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->req_meals = ft_atoi(argv[5]);
	else
		data->req_meals = -42;
	if (data->n_philos <= 0 || data->t2die < 0 || data->t2eat < 0 || \
	data->t2sleep < 0 || data->req_meals == -1 || data->req_meals == 0)
		return (1);
	data->forks_mtx = (pthread_mutex_t *)malloc(data->n_philos \
	* sizeof(pthread_mutex_t));
	if (!data->forks_mtx)
		return (1);
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (free(data->forks_mtx), 1);
	memset(data->philos, 0, (data->n_philos * sizeof(t_philo)));
	return (0);
}

int	ft_mutex_thread_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (ft_mutex_destroyer(data, 1, 0), 1);
	while (++i < data->n_philos)
		if (pthread_mutex_init(&data->forks_mtx[i], NULL))
			return (ft_mutex_destroyer(data, 3, i), 1);
	i = -1;
	while (++i < data->n_philos)
		if (pthread_mutex_init(&data->philos[i].philo_mtx, NULL))
			return (ft_mutex_destroyer(data, 4, i), 1);
	data->start_time = ft_gettime_ms();
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (pthread_create(&data->philos[i].thid, NULL, &ft_philo_loop, \
		&(data->philos[i])))
			return (ft_join_threads(data, i), 1);
	}
	return (0);
}
