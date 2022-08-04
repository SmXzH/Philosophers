/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:30:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/04 22:53:09 by sam              ###   ########.fr       */
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

void *start(void *ag)
{
	t_philo *philo;
	t_table *table;

	philo = (t_philo *)ag;
	table = philo->arg;
	if (philo->id % 2 == 0)
	{
		print_philo(table, philo, "he thinking");
		ft_usleep(50);
	}
	eating(table, philo);
}

int	philo_life(t_table *ph)
{
	pthread_t check;
	int	i;
	
	i = -1;
	ph->time_start = get_timestamp();
	while (++i < ph->count_philo)
	{
		ph->philo[i].time_start = ph->time_start;
		ph->philo[i].last_eat = ph->time_start;
	}
	printf("HIIHIH\n");
	i = -1;
	while (++i < ph->count_philo)
		pthread_create(&ph->thread[i], NULL, &start, &ph->philo[i]);
	i = -1;
	while (++i < ph->count_philo)
		pthread_join(ph->thread[i], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*all;
	int	i = -1;

	if (parse(ac, av))
		return (1);
	all = init(ac, av);
	if (!all)
		return (ft_free(all));
	if (init_time(all))
		return (ft_free(all));
	printf("1\n");
	philo_life(all);
	return (0);
}
