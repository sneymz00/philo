/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:53:06 by camurill          #+#    #+#             */
/*   Updated: 2024/08/06 14:29:53 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_ready_nbr);
	write_situation(TAKE_R_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_thread_ready(&table->table_mutex, &table->threads_ready_nbr,
			table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philos_dead(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->time_to_end, true);
				write_situation(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal,
		gettime(MILISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_ready_nbr);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_situation(SLEEPING, philo);
		usec_sleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread(&table->philos[0].thread_id, one_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	safe_thread(&table->monitor, monitor_dinner, table, CREATE);
	table->time_to_start = gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->all_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->time_to_end, true);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}
