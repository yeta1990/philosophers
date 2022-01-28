/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:05:25 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/28 10:56:07 by albgarci         ###   ########.fr       */
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
		exit(0);
	}
	data = malloc(sizeof(t_data));
	if (fill_data(argc, argv, data) == -1)
	{
		printf("Wrong parameters\n");
		free(data);
		exit(1);
	}
	print_input_data(data);
	free_data(data);
}

int	fill_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while(i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
			return (-1);
		i++;
	}
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_per_philo = -1;
	data->list = malloc(sizeof(t_philo *));
	*data->list = 0;
	create_philos(data);
	if (argc == 6)
		data->meals_per_philo = ft_atoi(argv[5]);
	return (0);
}

void	create_philos(t_data *data)
{
	t_philo *first;
	t_philo *last;
	t_philo *p;
	int		i;

	i = 0;
	first = 0;
	last = 0;
	p = 0;
	while (i < data->number_of_philosophers)
	{
		p = malloc(sizeof(t_philo));
		p->id = i + 1;
		p->current_action = 0;
		p->next = 0;
		add_to_philo_list(p, data->list);
		if (i == 0)
			first = p;
		if (i == data->number_of_philosophers - 1)
			last = p;
		p = 0;
		i++;
	}
	if (i > 1)
		last->next = first;
}

void	add_to_philo_list(t_philo *p, t_philo **list)
{
	t_philo *aux;

	aux = *list;
	if (!aux)
	{
		*list = p;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = p;
}

void	print_input_data(t_data *data)
{
	int		i;
	t_philo	*aux;

	i = 0;
	aux = *data->list;
	printf("Number of philosophers: %i\n", data->number_of_philosophers);
	printf("Time to die: %i\n", data->time_to_die);
	printf("TIme to eat: %i\n", data->time_to_eat);
	printf("Time to sleep: %i\n", data->time_to_sleep);
	printf("Meals per philo: %i\n\n", data->meals_per_philo);
	printf("==== Philos at table ====\n");
	while (i < data->number_of_philosophers)
	{
		printf("id: %i\n", aux->id);
		aux = aux->next;
		i++;
	}
}
