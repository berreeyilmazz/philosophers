/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:00:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 18:56:35 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_1(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->is_she_dead);
	if (table->dead >= 1)
	{
		pthread_mutex_unlock(&table->is_she_dead);
		return (0);
	}
	i++;
	pthread_mutex_unlock(&table->is_she_dead);
	return (1);
}

int	ft_2(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nmb_of_phork)
	{
		pthread_mutex_lock(&table->last_meal);
		if (ft_get_time() - table->philos[i].last_eat >= table->time_to_die)
		{
			pthread_mutex_unlock(&table->last_meal);
			pthread_mutex_lock(&table->is_she_dead);
			table->dead += 1;
			pthread_mutex_unlock(&table->is_she_dead);
			printf("[%lld] %d is dead\n", ft_get_time() - table->start,
				table->philos[i].id_num);
			return (0);
		}
		i++;
		pthread_mutex_unlock(&table->last_meal);
		usleep(100);
	}
	usleep(100);
	return (1);
}

int	ft_3(t_table *table)
{
	pthread_mutex_lock(&table->count);
	if (table->argc == 6 && table->re == table->nmb_of_phork)
	{
		pthread_mutex_unlock(&table->count);
		return (0);
	}
	pthread_mutex_unlock(&table->count);
	return (1);
}

int	ft_check(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((!ft_3(table)))
			return (0);
		if (!(ft_1(table)))
			return (0);
		if (!(ft_2(table)))
			return (0);
	}
	return (1);
}
