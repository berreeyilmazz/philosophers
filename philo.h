/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:51:44 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/07 16:26:42 by havyilma         ###   ########.fr       */
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
	struct s_table	*table;
	int				id_num;
	pthread_t		thread_id;
	int				eat_count;
	long long		last_eat;

}					t_philo;

typedef struct s_table
{
	struct s_rules	*rules;
	int				nmb_of_phork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_re;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*is_she_dead;
	pthread_mutex_t	*last_meal_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	count_mutex;
	t_philo			*philos;
	long long		start_time;
	int				dead;
	int				enough;

}					t_table;

int			ft_strlen(char *ac);
int			ft_atoi(char *ac);
int			ft_check_av(int ac, char **av);
int			ft_check_if_neg(t_table *table);
int			lets_take_av(t_table *table, char **av, int ac);
int			ft_create_philos(t_table *table);
int			ft_create_thread(t_table *table);
int			ft_control_eat(t_philo *philo, t_table *table);
int			ft_print_eating(t_philo *philo, t_table *table);
int			ft_print_fork_and_sleep(t_philo *philo, t_table *table, int a);
void		*ft_routine(void *vargs);
long long	ft_get_time(void);
int			ft_wait(long long milisec, t_table *table);
int			ft_check_repeat(t_table *table);
int			ft_check_if_dead(t_table *table, t_philo *philo);
int			ft_control_if_re(t_table *table);
int			ft_create_table(t_table *table);


#endif