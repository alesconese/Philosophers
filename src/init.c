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

//check arguments are numbers, positive and smaller than INT_MAX
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
			{
				printf("ERROR: arguments must be numerical AND positive\n");
				return (EXIT_FAILURE);
			}
			j++;
		}
		if (j > 9)
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			return (EXIT_FAILURE);
		}
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
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			return (-1);
		}
		str++;
	}
	return ((int)nbr);
}

static int	thread_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (1);//TODO: destroy func
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (1);//TODO: destroy func
	if (pthread_mutex_init(&data->meals_mtx, NULL))
		return (1);//TODO: destroy func
	data->forks_mtx = (pthread_mutex_t *)malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks_mtx)
		return (1);//TODO: destroy func
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);//TODO: destroy func
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks_mtx[i], NULL))
			return (1);//TODO: destroy func
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		if (pthread_create(&data->philos[i].thid, NULL, &philo_loop, &(data->philos[i])))
			return (pthread_join(data, i - 1), 1);
	}
	return (0);
}

int	data_init(t_data *data, char **argv)
{
	if (arg_checker(argv))
		return (1);
	//store arguments in data struct
	data->n_philos = ft_atoi(argv[1]);
	data->t2die = ft_atoi(argv[2]);
	data->t2eat = ft_atoi(argv[3]);
	data->t2sleep = ft_atoi(argv[4]);
	if (data->n_philos < 0 || data->t2die < 0 || data->t2eat < 0 || data->t2sleep < 0)
		return (1);
	if (argv[5])
	{
		data->req_meals = ft_atoi(argv[5]);
		if (data->req_meals < 0)
			return (1);
	}
	else
		data->req_meals = -1;	
	data->start_time = get_current_time_ms();
	if (thread_mutex_init(data))
		return (1);
	return (0);
}
