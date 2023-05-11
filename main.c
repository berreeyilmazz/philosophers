/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:35:59 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/11 05:11:24 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_control_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(table->count_mutex);
	if (philo->eat_count == table->time_to_re)
	{
		pthread_mutex_unlock(table->count_mutex);
		return (0);
	}
	pthread_mutex_unlock(table->count_mutex);
	pthread_mutex_lock(table->is_she_dead);
	if (table->dead == 1)
	{
		pthread_mutex_unlock(table->is_she_dead);
		return (0);
	}
	pthread_mutex_unlock(table->is_she_dead);
	return (1);
}

int	ft_print_eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(table->is_she_dead);
	if (table->dead == 0)
	{
		pthread_mutex_unlock(table->is_she_dead);
		pthread_mutex_lock(table->count_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(table->count_mutex);
		pthread_mutex_lock(table->last_meal_mutex);
		philo->last_eat = ft_get_time() - table->start_time;
		pthread_mutex_unlock(table->last_meal_mutex);
		if (!ft_wait((ft_get_time() + table->time_to_eat), table))
			return (0);
		pthread_mutex_lock(table->print_mutex);
		printf("%lld %d is eating\n", (ft_get_time() - table->start_time),
			philo->id_num);
		pthread_mutex_unlock(table->print_mutex);

		return (0);
	}
	pthread_mutex_unlock(table->is_she_dead);
	return (1);
}

int	ft_print_fork_and_sleep(t_philo *philo, t_table *table, int a)
{
	pthread_mutex_lock(table->is_she_dead);
	if (table->dead == 0)
	{
		pthread_mutex_unlock(table->is_she_dead);
		pthread_mutex_lock(table->print_mutex);
		if (a == 1)
			printf("%lld %d has taken a fork\n", (ft_get_time() - table->start_time),
			philo->id_num);
		else if (a == 3)
			printf("%lld %d is thinking\n", (ft_get_time() - table->start_time),
				philo->id_num);
		else if (a == 2)
		{
			printf("%lld %d is sleeping\n", (ft_get_time() - table->start_time),
				philo->id_num);
		}
		pthread_mutex_unlock(table->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(table->is_she_dead);
	return (1);
}

void	*ft_routine(void *vargs)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)vargs;
	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(table->count_mutex);
		pthread_mutex_lock(table->is_she_dead);
		if (table->enough == 1 || table->dead == 1)
		{
			pthread_mutex_unlock(table->count_mutex);
			pthread_mutex_unlock(table->is_she_dead);
			break ;
		}
		pthread_mutex_unlock(table->is_she_dead);
		pthread_mutex_unlock(table->count_mutex);
		pthread_mutex_lock(philo->right_fork);
		if (ft_print_fork_and_sleep(philo, table, 1) == 1)
			break ;
		pthread_mutex_lock(philo->left_fork);
		if (ft_print_fork_and_sleep(philo, table, 1) == 1)
			break ;
		if (ft_print_eating(philo, table) == 1)
			break;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		if (ft_print_fork_and_sleep(philo, table, 2) == 1)
			break ;
		if (!ft_wait((ft_get_time() + table->time_to_sleep), table))
			return (NULL);
		if (ft_print_fork_and_sleep(philo, table, 3) == 1)
		{
			break ;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!ft_check_av(ac, av))
		return (0);
	if (!lets_take_av(&table, av, ac))
		return (0);
	if (!ft_check_if_neg(&table))
		return (0);
	if (ft_create_thread(&table))
		return (0);
	printf("444\n");
	return (0);
}


// ft waitlere bak düzgünce