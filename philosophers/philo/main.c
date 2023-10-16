/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:44:27 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/20 15:18:12 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_numerics(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_arguments(int ac, char **av, t_shared	*shared)
{
	int			i;
	int			res;

	i = 1;
	res = 1;
	if (ac < 5 || ac > 6)
	{
		printf("invalid no of arguments\n");
		res = 0;
	}
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
		{
			res = 0;
			break ;
		}
		i++;
	}
	if (res)
		initialize_args(shared, av);
	return (res);
}

int	main(int ac, char **av)
{
	t_shared	*shared;

	shared = malloc(sizeof(t_shared));
	if (check_arguments(ac, av, shared))
	{
		initialize(shared);
		cleanup(shared);
		free_resources(shared);
	}
	else
	{
		free(shared);
	}
	return (0);
}
