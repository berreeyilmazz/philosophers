/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:35:42 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/11 04:39:28 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_philos(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nmb_of_phork);
	while (++i < table->nmb_of_phork)
	{
		table->philos[i].id_num = i + 1;
		table->philos[i].table = table;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1)
			% table->nmb_of_phork];
		table->philos[i].eat_count = 0;
		table->philos[i].last_eat = 0;
		pthread_mutex_init(&table->forks[i], NULL);
	}
	return (0);
}

int	ft_create_table(t_table *table)
{
	table->is_she_dead = 0;
	table->is_she_dead = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->is_she_dead, NULL);
	table->last_meal_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->last_meal_mutex, NULL);
	table->print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->print_mutex, NULL);
	table->dead = 0;
	table->count_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->count_mutex, NULL);
	table->enough = -1;
	return (0);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = ft_get_time();
	while (i < table->nmb_of_phork)
	{
		if (pthread_create(&(table->philos[i].thread_id), NULL, &ft_routine,
			(void *)&table->philos[i]))
			return (0);
		i++;
		usleep(100);
	}
	ft_control_if_re(table);
	i = 0;
	while (i < table->nmb_of_phork)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (0);
		printf("            %d\n", i);
		i++;
	}
	return (1);
}
