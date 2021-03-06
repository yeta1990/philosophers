/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:02:57 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/31 18:49:52 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_time_val_64
{
	uint64_t	tv_usec;
	uint64_t	tv_sec;
}	t_time_val_64;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_per_philo;
	int				satisfied_guests;
	int				any_death;
	struct s_philo	**list;
	pthread_mutex_t	mutex;
	struct timeval	start;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	m;
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
	pthread_t		thread;
	struct s_philo	*next;
	int				last_meal;
	int				total_meals;
	t_data			*data;
	struct timeval	start_time;
	struct timeval	last_meal_timestamp;
	int				am_i_dead;
	pthread_mutex_t	philo_lock;
}	t_philo;

int		ft_atoi(const char *str);
int		fill_data(int argc, char **argv, t_data *data);
void	print_input_data(t_data *data);
void	create_philos(t_data *data);
void	add_to_philo_list(t_philo *p, t_philo **list);
void	check_starving(t_philo *p);

//freezers.c
void	free_data(t_data *d);
void	free_philos(int num_of_philos, t_philo **list);

void	*routine(void *p);

//time_utils.c
int		timestamp_to_ms(struct timeval *tstamp);
void	replicate_usleep(int target_time, int time_corrector, t_philo *p);
int		elapsed_time(struct timeval *start);
void	init_all_mutex(t_data *data);
void	destroy_all_mutex(t_data *data);
void	start_threads(t_data *data);

#endif
