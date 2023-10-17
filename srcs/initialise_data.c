/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:57:12 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/01 16:46:35 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_philo_data	*initialise_philo_data(t_global_data *data);
static void			create_new_philo(t_philo_data **list, size_t index,
						t_global_data *data);
static int			initialise_mutexes(t_global_data *data, size_t forks_size);
static int			initialise_forks(t_global_data *data, size_t forks_size);

// Initialise the global data struct with the args
// and set ending variables to 0 as well as the forks mutex
//* If not defined, number_of_meals is set to 0 !
t_global_data	*initialise_global_data(int ac, char **av)
{
	t_global_data	*data;

	data = malloc(sizeof(t_global_data));
	if (!data)
		return (NULL);
	data->number_of_threads = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = 0;
	data->philo_data_list = initialise_philo_data(data);
	if (!data->philo_data_list)
		return (free(data), NULL);
	data->is_one_dead = 0;
	data->done_eating = 0;
	if (!initialise_forks(data, data->number_of_threads))
		return (free(data), NULL);
	if (!initialise_mutexes(data, data->number_of_threads))
		return (free(data), NULL);
	return (data);
}

// Initialise data philo list 
static t_philo_data	*initialise_philo_data(t_global_data *data)
{
	size_t			new_philo_iter;
	t_philo_data	*ret;

	ret = NULL;
	new_philo_iter = 1;
	while (new_philo_iter <= data->number_of_threads)
	{
		create_new_philo(&ret, new_philo_iter, data);
		if (!ret)
			return (free_list(&ret), NULL);
		new_philo_iter++;
	}
	data->philo_list_head = ret;
	return (ret);
}

// Create a new philo link in the list
static void	create_new_philo(t_philo_data **list, size_t index,
				t_global_data *data)
{
	t_philo_data	*new;
	t_philo_data	*node;

	new = malloc(sizeof(t_philo_data));
	if (!new)
	{
		free_list(list);
		return ;
	}
	new->thread = 0;
	new->time_since_meal = 0;
	new->meal_counter = 0;
	new->index_in_list = index;
	new->global_data = data;
	new->next = NULL;
	if (!list || !*list)
		*list = new;
	else
	{
		node = *list;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

// Initialise all mutexes
// If an initialisation fails, destroy all previous mutexes
static int	initialise_mutexes(t_global_data *data, size_t forks_size)
{
	size_t	iter;

	iter = 0;
	if (pthread_mutex_init(&(data->mutex_timer), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->mutex_dead), NULL) != 0)
		return (pthread_mutex_destroy(&(data->mutex_dead)), 0);
	if (pthread_mutex_init(&(data->mutex_done), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->mutex_dead));
		return (pthread_mutex_destroy(&(data->mutex_timer)), 0);
	}
	while (iter < forks_size)
	{
		if (pthread_mutex_init(&(data->forks_array[iter]), NULL) != 0)
		{
			while (iter-- > 0)
				pthread_mutex_destroy(&(data->forks_array[iter]));
			iter--;
			return (0);
		}
		iter++;
	}
	return (1);
}

static int	initialise_forks(t_global_data *data, size_t forks_size)
{
	data->forks_status = malloc((forks_size + 1) * sizeof(size_t));
	if (!data->forks_status)
		return (0);
	memset(data->forks_status, 0, forks_size * sizeof(size_t));
	data->forks_array = malloc((forks_size * sizeof(pthread_mutex_t)));
	if (!data->forks_array)
		return (free(data->forks_status), 0);
	return (1);
}
