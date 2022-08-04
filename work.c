/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:44:59 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/04 22:04:55 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(int time_ms)
{
	struct timeval now;
	struct timeval start;
	gettimeofday(&now, NULL);
	gettimeofday(&start, NULL);
	while (((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000) < time_ms)
	{
		usleep(10);
		gettimeofday(&now, NULL);
	}
	
}

void	print_philo(t_table *table, t_philo *philo, char *str)
{
	int	i;

	pthread_mutex_lock(&table->print);
	printf("%lld, %d, %s\n", get_timestamp() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&table->print);
}

void	*thinking(t_table *table, t_philo *philo)
{
	print_philo(table, philo, "He thinking");
}

void	*sleepeng(t_table *table, t_philo *philo)
{
	print_philo(table, philo, "He sleepeng");
	ft_usleep(50); //need own funciton
}

void	*eating(t_table *tb, t_philo *philo)
{
	pthread_mutex_lock(&tb->fork[philo->left]);
	print_philo(tb, philo, "taked fork");
	pthread_mutex_lock(&tb->fork[philo->right]);
	print_philo(tb, philo, "taked fork");
	print_philo(tb, philo, "he eating");
	philo->how_many_eat++;
	philo->last_eat = get_timestamp();
	pthread_mutex_unlock(&tb->fork[philo->left]);
	pthread_mutex_unlock(&tb->fork[philo->right]);
	return(0);
}