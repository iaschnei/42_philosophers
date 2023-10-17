/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:44:48 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 11:02:02 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleeping_subroutine(t_philo_data *data)
{
	print_message(3, data);
	ft_usleep(data, data->global_data->time_to_sleep);
	if (dead_check(data) || is_over(data))
		return (1);
	return (0);
}

void	ft_usleep(t_philo_data *data, size_t delay)
{
	size_t	end;

	end = get_time_in_ms() + delay;
	while (end > get_time_in_ms())
	{
		usleep(500);
		if (dead_check(data) || is_over(data))
			break ;
	}
}
