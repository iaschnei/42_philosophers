/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:07:07 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 11:15:16 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_global_data *data)
{
	size_t			iter;

	iter = 0;
	while (iter < data->number_of_threads)
	{
		if (pthread_create(&data->philo_data_list->thread, NULL,
				thread_start, data->philo_data_list) != 0)
			return (empty_data(data), 0);
		iter++;
		data->philo_data_list = data->philo_data_list->next;
	}
	data->philo_data_list = data->philo_list_head;
	return (1);
}

void	*thread_start(void *data)
{
	t_philo_data	*p_data;

	p_data = (t_philo_data *)data;
	if (p_data->index_in_list % 2 == 0)
		usleep(200);
	p_data->time_since_meal = 0;
	while (1)
	{
		if (eating_subroutine(p_data) == 1)
			break ;
		if (sleeping_subroutine(p_data) == 1)
			break ;
		print_message(4, p_data);
	}
	return (0);
}
