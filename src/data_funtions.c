/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_funtions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:47:11 by camurill          #+#    #+#             */
/*   Updated: 2024/07/30 16:06:57 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/***malloc safes***/
void	*safe_malloc(size_t	bytes)
{
	void	*aux;

	aux = malloc(bytes);
	if (!aux)
		error_message("Error with mallocs");
	return (aux);
}

/***MUTEX***/

static	void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_message("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_message("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_message("The current thread already owns the mutex");
	else if (status == EPERM)
		error_message("The current thread does not own the mutex");
	else if (status == ENOMEM)
		error_message("The procces cannot allocate enought memory");
	else if (status == EAGAIN)
		error_message("The max nbr of recursive lock for mutex is exceeded");
	else if (status == EBUSY)
		error_message("Mutex is locked");
}

/***mutex saves***/
void	safe_mutex(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_message("Problems with mutex");
}

/***thread saves***/
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (EAGAIN == status)
		error_message("No recourses to create a thread");
	else if (status == EPERM)
		error_message("No permission to set the scheduling policy");
	else if (status == EINVAL && CREATE == opcode)
		error_message("The value specified by attr is invalid");
	else if (status == EINVAL && (JOIN == opcode || opcode == DETACH))
		error_message("The value specified by thread is not joinable");
	else if (status == ESRCH)
		error_message("No thread could be found corresponding to that");
	else if (status == EDEADLK)
		error_message("A deadlock was detected");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_message("Wrong opcode thread handle");
}
