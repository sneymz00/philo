/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:52 by camurill          #+#    #+#             */
/*   Updated: 2024/08/06 20:48:41 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	gettime(t_time_code time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_message("Get time of day failed");
	if (SECOND == time)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND == time)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_message("Error input gettime");
	return (1500);
}

/***sleep***/

void	usec_sleep(long usec, t_table *table)
{
	long	start;
	long	lapso;
	long	ret;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		lapso = gettime(MICROSECOND) - start;
		ret = usec - lapso;
		if (ret > 1e3)
			usleep(ret / 2);
		else
		{
			while (gettime(MICROSECOND) - start)
				;
		}
	}
}
