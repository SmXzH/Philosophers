/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:30:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/26 23:08:16 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: Wrong arguments.\n");
		return (1);
	}
	return (0);
}

int	philo_life(t_table *ph)
{
	pthread_t tread;
	int	i;
	
	i = 0;
	while (ph->count_philo > i)
	{
		pthread_create(ph->thread, NULL, rutune, &ph);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*all;
	int	i = 0;

	if (parse(ac, av))
		return (1);
	all = init(ac, av);
	if (!all)
		return (ft_free(all));
	if (init_time(all))
		return (ft_free(all));
	philo_life(all);
	while (all->count_philo > i)
	{
		pthread_join(*(*all).thread, NULL);
		i++;
	}
	
	return (0);
}
