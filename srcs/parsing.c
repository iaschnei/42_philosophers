/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:28:18 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/15 14:21:10 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Checks that args are only number between 1 and MAX_SIZE
// Returns 0 if that's not the case 
int	valid_numbers_in_av(char **av)
{
	int	arg_iter;
	int	let_iter;

	arg_iter = 1;
	while (av[arg_iter])
	{
		let_iter = 0;
		while (av[arg_iter][let_iter])
		{
			if (av[arg_iter][let_iter] < '0' || av[arg_iter][let_iter] > '9')
				return (0);
			let_iter++;
		}
		if (ft_atoi(av[arg_iter]) > MAX_SIZE || ft_atoi(av[arg_iter]) == 0)
			return (0);
		arg_iter++;
	}
	return (1);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time_struct;
	size_t			ret;

	gettimeofday(&time_struct, NULL);
	ret = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (ret);
}

size_t	ft_atoi(char *string)
{
	size_t	iter;
	size_t	ret;

	iter = 0;
	ret = 0;
	while (string[iter])
	{
		ret = ret * 10 + (string[iter] - '0');
		iter++;
	}
	return (ret);
}
