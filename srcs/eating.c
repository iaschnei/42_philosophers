/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:45:32 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/03 10:01:15 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	wait_eat(t_philo_data *data);
static void	wait_fork(t_philo_data *data, size_t fork_index);
static void	close_fork(t_philo_data *data, size_t fork_index);

int	eating_subroutine(t_philo_data *data)
{
	size_t	left_fork_index;
	size_t	right_fork_index;

	if (data->index_in_list == 1)
		left_fork_index = data->global_data->number_of_threads - 1;
	else
		left_fork_index = data->index_in_list - 2;
	right_fork_index = data->index_in_list - 1;
	wait_fork(data, left_fork_index);
	wait_fork(data, right_fork_index);
	wait_eat(data);
	pthread_mutex_lock(&data->global_data->mutex_done);
	if (data->meal_counter == data->global_data->number_of_meals)
		data->global_data->done_eating++;
	pthread_mutex_unlock(&data->global_data->mutex_done);
	close_fork(data, left_fork_index);
	close_fork(data, right_fork_index);
	if (dead_check(data) || is_over(data))
		return (1);
	return (0);
}

static void	wait_eat(t_philo_data *data)
{
	pthread_mutex_lock(&data->global_data->mutex_timer);
	data->time_since_meal = data->global_data->timer;
	pthread_mutex_unlock(&data->global_data->mutex_timer);
	data->meal_counter++;
	print_message(2, data);
	ft_usleep(data, data->global_data->time_to_eat);
	if (dead_check(data) || is_over(data))
		return ;
}

static void	wait_fork(t_philo_data *data, size_t fork_index)
{
	while (1)
	{
		if (dead_check(data) || is_over(data))
			return ;
		pthread_mutex_lock(&data->global_data->forks_array[fork_index]);
		if (data->global_data->forks_status[fork_index] == 0)
		{
			data->global_data->forks_status[fork_index] = 1;
			pthread_mutex_unlock(&data->global_data->forks_array[fork_index]);
			break ;
		}
		pthread_mutex_unlock(&data->global_data->forks_array[fork_index]);
		ft_usleep(data, 1);
	}
	print_message(1, data);
}

static void	close_fork(t_philo_data *data, size_t fork_index)
{
	pthread_mutex_lock(&data->global_data->forks_array[fork_index]);
	data->global_data->forks_status[fork_index] = 0;
	pthread_mutex_unlock(&data->global_data->forks_array[fork_index]);
}
