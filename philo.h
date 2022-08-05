/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:31:01 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/05 00:18:51 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_O
# define PHILO_O

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h> //gettimeofday()
# include <stdlib.h>
# include <unistd.h>

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"

typedef struct table
{
	int				id;
	long long		time_start;
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
	int				flg_of_dead;
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
long long get_timestamp();
void	print_philo(t_table *table, t_philo *philo, char *str);
void	thinking(t_table *table, t_philo *philo);
void	sleepeng(t_table *table, t_philo *philo);
int	eating(t_table *tb, t_philo *philo);
void ft_usleep(int time_ms);

#endif