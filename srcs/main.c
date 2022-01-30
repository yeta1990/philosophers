/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:05:25 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/30 13:42:15 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	replicate_usleep(int target_time)
{
	struct timeval	start;
	struct timeval	end;

	end.tv_usec = 0;
	end.tv_sec = 0;
	start.tv_usec = 0;
	start.tv_sec = 0;
	gettimeofday(&start, NULL);
	while (end.tv_usec - start.tv_usec < target_time)
	{
		usleep(10);
		gettimeofday(&end, NULL);
	}
	return (target_time);
}

long time_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_usec - start->tv_usec) / 1000.0;
}

void	*routine(void *p)
{
	t_philo *philo;
	struct timeval	start;
	struct timeval	end;
	int		final;
	int		forks;

	start.tv_usec = 0;
	start.tv_sec = 0;
	end.tv_usec = 0;
	end.tv_sec = 0;
	final = 0;
	gettimeofday(&start, NULL);
	forks = 0;
	philo = p;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->m);
		gettimeofday(&end, NULL);
		printf("[%li] - ID %i, i've taken the left fork %i\n", time_diff(&start, &end), philo->id, philo->left_fork->id);
		pthread_mutex_lock(&philo->right_fork->m);
		gettimeofday(&end, NULL);
		printf("[%li] - ID %i, i've taken the right fork %i\n", time_diff(&start, &end), philo->id, philo->right_fork->id);
		printf("[%li] - ID %i, eating\n", time_diff(&start, &end), philo->id);
		replicate_usleep(philo->data->time_to_eat * 1000);
	//	usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork->m);
		pthread_mutex_unlock(&philo->right_fork->m);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->m);
		gettimeofday(&end, NULL);
		printf("[%li] - ID %i, i've taken the right fork %i\n", time_diff(&start, &end), philo->id, philo->right_fork->id);

		pthread_mutex_lock(&philo->left_fork->m);

		gettimeofday(&end, NULL);
		printf("[%li] - ID %i, i've taken the left fork %i\n", time_diff(&start, &end), philo->id, philo->left_fork->id);
		printf("[%li] - ID %i, eating\n", time_diff(&start, &end), philo->id);
		final += replicate_usleep(philo->data->time_to_eat * 1000);
//		usleep(philo->data->time_to_eat * 1000);
		
		pthread_mutex_unlock(&philo->right_fork->m);
		pthread_mutex_unlock(&philo->left_fork->m);
	}
	gettimeofday(&end, NULL);

	printf("[%li] - ID %i, sleeping\n", time_diff(&start, &end), philo->id);

	replicate_usleep(philo->data->time_to_sleep * 1000);
//	usleep(philo->data->time_to_sleep * 1000);

	gettimeofday(&end, NULL);
	printf("[%li] - ID %i, thinking\n", time_diff(&start, &end), philo->id);

	return 0;
}

void	start_threads(t_data *data)
{
	int		i;
	t_philo	*aux;

	i = 0;
	aux = *data->list;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&aux->thread, NULL, &routine, (void *) aux);
		aux = aux->next;
		i++;
	}
	i = 0;
	aux = *data->list;
	while (i < data->number_of_philosophers)
	{
		pthread_join(aux->thread, NULL);
		aux = aux->next;
		i++;
	}
}
void	init_all_mutex(t_data *data)
{
	t_philo	*p;
	int		i;

	i = 0;
	p = *data->list;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&p->right_fork->m, NULL);
		p = p->next;
		i++;
	}
}

void	destroy_all_mutex(t_data *data)
{
	t_philo	*p;
	int		i;

	i = 0;
	p = *data->list;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&p->right_fork->m);
		p = p->next;
		i++;
	}
}

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
//	gettimeofday(&data->start, NULL);
//	pthread_mutex_init(&data->mutex, NULL);
	print_input_data(data);
	init_all_mutex(data);
	printf("\n\n");
	start_threads(data);
//	pthread_mutex_destroy(&data->mutex);

	destroy_all_mutex(data);
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
	t_fork	*f;
	t_fork	*aux_fork;
	int		i;

	i = 0;
	first = 0;
	last = 0;
	p = 0;
	f = 0;
	aux_fork = 0;
	while (i < data->number_of_philosophers)
	{
		p = malloc(sizeof(t_philo));
		f = malloc(sizeof(t_fork));
		f->id = i + 1;
		f->available = 1;
		p->id = i + 1;
		p->current_action = 0;
		p->alive = 1;
		p->left_fork = aux_fork;
		p->right_fork = f;
		aux_fork = f;
		p->next = 0;
		p->last_meal = 0;
		p->num_of_meals = 0;
		p->data = data;
		add_to_philo_list(p, data->list);
		if (i == 0)
			first = p;
		if (i == data->number_of_philosophers - 1)
			last = p;
		p = 0;
		i++;
	}
	first->left_fork = aux_fork;
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
	printf("\033[1;32m==== Philosophers ====\033[0m\n");
	printf("\033[1;37m-= Input data =-\033[0m\n");
	printf("Number of philosophers: \033[1;33m%i\033[0m\n", data->number_of_philosophers);
	printf("Time to die: \033[1;33m%i\033[0m\n", data->time_to_die);
	printf("TIme to eat: \033[1;33m%i\033[0m\n", data->time_to_eat);
	printf("Time to sleep: \033[1;33m%i\033[0m\n", data->time_to_sleep);
	printf("Meals per philo: \033[1;33m%i\033[0m\n\n", data->meals_per_philo);
	printf("\033[1;37m-= Philos at table =-\033[0m\n");
	while (i < data->number_of_philosophers)
	{
		if (i != 0)
			printf(", ");
		printf("%i", aux->id);
		aux = aux->next;
		i++;
	}
}
