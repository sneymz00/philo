/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:44:16 by camurill          #+#    #+#             */
/*   Updated: 2024/08/06 13:04:38 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	assing_forks(t_philo *philo, t_fork *forks, int philo_i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->r_fork = &forks[(philo_i + 1) % philo_nbr];
	philo->l_fork = &forks[philo_i];
	if (philo->id % 2 == 0)
	{
		philo->r_fork = &forks[philo_i];
		philo->l_fork = &forks[(philo_i + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo_n;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo_n = table->philos + i;
		philo_n->id = i + 1;
		philo_n->full = false;
		philo_n->meals_eaten = 0;
		philo_n->table = table;
		safe_mutex(&philo_n->philo_mutex, INIT);
		assing_forks(philo_n, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->time_to_end = false;
	table->all_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
