/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:31:01 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/24 15:34:09 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_O
# define PHILO_O

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct table
{
	int				id;
	int				time_to_eat;
	int				time_to_sleap;
	int				time_to_die;
	int				how_many_eat;
	int				left;
	int				right;
	long long		last_eat;
	struct philo	*arg;
}	t_philo;

typedef struct philo
{
	int				count_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				count_lanch;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_table;

long long	ft_atoi(const char *str);
t_table	*init(int ac, char **av);
int	init_time(t_table *all);
int	ft_free(t_table	*all);
int	init_phiolos(t_table *table);
int	parse(int ac, char **av);
#endif