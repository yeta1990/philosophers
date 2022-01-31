/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:38:33 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 17:39:01 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_data *data)
{
	int		i;
	t_philo	*aux;

	i = 0;
	aux = *data->list;
	gettimeofday(&data->start, NULL);
	while (i < data->num_philos)
	{
		pthread_create(&aux->thread, NULL, &routine, (void *) aux);
		aux = aux->next;
		i++;
	}
	i = 0;
	aux = *data->list;
	while (data->any_death == 0)
		check_starving(*data->list);
	while (i < data->num_philos)
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
	while (i < data->num_philos)
	{
		pthread_mutex_init(&p->right_fork->m, NULL);
		pthread_mutex_init(&p->philo_lock, NULL);
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
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&p->right_fork->m);
		pthread_mutex_destroy(&p->philo_lock);
		p = p->next;
		i++;
	}
}
