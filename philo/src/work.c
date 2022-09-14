/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:44:59 by szhakypo          #+#    #+#             */
/*   Updated: 2022/09/14 18:43:30 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Printing what philosopher doing

void	print_philo(t_table *table, t_philo *philo, char *str)
{
	if (table->flg_of_dead)
		return ;
	pthread_mutex_lock(&table->print);
	if (table->flg_of_dead)
		return ;
	printf("%lld %d %s\n", get_timestamp() - philo->time_start, philo->id, str);
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
	print_philo(table, philo, YEL"He sleepeng"RESET);
	ft_usleep(table->time_to_sleep);
}

int	eating(t_table *tb, t_philo *philo)
{
	if (tb->flg_of_dead)
		return (1);
	pthread_mutex_lock(&tb->fork[philo->left]);
	print_philo(tb, philo, BLUE"Taked fork"RESET);
	if (tb->count_philo == 1)
		return (pthread_mutex_unlock(\
			&tb->fork[tb->philo->left]), 1);
	pthread_mutex_lock(&tb->fork[philo->right]);
	print_philo(tb, philo, BLUE"Taked fork"RESET);
	print_philo(tb, philo, MAGENTA"He eating"RESET);
	philo->how_many_eat++;
	philo->last_eat = get_timestamp();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&tb->fork[philo->left]);
	pthread_mutex_unlock(&tb->fork[philo->right]);
	return (0);
}