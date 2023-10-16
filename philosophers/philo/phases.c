/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phases.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:33:51 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/20 14:24:17 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_eating(t_philo *philo)
{
	if (check_philo_state(philo))
		return ;
	pthread_mutex_lock(&philo->shared->last_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->shared->last_meal);
	pthread_mutex_lock(&philo->shared->mutex_state);
	printf("%lu -> philo %d is eating\n",
		(get_current_time() - philo->shared->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->shared->mutex_state);
	pthread_mutex_lock(&philo->shared->sign_mutex[philo->right_fork]);
	philo->shared->sign[philo->right_fork] = philo->id;
	pthread_mutex_unlock(&philo->shared->sign_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->shared->sign_mutex[philo->left_fork]);
	philo->shared->sign[philo->left_fork] = philo->id;
	pthread_mutex_unlock(&philo->shared->sign_mutex[philo->left_fork]);
	ft_usleep(philo->shared->time_to_eat);
	philo->total_eats++;
	release_forks(philo);
	philo_is_sleeping_thinking(philo);
}

void	philo_is_sleeping_thinking(t_philo *philo)
{
	if (check_philo_state(philo))
		return ;
	pthread_mutex_lock(&philo->shared->mutex_state);
	printf("%lu -> philo %d is sleeping\n",
		(get_current_time() - philo->shared->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->shared->mutex_state);
	ft_usleep(philo->shared->time_to_sleep);
	if (check_philo_state(philo))
		return ;
	pthread_mutex_lock(&philo->shared->mutex_state);
	printf("%lu -> philo %d  is thinking\n",
		(get_current_time() - philo->shared->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->shared->mutex_state);
}
