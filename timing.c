/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:43:09 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/11 04:56:29 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_wait(long long milisec, t_table *table)
{
	int	i;

	i = 0;
	while (ft_get_time() < milisec)
	{
		pthread_mutex_lock(table->is_she_dead);
		if (table->dead == 1)
		{
			pthread_mutex_unlock(table->is_she_dead);
			return (0);
		}
		pthread_mutex_unlock(table->is_she_dead);
		usleep(500);
	}
	return (1);
}

int	ft_check_repeat(t_table *table)
{
	int	x;
	int y;

	x = 0;
	y = -1;
	pthread_mutex_lock(table->count_mutex);
	while (++y < table->nmb_of_phork)
	{
		if (table->philos[y].eat_count != table->time_to_re)
		{
			pthread_mutex_unlock(table->count_mutex);
			return (-1);
		}
		usleep(100);
	}
	table->enough = 1;
	pthread_mutex_unlock(table->count_mutex);
	return (1);
}

int	ft_check_if_dead(t_table *table)
{
	int	i;

	i = -1;
	if (table->time_to_die < table->time_to_eat + table->time_to_sleep)
		return(0);
	while (++i < table->nmb_of_phork)
	{
		pthread_mutex_lock(table->last_meal_mutex);
		if (table->time_to_die < (ft_get_time() - table->start_time - table->philos[i].last_eat))
		{
			pthread_mutex_unlock(table->last_meal_mutex);
			pthread_mutex_lock(table->is_she_dead);
			table->dead = 1;
			pthread_mutex_unlock(table->is_she_dead);
			pthread_mutex_lock(table->print_mutex);
			printf("%lld %d is died\n", (ft_get_time() - table->start_time), table->philos[i].id_num);
			pthread_mutex_unlock(table->print_mutex);
			return (0);
		}
		pthread_mutex_unlock(table->last_meal_mutex);
	}
	return (1);
}

int	ft_control_if_re(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nmb_of_phork)
	{
		if (!ft_check_if_dead(table))
			return (0);
		else if(ft_check_repeat(table) != -1)
			return (0);
		i++;
		if (i == table->nmb_of_phork)
			i = 0;
		usleep(500);
	}
	return (1);
}
