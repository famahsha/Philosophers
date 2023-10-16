/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:54:46 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/20 15:30:33 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(100);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	cleanup(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->num_of_philo)
	{
		pthread_mutex_destroy(&shared->fork_mutex[i]);
		pthread_mutex_destroy(&shared->sign_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&shared->mutex_state);
	pthread_mutex_destroy(&shared->die_mutex);
	pthread_mutex_destroy(&shared->last_meal);
	free(shared->fork_available);
	free(shared->sign);
}

void	free_resources(t_shared *shared)
{
	free(shared->philo);
	free(shared->fork_mutex);
	free(shared->sign_mutex);
	free(shared);
}
