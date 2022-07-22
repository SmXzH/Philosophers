/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:12:07 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/22 21:29:25 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_phiolos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].time_to_eat = table->time_to_eat;
		table->philo[i].time_to_die = table->time_to_die;
		table->philo[i].time_to_sleap = table->time_to_sleep;
		table->philo[i].how_many_eat = 0;
		table->philo[i].left = i;
		if (i < table->count_philo - 1)
			table->philo[i].right = i + 1;
		else
			table->philo[i].right = 0;
		table->philo[i].last_eat = 0;
		table->philo[i].arg = table;
		i++;
	}
	i = 0;
	while (i < table->count_lanch)
	{
		if (pthread_mutex_init(&table->fork[i++],NULL))
			return (1);
	}
	return (0);
}