/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:14:46 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 10:36:17 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	int				id_num;
	struct s_table	*table;
	long long		last_eat;
	int				eaten;

}					t_philo;

typedef struct s_table
{
	int				nmb_of_phork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_re;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_she_dead;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	print;
	pthread_mutex_t	count;
	pthread_mutex_t	ctrl;
	pthread_mutex_t	dst;
	int				dead;
	long long		start;
	int				argc;

}					t_table;

int	ft_strlen(char *ac);
int	ft_atoi(char *ac);
int	ft_take_argv(t_table *table, char **av, int ac);
int	ft_check_argv(int ac, char **av);
int	ft_check(t_table *table);
void	ft_create_philos_and_table(t_table *table);
int	ft_create_thread(t_table *table);
void ft_print(t_table *table, t_philo *philo, int p);
long long	ft_get_time();
int	ft_wait(long long milisec, t_table *table, t_philo *philo);
void	*ft_routine(void *arg);
int	ft_eating(t_table *table, t_philo *philo);
void ft_print(t_table *table, t_philo *philo, int p);

#endif