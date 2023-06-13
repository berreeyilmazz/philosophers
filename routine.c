/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:18:23 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 11:39:01 by havyilma         ###   ########.fr       */
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
		pthread_mutex_lock(&table->is_she_dead);
		if(table->dead == 1)
		{
			pthread_mutex_unlock(&table->is_she_dead);
			return(NULL);
		}
		pthread_mutex_unlock(&table->is_she_dead);
		if(!ft_eating(table, philo))
			break;
		pthread_mutex_lock(&table->count);
		if (philo->eaten == table->time_to_re)
		{
			pthread_mutex_unlock(&table->count);
			break;
		}
		pthread_mutex_unlock(&table->count);
		ft_print(table, philo, 's');
		if(!ft_wait(ft_get_time() + table->time_to_sleep, table, philo))
			break;
		ft_print(table, philo, 't');
	}
	return(NULL);
}

int	ft_eating(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->is_she_dead);
	if(table->dead >= 1)
	{
		pthread_mutex_unlock(&table->is_she_dead);
		return (0);
	}
	pthread_mutex_unlock(&table->is_she_dead);
	pthread_mutex_lock(philo->right_fork);
	ft_print(table, philo, 'f');
	pthread_mutex_lock(philo->left_fork);
	ft_print(table, philo, 'f');
	pthread_mutex_lock(&table->count);
	philo->eaten += 1;
	pthread_mutex_unlock(&table->count);

	pthread_mutex_lock(&table->last_meal);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&table->last_meal);
	ft_print(table, philo, 'e');
	if((!ft_wait(ft_get_time() + table->time_to_eat, table, philo)))
		return (0);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}


void ft_print(t_table *table, t_philo *philo, int p)
{
	pthread_mutex_lock(&table->print);
	if (p == 'f')
		printf("[%lld] %d has taken a fork\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 'e')
		printf("[%lld] %d is eating\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 's')
		printf("[%lld] %d is sleeping\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 't')
		printf("[%lld] %d is thinking\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 'd')
	{
		pthread_mutex_lock(&table->is_she_dead);
		if(table->dead == 1)
			printf("[%lld] %d is dead\n", ft_get_time() - table->start, philo->id_num);
		pthread_mutex_unlock(&table->is_she_dead);
	}
	pthread_mutex_unlock(&table->print);

}