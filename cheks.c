/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:37:03 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/21 21:51:22 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(char *s)
{
	int			i;
	long long	n;
	int			flag;

	i = 0;
	flag = 0;
	if (s[i] == '-')
		flag = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= 0 && s[i] <= '9')
	{
		n = s[i] * 10 + s[i] - '0';
		i++;
	}
	if (n >= 9223372036854775807 && flag == -1)
		return (-1);
	if (n >= 9223372036854775807 && flag == 1)
		return (0);
	return (n * flag);
}

t_table	*init(int ac, char **av)
{
	t_table	*arg;

	arg = malloc(sizeof(t_table));
	if (!arg)
		return (NULL);
	arg->count_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->count_lanch = ft_atoi(av[5]);
	pthread_mutex_init(&arg->print, NULL);
	arg->philo = NULL;
	arg->thread = NULL;
	arg->fork = NULL;
}

int	init_time(t_table *all)
{
	all->philo = malloc(sizeof(t_philo) * all->count_philo);
	if (!all->philo)
		return (1);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->count_philo);
	if (!all->fork)
		return (1);
	all->thread = malloc(sizeof(pthread_t) * all->count_philo);
	if (!all->thread)
		return (1);
}

void	ft_free(t_table	*all)
{
	if (all->philo)
		free(all->philo);
	if (all->fork)
		free(all->fork);
	if (all->thread)
		free(all->thread);
	free(all);
}
