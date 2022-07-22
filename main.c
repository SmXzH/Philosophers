/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:30:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/22 21:24:22 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int ac, char **av)
{
	if (ft_atoi(av[1] <= 0) || ft_atoi(av[2] <= 0) || ft_atoi(av[3] <= 0)
		|| ft_atoi(av[4] <= 0) || (ac == 6 && ft_atoi(av[5])))
	{
		printf("WRONG ARGEMENTS\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*all;

	parse(ac, av);
	init(ac, av);
	if (all)
		return (ft_free(all));
	if (init_time(all))
		return (ft_free(all));
	return (0);
}