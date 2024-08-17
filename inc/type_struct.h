/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:46:19 by camurill          #+#    #+#             */
/*   Updated: 2024/08/05 12:18:05 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_STRUCT_H
# define TYPE_STRUCT_H

# include "philo.h"
# include "enum.h"

/***DEFINE***/
typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

/***FORK***/
typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}			t_fork;

/***PHILO***/
typedef struct s_philo
{
	int			id;
	long		meals_eaten;
	long		last_meal;
	bool		full;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	thread_id;
	t_mutex		philo_mutex;
	t_table		*table;
}				t_philo;

/***TABLE***/
struct	s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_start;
	bool		time_to_end;
	bool		all_ready;
	long		limit_meals;
	long		threads_ready_nbr;
	pthread_t	monitor;
	t_mutex		write_mutex;
	t_mutex		table_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

#endif