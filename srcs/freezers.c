/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freezers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:44:04 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 18:38:25 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *d)
{
	free_philos(d->num_philos, d->list);
	free(d);
}

void	free_philos(int num_of_philos, t_philo **list)
{
	t_philo	*aux;
	t_philo	*next;
	int		i;

	i = 0;
	if (*list)
	{	
		aux = *list;
		while (i < num_of_philos)
		{
			next = aux->next;
			free(aux->right_fork);
			free(aux);
			aux = next;
			i++;
		}
		free(list);
	}
}
