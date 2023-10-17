/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:20:20 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 11:00:23 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(int type, t_philo_data *data)
{
	if (is_over(data))
		return ;
	pthread_mutex_lock(&data->global_data->mutex_timer);
	if (type == 1)
	{
		printf("%zu %zu has taken a fork\n",
			data->global_data->timer, data->index_in_list);
	}
	else if (type == 2)
	{
		printf("%zu %zu is eating\n",
			data->global_data->timer, data->index_in_list);
	}
	else if (type == 3)
	{
		printf("%zu %zu is sleeping\n",
			data->global_data->timer, data->index_in_list);
	}
	else if (type == 4)
	{
		printf("%zu %zu is thinking\n",
			data->global_data->timer, data->index_in_list);
	}
	pthread_mutex_unlock(&data->global_data->mutex_timer);
}
