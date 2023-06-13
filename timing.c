/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:49:13 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 11:31:54 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time()
{
	struct timeval mikro;

	gettimeofday(&mikro, NULL);
	return((mikro.tv_sec * 1000) + mikro.tv_usec / 1000);
}

int	ft_wait(long long milisec, t_table *table, t_philo *philo)
{
	(void)philo;
	while (ft_get_time() < milisec)
	{
		pthread_mutex_lock(&table->is_she_dead);
		if (table->dead >= 1)
		{
			pthread_mutex_unlock(&table->is_she_dead);
			return (0);
		}
		pthread_mutex_unlock(&table->is_she_dead);
		usleep(30);
	}
	return (1);
}