/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:33:53 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/20 16:05:17 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->last_meal);
	if ((get_current_time() - philo->last_meal) >= philo->shared->time_to_die)
	{
		pthread_mutex_unlock(&philo->shared->last_meal);
		pthread_mutex_lock(&philo->shared->die_mutex);
		if (philo->shared->philo_died == 0)
		{
			philo->shared->philo_died = 1;
			pthread_mutex_unlock(&philo->shared->die_mutex);
			pthread_mutex_lock(&philo->shared->mutex_state);
			printf("%lu ->  philo %d is died\n",
				get_current_time() - philo->shared->start_time, philo->id + 1);
			pthread_mutex_unlock(&philo->shared->mutex_state);
			return (1);
		}
		pthread_mutex_unlock(&philo->shared->die_mutex);
	}
	else
		pthread_mutex_unlock(&philo->shared->last_meal);
	return (0);
}

int	check_for_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->fork_mutex[philo->right_fork]);
	if (philo->shared->num_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->shared->fork_mutex[philo->right_fork]);
		ft_usleep(philo->shared->time_to_die + 1);
		check_death(philo);
	}
	return (0);
}
