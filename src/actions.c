/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:10:03 by camurill          #+#    #+#             */
/*   Updated: 2024/08/06 14:27:41 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
	safe_mutex(&philo->r_fork->fork, LOCK);
	write_situation(TAKE_R_FORK, philo);
	safe_mutex(&philo->l_fork->fork, LOCK);
	write_situation(TAKE_L_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILISECOND));
	philo->meals_eaten++;
	write_situation(EATING, philo);
	usec_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->table->limit_meals == philo->meals_eaten)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->r_fork->fork, UNLOCK);
	safe_mutex(&philo->l_fork->fork, UNLOCK);
}

void	thinking(t_philo *philo)
{
	write_situation(THINKING, philo);
}

bool	philos_dead(t_philo	*philos)
{
	long	lapso;
	long	t_die;

	if (get_bool(&philos->philo_mutex, &philos->full))
		return (false);
	lapso = gettime(MILISECOND)
		- get_long(&philos->philo_mutex, &philos->last_meal);
	t_die = philos->table->time_to_die / 1e3;
	if (lapso > t_die)
		return (true);
	return (false);
}

void	write_situation(t_status status, t_philo *philo)
{
	long	lapso;

	lapso = gettime(MILISECOND) - philo->table->time_to_start;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_R_FORK || status == TAKE_L_FORK)
		&& !simulation_finished(philo->table))
		printf(CYAN "%zu %d has taken a fork\n" GBD, lapso, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(GREEN "%zu %d is eating\n" GBD, lapso, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(BLUE "%zu %d is sleeping\n" GBD, lapso, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(YELLOW "%zu %d is thinking\n" GBD, lapso, philo->id);
	else if (status == DIED)
		printf(RED "%zu %d is died\n" GBD, lapso, philo->id);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
