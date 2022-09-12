/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:44:59 by szhakypo          #+#    #+#             */
/*   Updated: 2022/09/12 14:45:42 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Why? cuz usleep taking more time that i need cuz cpu taked time for
//compile time and taking more;

void	ft_usleep(int time_ms)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < time_ms)
		usleep(100);
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
	print_philo(table, philo, YEL"He sleepeng"RESET);
	ft_usleep(table->time_to_die);
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
