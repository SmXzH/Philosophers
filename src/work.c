/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:44:59 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/06 20:01:14 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Why? cuz usleep taking more time that i need cuz cpu taked time for compile time and taking more;

void ft_usleep(int time_ms)
{
	struct timeval now;
	struct timeval start;
	gettimeofday(&now, NULL);
	gettimeofday(&start, NULL);
	while (((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000) <= time_ms)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
	
}

//Printing what philosopher doing

void	print_philo(t_table *table, t_philo *philo, char *str)
{
	pthread_mutex_lock(&table->print);
	printf("%lld, %d,%s\n", get_timestamp() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&table->print);
}

void	thinking(t_table *table, t_philo *philo)
{
	if (table->flg_of_dead)
		return ;
	print_philo(table, philo, GRN"He thinking"RESET);
}

void	sleepeng(t_table *table, t_philo *philo)
{
	if (table->flg_of_dead)
		return ;
	print_philo(table, philo, WHITE"He sleepeng"RESET);
	ft_usleep(50);
}

int	eating(t_table *tb, t_philo *philo)
{
	if (tb->flg_of_dead)
		return (1);
	pthread_mutex_lock(&tb->fork[philo->left]);
	print_philo(tb, philo, BLUE"Taked fork"RESET);
	pthread_mutex_lock(&tb->fork[philo->right]);
	print_philo(tb, philo, BLUE"Taked fork"RESET);
	print_philo(tb, philo, MAGENTA"He eating"RESET);
	philo->how_many_eat++;
	philo->last_eat = get_timestamp();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&tb->fork[philo->left]);
	pthread_mutex_unlock(&tb->fork[philo->right]);
	return(0);
}