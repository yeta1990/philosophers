/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:46:35 by albgarci          #+#    #+#             */
/*   Updated: 2022/01/30 19:43:58 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	timestamp_to_ms(struct timeval *tstamp)
{
	return (tstamp->tv_sec * 1000 + tstamp->tv_usec / 1000);
}

void	replicate_usleep(int target_time, int time_corrector, t_philo *p)
{
	struct timeval	timestamp;
	int				finish;

	timestamp.tv_usec = 0;
	timestamp.tv_sec = 0;
	gettimeofday(&timestamp, NULL);
	finish = timestamp_to_ms(&timestamp) + target_time;
	while (timestamp_to_ms(&timestamp) < finish)
	{
		check_starving(p);	
		gettimeofday(&timestamp, NULL);
		usleep(time_corrector);
	}
}

int	elapsed_time(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (timestamp_to_ms(&end) - timestamp_to_ms(start));
}
