/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:02:57 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/28 17:30:59 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_per_philo;
	struct s_philo	**list;
}	t_data;

typedef struct s_fork
{
	int				id;
	int				available;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				current_action;
	int				alive;
	struct s_fork	*left_fork;
	struct s_fork	*right_fork;
	pthread_t 		thread;
	struct s_philo	*next;
}	t_philo;

int		ft_atoi(const char *str);
int		fill_data(int argc, char **argv, t_data *data);
void	print_input_data(t_data *data);
void	create_philos(t_data *data);
void	add_to_philo_list(t_philo *p, t_philo **list);

//freezers.c
void	free_data(t_data *d);
void	free_philos(int num_of_philos, t_philo **list);
