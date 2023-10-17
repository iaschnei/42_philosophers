/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:16:42 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 11:24:46 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_global_data	*data;

	if (ac != 5 && ac != 6)
		return (write(2, "Invalid number of args.\n", 24), 1);
	if (!valid_numbers_in_av(av))
		return (write(2, "Invalid argument(s).\n", 21), 2);
	data = initialise_global_data(ac, av);
	if (!data)
		return (write(2, "Alloc error.\n", 13), 2);
	pthread_mutex_lock(&data->mutex_timer);
	data->begin_timer = get_time_in_ms();
	data->timer = get_time_in_ms() - data->begin_timer;
	pthread_mutex_unlock(&data->mutex_timer);
	if (!create_threads(data))
		return (write(2, "Thread creation failed.\n", 24), 3);
	wait_threads(data);
	empty_data(data);
	return (0);
}
