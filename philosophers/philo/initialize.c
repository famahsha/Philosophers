/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:33:18 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/20 15:32:16 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_args(t_shared *shared, char **av)
{
	shared->num_of_philo = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	shared->start_time = get_current_time();
	if (av[5])
		shared->totalno_of_eats = ft_atoi(av[5]);
	else
		shared->totalno_of_eats = -1;
	shared->philo_died = 0;
}

void	mutex_init(t_shared *shared)
{
	int	i;

	i = 0;
	shared->fork_available = malloc(shared->num_of_philo * sizeof(int));
	shared->sign = malloc(shared->num_of_philo * sizeof(int));
	while (i < shared->num_of_philo)
	{
		shared->fork_available[i] = -1;
		shared->sign[i] = -1;
		i++;
	}
	i = 0;
	while (i < shared->num_of_philo)
	{
		pthread_mutex_init(&shared->fork_mutex[i], NULL);
		pthread_mutex_init(&shared->sign_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->mutex_state, NULL);
	pthread_mutex_init(&shared->die_mutex, NULL);
	pthread_mutex_init(&shared->last_meal, NULL);
}

void	initialize_philo(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->num_of_philo)
	{
		shared->philo[i].id = i;
		shared->philo[i].right_fork = i;
		shared->philo[i].left_fork = ((i + 1) % shared->num_of_philo);
		shared->philo[i].shared = shared;
		shared->philo[i].last_meal = 0;
		shared->philo[i].total_eats = 0;
		i++;
	}
}

void	initialize(t_shared *shared)
{
	int	i;

	i = 0;
	shared->philo = malloc(shared->num_of_philo * sizeof(t_philo));
	shared->fork_mutex = malloc(shared->num_of_philo * sizeof(pthread_mutex_t));
	shared->sign_mutex = malloc(shared->num_of_philo * sizeof(pthread_mutex_t));
	shared->start_time = get_current_time();
	mutex_init(shared);
	initialize_philo(shared);
	i = 0;
	while (i < shared->num_of_philo)
	{
		pthread_create(&shared->philo[i].thread_id, NULL, &philo_routine,
			&shared->philo[i]);
		i++;
	}
	i = 0;
	while (i < shared->num_of_philo)
	{
		pthread_join(shared->philo[i].thread_id, NULL);
		i++;
	}
}
