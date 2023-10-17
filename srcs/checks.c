/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:13:21 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 11:00:32 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	join_threads(t_global_data *data);

int	dead_check(t_philo_data *data)
{
	pthread_mutex_lock(&data->global_data->mutex_timer);
	if (data->global_data->timer - data->time_since_meal
		> data->global_data->time_to_die)
	{
		pthread_mutex_unlock(&data->global_data->mutex_timer);
		pthread_mutex_lock(&data->global_data->mutex_dead);
		if (data->global_data->is_one_dead == 0)
		{
			data->global_data->is_one_dead = 1;
			pthread_mutex_lock(&data->global_data->mutex_timer);
			printf("%zu %zu died\n", data->global_data->timer,
				data->index_in_list);
			pthread_mutex_unlock(&data->global_data->mutex_timer);
		}
		pthread_mutex_unlock(&data->global_data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->global_data->mutex_timer);
	return (0);
}

void	wait_threads(t_global_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_timer);
		data->timer = get_time_in_ms() - data->begin_timer;
		pthread_mutex_unlock(&data->mutex_timer);
		pthread_mutex_lock(&data->mutex_dead);
		if (data->is_one_dead)
		{
			pthread_mutex_unlock(&data->mutex_dead);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&data->mutex_done);
		if (data->done_eating == data->number_of_threads)
		{
			pthread_mutex_unlock(&data->mutex_done);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_done);
		usleep(1000);
	}
	data->philo_data_list = data->philo_list_head;
	join_threads(data);
}

static void	join_threads(t_global_data *data)
{
	size_t	iter;

	iter = 0;
	while (iter < data->number_of_threads)
	{
		pthread_join(data->philo_data_list->thread, NULL);
		iter++;
		data->philo_data_list = data->philo_data_list->next;
	}
}

int	is_over(t_philo_data *data)
{
	pthread_mutex_lock(&data->global_data->mutex_dead);
	if (data->global_data->is_one_dead)
	{
		pthread_mutex_unlock(&data->global_data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->global_data->mutex_dead);
	pthread_mutex_lock(&data->global_data->mutex_done);
	if (data->global_data->done_eating == data->global_data->number_of_threads)
	{
		pthread_mutex_unlock(&data->global_data->mutex_done);
		return (1);
	}
	pthread_mutex_unlock(&data->global_data->mutex_done);
	return (0);
}
