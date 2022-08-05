/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:30:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/05 17:11:02 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*near_to_die(void *tmp)
{
	t_table	*table;
	t_philo	*philo;
	int	i;

	table = tmp;
	philo = table->philo;
	while (1)
	{
		i = -1;
		while (++i < table->count_philo)
		{
			if(table->count_lanch)
				if (philo->how_many_eat == table->count_lanch)
					return (NULL);
			if (get_timestamp() - philo[i].last_eat > philo[i].time_to_die)
			{
				table->flg_of_dead = 1;
				pthread_mutex_lock(&table->print);
				printf("%lld %d" YEL " is died\n", get_timestamp() - philo->time_start, philo->id);
				return(NULL);
			}
		}
	}
	return(NULL);
}

int	parse(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf(RED "Error: Wrong number of arguments.\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf(RED "Error: Wrong arguments.\n");
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
	while (!table->flg_of_dead)
	{
		if(table->count_lanch)
			if (philo->how_many_eat == table->count_lanch)
				return (NULL);
		eating(table, philo);
		thinking(table, philo);
	}
	return (NULL);
}

int	philo_life(t_table *ph)
{
	//pthread_t check;
	int	i;
	
	i = -1;
	ph->time_start = get_timestamp();
	while (++i < ph->count_philo)
	{
		ph->philo[i].time_start = ph->time_start;
		ph->philo[i].last_eat = ph->time_start;
	}
	
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
	if(init_phiolos(all))
		return(ft_free(all));
	philo_life(all);
	return (0);
}
