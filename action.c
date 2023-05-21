/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:38:05 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/21 01:45:42 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_rfork(t_table *table, t_philo *philo)
{
	if (!ft_imdead(table, philo))
		return (0);
	pthread_mutex_lock(&(table->count));
	if (ft_dead(table, philo) && (table->argc == 5 || ft_repeat(table)))
	{
		pthread_mutex_unlock(&(table->count));
		pthread_mutex_lock (philo->right_fork);
		ft_print (table, philo, 1);
		return (1);
	}
	pthread_mutex_unlock(&(table->count));
	return (0);
}

int	ft_lfork(t_table *table, t_philo *philo)
{
	if (!ft_imdead(table, philo))
		return (0);
	pthread_mutex_lock(&(table->count));
	if (ft_dead(table, philo) && (table->argc == 5 || ft_repeat(table)))
	{
		pthread_mutex_lock (philo->left_fork);
		ft_print (table, philo, 1);
		pthread_mutex_unlock(&(table->count));
		return (1);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&(table->count));
	return (0);
}

int	ft_eating (t_table *table, t_philo *philo)
{
	if (!ft_imdead(table, philo))
		return (0);
	pthread_mutex_lock(&(table->count));
	if (ft_dead(table, philo) && (table->argc == 5 || ft_repeat(table)))
	{
		pthread_mutex_unlock(&table->count);
		ft_print (table, philo, 2);
		pthread_mutex_lock(&(table->last_meal));
		*(philo->eaten) = 1;
		philo->last_eat = ft_get_time();
		pthread_mutex_unlock(&(table->last_meal));
		printf("          EAT %d\n", table->time_to_eat);
		ft_wait(table->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&table->count);
	return (0);
}

int	ft_sleeping(t_table *table, t_philo *philo)
{
	if (!ft_imdead(table, philo))
		return (0);
	pthread_mutex_lock(&(table->count));
	if (ft_dead(table, philo) && (table->argc == 5 || ft_repeat(table)))
	{
		pthread_mutex_unlock(&table->count);
		ft_print(table, philo, 3);
		ft_wait(table->time_to_sleep);
		return (1);
	}
	pthread_mutex_unlock(&table->count);
	return (0);
}

int	ft_thinking(t_table *table, t_philo *philo)
{
	if (!ft_imdead(table, philo))
		return (0);
	pthread_mutex_lock(&(table->count));
	if (ft_dead(table, philo) && (table->argc == 5 || ft_repeat(table)))
	{
		pthread_mutex_unlock(&table->count);
		ft_print(table, philo, 4);
		return (1);
	}
	pthread_mutex_unlock(&table->count);
	return (0);
}
