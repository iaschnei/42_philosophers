/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:46:23 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/20 10:32:01 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	destroy_mutexes(t_global_data *data, size_t forks_size);

void	empty_data(t_global_data *data)
{
	data->philo_data_list = data->philo_list_head;
	free_list(&(data->philo_data_list));
	destroy_mutexes(data, data->number_of_threads - 1);
	free(data->forks_array);
	free(data->forks_status);
	free(data);
}

static void	destroy_mutexes(t_global_data *data, size_t forks_size)
{
	while (forks_size > 0)
	{
		pthread_mutex_destroy(&(data->forks_array[forks_size]));
		forks_size--;
	}
	pthread_mutex_destroy(&(data->mutex_dead));
	pthread_mutex_destroy(&(data->mutex_done));
}

void	free_list(t_philo_data **list)
{
	t_philo_data	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free (tmp);
	}
}
