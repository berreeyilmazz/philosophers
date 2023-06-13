/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:17:45 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 10:36:36 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start = ft_get_time();
	ft_create_philos_and_table(table);
	while (i < table->nmb_of_phork)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &ft_routine, (void *)&table->philos[i]))
			return (0);
		i++;
		usleep(100);
	}
	i = 0;
	ft_check(table);
	while (i < table->nmb_of_phork)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (0);
		i++;
	}
	return (1);
}

void	ft_create_philos_and_table(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nmb_of_phork);
	table->philos = malloc(sizeof(t_philo) * table->nmb_of_phork);
	table->dead = 0;
	while (++i < table->nmb_of_phork)
	{
		table->philos[i].id_num = i + 1;
		table->philos[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1) % table->nmb_of_phork];
		table->philos[i].eaten = 0;
		table->philos[i].last_eat = table->start;
	}
	pthread_mutex_init(&table->is_she_dead, NULL);
	pthread_mutex_init(&table->last_meal, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->count, NULL);
}
