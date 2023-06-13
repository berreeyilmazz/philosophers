/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:00:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 11:17:01 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->nmb_of_phork)
	{
		pthread_mutex_lock(&table->last_meal);
		if(ft_get_time() - table->philos[i].last_eat >= table->time_to_die)
		{
			pthread_mutex_lock(&table->is_she_dead);
			table->dead += 1;
			pthread_mutex_unlock(&table->last_meal);
			pthread_mutex_unlock(&table->is_she_dead);
			return (0);
		}
		pthread_mutex_unlock(&table->last_meal);
		if (table->dead >= 1)
		{
			pthread_mutex_unlock(&table->is_she_dead);
			ft_print(table, &table->philos[i], 'd');
			return (0);
		}
		pthread_mutex_unlock(&table->is_she_dead);
		i++;
		if (i == table->nmb_of_phork)
			i = 0;
	}
	return (1);
}