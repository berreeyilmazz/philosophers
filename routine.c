/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:18:23 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/15 21:15:38 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (!ft_eating(table, philo))
			return (NULL);
		pthread_mutex_lock(&table->count);
		if (philo->eaten == table->time_to_re)
		{
			table->re += 1;
			pthread_mutex_unlock(&table->count);
			return (NULL);
		}
		pthread_mutex_unlock(&table->count);
		ft_print(table, philo, 's');
		ft_wait(ft_get_time() + table->time_to_sleep);
		ft_print(table, philo, 't');
	}
	return (NULL);
}

int	ft_zero(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->is_she_dead);
	table->dead += 1;
	pthread_mutex_unlock(&table->is_she_dead);
	ft_wait(ft_get_time() + table->time_to_die);
	printf("[%lld]  %d is dead\n", ft_get_time() - table->start, philo->id_num);
	return (0);
}

int	ft_eating(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->is_she_dead);
	if (table->dead >= 1)
	{
		pthread_mutex_unlock(&table->is_she_dead);
		return (0);
	}
	pthread_mutex_unlock(&table->is_she_dead);
	pthread_mutex_lock(philo->right_fork);
	ft_print(table, philo, 'f');
	if (table->nmb_of_phork == 1)
		return (ft_zero(table, philo));
	pthread_mutex_lock(philo->left_fork);
	ft_print(table, philo, 'f');
	pthread_mutex_lock(&table->last_meal);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&table->last_meal);
	pthread_mutex_lock(&table->count);
	philo->eaten += 1;
	pthread_mutex_unlock(&table->count);
	ft_print(table, philo, 'e');
	ft_wait(ft_get_time() + table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

void	ft_print(t_table *table, t_philo *philo, int p)
{
	pthread_mutex_lock(&table->print);
	pthread_mutex_lock(&table->is_she_dead);
	if (table->dead < 1)
	{
		pthread_mutex_unlock(&table->is_she_dead);
		if (p == 'f')
			printf("[%lld]  %d has taken a fork\n", ft_get_time()
				- table->start, philo->id_num);
		else if (p == 'e')
			printf("[%lld]  %d is eating\n", ft_get_time() - table->start,
				philo->id_num);
		else if (p == 's')
			printf("[%lld]  %d is sleeping\n", ft_get_time() - table->start,
				philo->id_num);
		else if (p == 't')
			printf("[%lld]  %d is thinking\n", ft_get_time() - table->start,
				philo->id_num);
	}
	else
		pthread_mutex_unlock(&table->is_she_dead);
	pthread_mutex_unlock(&table->print);
}
