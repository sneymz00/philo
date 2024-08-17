/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:11:18 by camurill          #+#    #+#             */
/*   Updated: 2024/07/31 13:10:25 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//BOOL
void	set_bool(t_mutex *mutex, bool *sts, bool val)
{
	safe_mutex(mutex, LOCK);
	*sts = val;
	safe_mutex(mutex, UNLOCK);
}

//BOOL direction
bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	aux;

	safe_mutex(mutex, LOCK);
	aux = *value;
	safe_mutex(mutex, UNLOCK);
	return (aux);
}

//LONG
long	get_long(t_mutex *mutex, long *value)
{
	long	fin;

	safe_mutex(mutex, LOCK);
	fin = *value;
	safe_mutex(mutex, UNLOCK);
	return (fin);
}

void	set_long(t_mutex *mutex, long *dst, long value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->time_to_end));
}
