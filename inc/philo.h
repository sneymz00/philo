/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:18:58 by camurill          #+#    #+#             */
/*   Updated: 2024/08/05 13:14:02 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include "enum.h"
# include "type_struct.h"

/***ERROR***/
void	error_message(const char *error);

/**EVENTS***/
void	possible_start(t_table *table, char **arg);
void	data_init(t_table *table);
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);
void	clean_table(t_table *table);

/***AUX_FUNTIONS***/
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex(t_mutex *mutex, t_opcode opcode);
void	*safe_malloc(size_t bytes);
void	usec_sleep(long usec, t_table *table);
long	gettime(t_time_code time);

/***ACTIONS***/
void	eat(t_philo *philo);
void	*monitor_dinner(void *data);
void	thinking(t_philo *philo);
void	*one_philo(void *data);
void	write_situation(t_status status, t_philo *philo);
bool	philos_dead(t_philo	*philos);

/***LIBFT***/
long	my_atoi(char *ag);

/***SET_GET_LONG_BOOL***/
void	set_bool(t_mutex *mutex, bool *sts, bool val);
void	set_long(t_mutex *mutex, long *dst, long val);
bool	get_bool(t_mutex *mutex, bool *value);
bool	simulation_finished(t_table *table);
long	get_long(t_mutex *mutex, long *value);

/***SYNC***/
void	wait_thread(t_table *table);
void	increase_long(t_mutex *mutex, long	*threads_nbr);
bool	all_thread_ready(t_mutex *mutex, long *threads, long philo_nbr);
#endif
