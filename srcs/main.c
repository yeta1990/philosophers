/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:05:25 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 18:44:27 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philosophers number_of_philo time_to_die ");
		printf("time_to_eat time_to_sleep [meals_per_philo]\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (fill_data(argc, argv, data) == -1)
	{
		printf("Wrong parameters\n");
		free(data);
		return (1);
	}
	pthread_mutex_init(&data->mutex, NULL);
	init_all_mutex(data);
	start_threads(data);
	destroy_all_mutex(data);
	pthread_mutex_destroy(&data->mutex);
	free_data(data);
}

void	waiter(t_philo *p, int meals_per_philo, int *i)
{
	if (meals_per_philo != -1)
	{
		if (p->total_meals >= meals_per_philo)
			(*i)++;
		else
			*i = 0;
		if (*i >= p->data->num_philos)
		{
			p->data->satisfied_guests = 1;
			p->data->any_death = 1;
		}
	}
}

void	check_starving(t_philo *philo)
{
	t_philo	*p;
	int		i;
	int		meals_per_philo;

	i = 0;
	p = philo;
	meals_per_philo = philo->data->meals_per_philo;
	while (p->data->any_death == 0 && p->data->satisfied_guests == 0)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (p->data->any_death == 0 && p->am_i_dead == 0
			&& elapsed_time(&p->last_meal_timestamp) > p->data->time_to_die)
		{
			p->am_i_dead = 1;
			p->data->any_death = philo->id;
			printf("%i %i died\n", elapsed_time(&p->start_time), p->id);
		}
		waiter(p, meals_per_philo, &i);
		pthread_mutex_unlock(&philo->data->mutex);
		p = p->next;
	}
}

int	fill_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
			return (-1);
		i++;
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_per_philo = -1;
	data->any_death = 0;
	data->satisfied_guests = 0;
	data->list = malloc(sizeof(t_philo *));
	*data->list = 0;
	create_philos(data);
	if (argc == 6)
		data->meals_per_philo = ft_atoi(argv[5]);
	return (0);
}
