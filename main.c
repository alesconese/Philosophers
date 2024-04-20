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

#include "philo.h"

int	ft_atoi(char *str)
{
	long	nbr = 0;
	while (*str && *str > '0' && *str < '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		if (nbr > 2147483647)
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			exit(EXIT_FAILURE);
		}
		str++;
	}
	return ((int)nbr);
}
//check arguments are numbers, positive and smaller than INT_MAX
void	arg_checker(char **argv)
{
	int	i;
	int j;
	
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("ERROR: arguments must be numerical AND positive\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		if (j > 9)
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	data_init(t_data *data, char **argv)
{
	arg_checker(argv);
	//store arguments in data struct
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_meals = ft_atoi(argv[5]);
	else
		data->n_meals = -1;

	//init philos
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		exit(MALLOC_ERROR);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Wrong arguments. Corrrect format is {./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (OPT)[number_of_times_each_philosopher_must_eat]}\n");
		exit(EXIT_FAILURE);
	}

	//DATA INIT
	//init data struct
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(MALLOC_ERROR);
	memset(data, 0, sizeof(t_data));
	
	data_init(data, argv);
		

	free (data);
	return (0);
}
