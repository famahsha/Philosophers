/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:50:30 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/18 18:05:30 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_shared {
	int				num_of_philo;
	int				time_to_sleep;
	int				time_to_eat;
	size_t			time_to_die;
	int				totalno_of_eats;
	size_t			start_time;
	int				philo_died;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	mutex_state;
	pthread_mutex_t	*sign_mutex;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	die_mutex;
	int				*sign;
	int				*fork_available;
	struct s_philo	*philo;
}t_shared;

typedef struct s_philo {
	int				id;
	pthread_t		thread_id;
	int				left_fork;
	int				right_fork;
	int				total_eats;
	size_t			last_meal;
	t_shared		*shared;
}t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_error(void);
void	initialize_args(t_shared *shared, char **av);
void	initialize_philo(t_shared *shared);
void	initialize(t_shared *shared);
int		try_aquire_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	*philo_routine(void *args);
int		philosopher_is_dead(t_philo *philo);
void	philo_is_sleeping_thinking(t_philo *philo);
void	philo_is_eating(t_philo *philo);
int		philo_is_died(t_philo *philo);
size_t	get_current_time(void);
int		ft_usleep(useconds_t time);
int		check_death(t_philo *philo);
int		check_for_one_philo(t_philo *philo);
int		check_philo_state(t_philo *philo);
void	free_resources(t_shared *shared);
void	cleanup(t_shared *shared);

#endif