/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:42:30 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 18:57:55 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	left_handed_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->m);
	if (philo->data->any_death == 0)
		printf("%i %i has taken a fork (left)\n",
			elapsed_time(&philo->start_time), philo->id);
	pthread_mutex_lock(&philo->right_fork->m);
	if (philo->data->any_death == 0)
		printf("%i %i has taken a fork (right)\n",
			elapsed_time(&philo->start_time), philo->id);
}

void	right_handed_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->m);
	if (philo->data->any_death == 0)
		printf("%i %i has taken a fork (right)\n",
			elapsed_time(&philo->start_time), philo->id);
	if (philo->data->num_philos > 1)
	{
		pthread_mutex_lock(&philo->left_fork->m);
		if (philo->data->any_death == 0)
			printf("%i %i has taken a fork (left)\n",
				elapsed_time(&philo->start_time), philo->id);
	}
}

void	eat_eat(t_philo *philo)
{
	if (philo->data->any_death == 0)
	{
		printf("%i %i is eating\n", elapsed_time(&philo->start_time),
			philo->id);
		gettimeofday(&philo->last_meal_timestamp, NULL);
	}
	if (philo->data->any_death == 0)
	{
		philo->total_meals++;
		replicate_usleep(philo->data->time_to_eat, philo->data->num_philos,
			philo);
	}
	pthread_mutex_unlock(&philo->left_fork->m);
	pthread_mutex_unlock(&philo->right_fork->m);
	pthread_mutex_unlock(&philo->philo_lock);
	if (philo->data->any_death == 0)
		printf("%i %i is sleeping\n", elapsed_time(&philo->start_time),
			philo->id);
	if (philo->data->any_death == 0)
		replicate_usleep(philo->data->time_to_eat, philo->data->num_philos,
			philo);
	if (philo->data->any_death == 0)
		printf("%i %i is thinking\n", elapsed_time(&philo->start_time),
			philo->id);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = p;
	gettimeofday(&philo->start_time, NULL);
	gettimeofday(&philo->last_meal_timestamp, NULL);
	while (philo->am_i_dead == 0 && philo->data->any_death == 0)
	{
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->id % 2 == 0)
			left_handed_routine(philo);
		else
			right_handed_routine(philo);
		if (philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->right_fork->m);
			pthread_mutex_unlock(&philo->philo_lock);
			break ;
		}
		eat_eat(philo);
	}
	return (0);
}
