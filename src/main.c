/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:30:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/10 21:14:12 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Check: Philo dead or not

void	*near_to_die(void *tmp)
{
	t_table	*table;
	t_philo	*philo;
	int	i;
	int count;

	table = tmp;
	philo = table->philo;
	while (1)
	{
		i = -1;
		while (++i < table->count_philo)
		{			
			pthread_mutex_lock(&table->many_eat);
			count = philo->how_many_eat;
			pthread_mutex_unlock(&table->many_eat);
			if(table->count_lanch)
				if (count == table->count_lanch)
					return (NULL);
			pthread_mutex_lock(&table->eat);
			count = philo[i].last_eat;
			pthread_mutex_unlock(&table->eat);
			if (get_timestamp() - count > philo[i].time_to_die)
			{
				pthread_mutex_lock(&table->dead);
				table->flg_of_dead = 1;
				pthread_mutex_unlock(&table->dead);
				pthread_mutex_lock(&table->print);
				printf("%lld %d" YEL " is died\n" RESET, get_timestamp() - philo->time_start, philo->id);
				return(NULL);
			}
		}
	}
	return(NULL);
}

// Parse arguments

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
	int sv_dead;

	philo = (t_philo *)ag;
	table = philo->arg;
	if (philo->id % 2 == 0)
	{
		print_philo(table, philo,GRN"He thinking"RESET);
		ft_usleep(50);
	}
	pthread_mutex_lock(&table->dead);
	sv_dead = table->flg_of_dead;
	pthread_mutex_unlock(&table->dead);
	while (!sv_dead)
	{
		if(table->count_lanch)
			if (philo->how_many_eat == table->count_lanch)
				return (NULL);
		if(eating(table, philo))
			return(NULL);
		eating(table, philo);
		thinking(table, philo);
		pthread_mutex_lock(&table->dead);
		sv_dead = table->flg_of_dead;
		pthread_mutex_unlock(&table->dead);
	}
	return (NULL);
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
	
	i = -1;
	while (++i < ph->count_philo)
		pthread_create(&ph->thread[i], NULL, &start, &ph->philo[i]);
	pthread_create(&check, NULL, &near_to_die, ph);
	pthread_mutex_unlock(&ph->print);
	pthread_join(check, NULL);
	i = -1;
	while (++i < ph->count_philo)
		pthread_join(ph->thread[i], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*all;

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
	destoriy(all);
	free(all);
	return (0);
}
