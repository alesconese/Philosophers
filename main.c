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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	debug(t_philo *philo)
{
	size_t current_time;

	pthread_mutex_lock(&philo->data->print_mtx);
	current_time = get_current_time() - philo->data->start_time;
	printf ("%zu ", current_time);
	printf("hola soy el filo ");
	printf("%d\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

int	ft_atoi(char *str)
{
	long	nbr = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		if (nbr > 2147483647)
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			return(-1);
		}
		str++;
	}
	return ((int)nbr);
}
//check arguments are numbers, positive and smaller than INT_MAX
int	arg_checker(char **argv)
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
				return(EXIT_FAILURE);
			}
			j++;
		}
		if (j > 9)
		{
			printf("ERROR: arguments cannot be higher than 2147483647\n");
			return(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

void	*philo_loop(void *philo_void)
{
	t_philo	*philo = (t_philo *)philo_void;

	debug(philo);

	//TRY TO LOCK L & R FORKS
	//SET last_meal WHEN BOTH FORKS ARE LOCKED
	//PRINT EATING MSG
	//WAIT FOR t2eat
	//UNLOCK FORKS
	//PRINT SLEEPING MSG
	//WAIT FOR t2sleep
	//PRINT THINKING MSG

	return (NULL);
}

int	data_init(t_data *data, char **argv)
{
	int	i;

	i = -1;
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

	//init threads & mutexes
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (1);//TODO: destroy func
	data->forks_mtx = (pthread_mutex_t *)malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks_mtx)
		return (1);//TODO: destroy func
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);//TODO: destroy func
	data->start_time = get_current_time();
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks_mtx[i], NULL))
			return (1);//TODO: destroy func
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		if (pthread_create(&data->philos[i].thid, NULL, &philo_loop, &(data->philos[i])))
			return (1);//TODO: destroy func		
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Wrong arguments. Corrrect format is {./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (OPT)[number_of_times_each_philosopher_must_eat]}\n");
		return(EXIT_FAILURE);
	}

	//DATA INIT
	//init data struct
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(MALLOC_ERROR);
	memset(data, 0, sizeof(t_data));
	if (data_init(data, argv))
		return (free(data), 1);

	//MONITOR LOOP
	while (!data->dead)	
	{
		i = 0;
		while (i < data->n_philos)
		{
			if ((get_current_time() - data->start_time) > (data->philos[i].last_meal + data->t2die))
			{
				pthread_mutex_lock(&data->print_mtx);
				printf ("%zu %d", get_current_time() - data->start_time, data->philos[i].id);
				printf (" has died\n");
				pthread_mutex_unlock(&data->print_mtx);
				data->dead = 1;
				break ;
			}
			i++;
		}
	}

	//CLEANUP
	i = 0;
	while(i < data->n_philos)
	{
		pthread_join(data->philos[i].thid, NULL);
		pthread_mutex_destroy(&data->forks_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mtx);
	free(data->philos);
	free(data->forks_mtx);
	free (data);
	return (0);
}
