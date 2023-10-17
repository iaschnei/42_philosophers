/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:21:37 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/03 09:51:41 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_SIZE 4294967295

struct	s_philo_data;

typedef struct s_global_data
{
	size_t				begin_timer;
	size_t				timer;
	pthread_mutex_t		mutex_timer;
	size_t				number_of_threads;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				number_of_meals;
	pthread_mutex_t		*forks_array;
	size_t				*forks_status;
	size_t				is_one_dead;
	pthread_mutex_t		mutex_dead;
	size_t				done_eating;
	pthread_mutex_t		mutex_done;
	struct s_philo_data	*philo_data_list;
	struct s_philo_data	*philo_list_head;
}				t_global_data;

typedef struct s_philo_data
{
	size_t				time_since_meal;
	size_t				meal_counter;
	size_t				index_in_list;
	pthread_t			thread;
	struct s_philo_data	*next;
	t_global_data		*global_data;
}				t_philo_data;

// -------- PARSING -------
int				valid_numbers_in_av(char **av);
size_t			ft_atoi(char *string);
size_t			get_time_in_ms(void);

// -------- INITIALISE DATA -------
t_global_data	*initialise_global_data(int ac, char **av);

// ------- CREATE THREADS -------
int				create_threads(t_global_data *data);
void			*thread_start(void *data);
void			wait_threads(t_global_data *data);

// ------- EATING -------
int				eating_subroutine(t_philo_data *data);

// ------- SLEEPING -------
int				sleeping_subroutine(t_philo_data *data);
void			ft_usleep(t_philo_data *data, size_t delay);

// ------- CHECKS -------
int				dead_check(t_philo_data *data);
int				is_over(t_philo_data *data);

// ------- MESSAGES -------
void			print_message(int type, t_philo_data *data);

// -------- CLEANUP -------
void			empty_data(t_global_data *data);
void			free_list(t_philo_data **list);

// -------- DEBUG -------
void			debug_print_data(t_global_data *data);

#endif
