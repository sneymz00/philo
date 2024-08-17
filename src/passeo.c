/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:22:13 by camurill          #+#    #+#             */
/*   Updated: 2024/07/31 13:14:00 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	my_atoi(char *ag)
{
	long	nbr;

	nbr = 0;
	while (*ag)
		nbr = (nbr * 10) + (*ag++ - 48);
	return (nbr);
}

/***
 * ./philo [nbr_philo] [time_die] [time_eat] [time_sleep] [nbt_to_eat]
 */

void	possible_start(t_table *table, char **agv)
{
	table->philo_nbr = my_atoi(agv[1]);
	table->time_to_die = my_atoi(agv[2]) * 1e3;
	table->time_to_eat = my_atoi(agv[3]) * 1e3;
	table->time_to_sleep = my_atoi(agv[4]) * 1e3;
	if (table->time_to_die < 1e4
		||table->time_to_eat < 1e4
		||table->time_to_sleep < 1e4)
		error_message("Pls, user timestamp major than 60ms");
	if (agv[5])
		table->limit_meals = my_atoi(agv[5]);
	else
		table->limit_meals = -1;
}
