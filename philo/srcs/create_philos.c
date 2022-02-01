/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:05:02 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 18:12:25 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*fill_fields(int i, t_fork **aux_fork, t_data *data)
{
	t_philo	*p;
	t_fork	*f;

	p = malloc(sizeof(t_philo));
	f = malloc(sizeof(t_fork));
	f->id = i + 1;
	f->available = 1;
	p->id = i + 1;
	p->current_action = 0;
	p->alive = 1;
	p->left_fork = *aux_fork;
	p->right_fork = f;
	*aux_fork = f;
	p->next = 0;
	p->last_meal = 0;
	p->total_meals = 0;
	p->last_meal_timestamp.tv_sec = 0;
	p->last_meal_timestamp.tv_usec = 0;
	p->am_i_dead = 0;
	p->data = data;
	return (p);
}

void	create_philos(t_data *data)
{
	t_philo	*first;
	t_philo	*last;
	int		i;
	t_fork	*aux_fork;
	t_philo	*p;

	i = 0;
	first = 0;
	last = 0;
	p = 0;
	aux_fork = 0;
	while (i < data->num_philos)
	{
		p = fill_fields(i, &aux_fork, data);
		add_to_philo_list(p, data->list);
		if (i == 0)
			first = p;
		if (i == data->num_philos - 1)
			last = p;
		p = 0;
		i++;
	}
	first->left_fork = aux_fork;
	last->next = first;
}

void	add_to_philo_list(t_philo *p, t_philo **list)
{
	t_philo	*aux;

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
