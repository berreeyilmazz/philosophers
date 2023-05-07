/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:43:09 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/07 17:31:53 by havyilma         ###   ########.fr       */
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
		if (ft_check_repeat(table) == 0)
		{
			return (0);
		}
		usleep(200);
	}
	return (1);
}

int	ft_check_repeat(t_table *table)
{
	int	x;

	x = 0;
	while (x < table->nmb_of_phork)
	{
		pthread_mutex_lock(&table->count_mutex);
		if (table->philos[x].eat_count == table->time_to_re)
			x++;
		if (x == table->nmb_of_phork)
		{
			table->enough = 1;
			pthread_mutex_unlock(&table->count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->count_mutex);
	}
	return(1);
}

int	ft_check_if_dead(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(table->last_meal_mutex);
	if (table->time_to_die <= (ft_get_time() - table->start_time
			- philo->last_eat))
	{
		pthread_mutex_unlock(table->last_meal_mutex);
		printf("%lld %d is died\n", (ft_get_time() - table->start_time), philo->id_num);
		pthread_mutex_lock(table->is_she_dead);
		table->dead = 1;
		pthread_mutex_unlock(table->is_she_dead);
		return (0);
	}
	pthread_mutex_unlock(table->last_meal_mutex);
	//printf("++\n");
	return (1);
}

int	ft_control_if_re(t_table *table)
{
	int	i;

	i = 0;
	ft_check_repeat(table);
	printf("cikti\n");

	while (i < table->nmb_of_phork)
	{
	//	printf("    enough %d    \n", table->enough);
		pthread_mutex_lock(&(table->count_mutex));
		if (ft_check_if_dead(table, &(table->philos[i])) == 0 || table->enough == 1)
		{
			pthread_mutex_unlock(&(table->count_mutex));
			break ;
		}
		pthread_mutex_unlock(&(table->count_mutex));
		i++;
		if (i == table->nmb_of_phork)
			i = 0;
		usleep(200);
	}
	return (0);
}
