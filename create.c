/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:55:15 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/21 01:37:31 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_philos_and_table(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nmb_of_phork);
	table->philos = malloc(sizeof(t_philo) * table->nmb_of_phork);
	table->dead = malloc(sizeof(int) * table->nmb_of_phork);
	table->eat = malloc(sizeof(int) * table->nmb_of_phork);
	while (++i < table->nmb_of_phork)
	{
		table->philos[i].id_num = i + 1;
		table->philos[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1) % table->nmb_of_phork];
		table->eat[i] = 0;
		table->dead[i] = 0;
		table->philos[i].im_dead = &(table->dead[i]);
		table->philos[i].eaten = &(table->eat[i]);
		table->philos[i].last_eat = 0;
	}
	pthread_mutex_init(&table->is_she_dead, NULL);
	pthread_mutex_init(&table->last_meal, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->count, NULL);
}

void	ft_print(t_table *table, t_philo *philo, int p)
{
	pthread_mutex_lock(&table->print);
	if (p == 1)
		printf("%lld %d has taken a fork\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 2)
		printf("%lld %d is eating\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 3)
		printf("%lld %d is sleeping\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 4)
		printf("%lld %d is thinking\n", ft_get_time() - table->start, philo->id_num);
	else if (p == 5)
		printf("%lld %d is died\n", ft_get_time() - table->start, philo->id_num);
	pthread_mutex_unlock(&table->print);
}


void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int i;
	i = 1;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (!ft_rfork(table, philo))
			break;
		if(!ft_lfork(table, philo))
			break;
		if(!ft_eating(table, philo))
			break;
		if(!ft_sleeping(table, philo))
			break;
		if(!ft_thinking(table, philo))
			break;
	}
	return(NULL);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start = ft_get_time();
	ft_create_philos_and_table(table);
	while (i < table->nmb_of_phork)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &ft_routine, (void *)&table->philos[i]) < 0)
			return (0);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < table->nmb_of_phork)
	{
	printf("ttt\n");
	printf("A\n");
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (0);
		i++;
	}
	return (1);
}