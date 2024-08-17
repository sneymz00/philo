/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_th.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:25:57 by camurill          #+#    #+#             */
/*   Updated: 2024/08/05 13:42:30 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_thread(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_ready))
		;
}

bool	all_thread_ready(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	aux;

	aux = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		aux = true;
	safe_mutex(mutex, UNLOCK);
	return (aux);
}

void	increase_long(t_mutex *mutex, long	*threads_nbr)
{
	safe_mutex(mutex, LOCK);
	(*threads_nbr)++;
	safe_mutex(mutex, UNLOCK);
}
