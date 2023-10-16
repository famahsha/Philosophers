/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:50:41 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/19 19:51:19 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sign(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->sign_mutex[philo->right_fork]);
	if (philo->shared->sign[philo->right_fork] != philo->id)
	{
		pthread_mutex_unlock(&philo->shared->sign_mutex[philo->right_fork]);
		pthread_mutex_lock(&philo->shared->sign_mutex[philo->left_fork]);
		if (philo->shared->sign[philo->left_fork] != philo->id)
		{
			pthread_mutex_unlock(&philo->shared->sign_mutex[philo->left_fork]);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&philo->shared->sign_mutex[philo->left_fork]);
		}
	}
	else
		pthread_mutex_unlock(&philo->shared->sign_mutex[philo->right_fork]);
	return (1);
}

int	try_aquire_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->fork_mutex[philo->right_fork]);
	if (philo->shared->fork_available[philo->right_fork] == -1)
	{
		philo->shared->fork_available[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->shared->fork_mutex[philo->right_fork]);
		pthread_mutex_lock(&philo->shared->fork_mutex[philo->left_fork]);
		if (philo->shared->fork_available[philo->left_fork] == -1)
		{
			philo->shared->fork_available[philo->left_fork] = 0;
			pthread_mutex_unlock(&philo->shared->fork_mutex[philo->left_fork]);
			pthread_mutex_lock(&philo->shared->mutex_state);
			printf("%lu philo %d has taken forks\n",
				get_current_time() - philo->shared->start_time, philo->id + 1);
			pthread_mutex_unlock(&philo->shared->mutex_state);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&philo->shared->fork_mutex[philo->left_fork]);
			pthread_mutex_lock(&philo->shared->fork_mutex[philo->right_fork]);
			philo->shared->fork_available[philo->right_fork] = -1;
		}
	}
	pthread_mutex_unlock(&philo->shared->fork_mutex[philo->right_fork]);
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->fork_mutex[philo->right_fork]);
	philo->shared->fork_available[philo->right_fork] = -1;
	pthread_mutex_unlock(&philo->shared->fork_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->shared->fork_mutex[philo->left_fork]);
	philo->shared->fork_available[philo->left_fork] = -1;
	pthread_mutex_unlock(&philo->shared->fork_mutex[philo->left_fork]);
}

int	check_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->die_mutex);
	if (philo->shared->philo_died == 1)
	{
		pthread_mutex_unlock(&philo->shared->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->die_mutex);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->shared->last_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->shared->last_meal);
	while (1)
	{
		if (check_philo_state(philo)
			|| philo->shared->totalno_of_eats == philo->total_eats)
			return (NULL);
		if (!check_philo_state(philo))
		{
			if (check_death(philo) == 0
				&& check_sign(philo) == 0 && try_aquire_forks(philo) == 0)
			{
				philo_is_eating(philo);
			}
			usleep(100);
		}
	}
	return (0);
}
