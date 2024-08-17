/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:14:23 by camurill          #+#    #+#             */
/*   Updated: 2024/08/06 14:19:49 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_message(const char *error)
{
	printf("Error found: %s\n", error);
	exit(1);
}

void	clean_table(t_table	*table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&table->write_mutex, DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

int	main(int ac, char **ag)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_message("Need 4-5 arguments");
	if (atoi(ag[1]) > 200)
		error_message("Need unless 200 philosophers");
	possible_start(&table, ag);
	data_init(&table);
	dinner_start(&table);
	clean_table(&table);
	return (0);
}
