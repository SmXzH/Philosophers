/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:44:59 by szhakypo          #+#    #+#             */
/*   Updated: 2022/07/26 22:56:32 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rutune(void *ph)
{
	//pthread_t	*tmp;
	t_table	*tmp;
	
	tmp = ph;
	
	printf("pthread =  %d\n", tmp->count_lanch);
	return (NULL);
}