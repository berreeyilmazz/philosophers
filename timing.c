/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:49:13 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 18:55:51 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	mikro;

	gettimeofday(&mikro, NULL);
	return ((mikro.tv_sec * 1000) + mikro.tv_usec / 1000);
}

int	ft_wait(long long milisec)
{
	while (ft_get_time() < milisec)
		usleep(50);
	return (1);
}
