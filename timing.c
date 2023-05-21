/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:33:07 by havyilma          #+#    #+#             */
/*   Updated: 2023/05/21 01:48:36 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_get_time()
{
	struct timeval mikro;

	gettimeofday(&mikro, NULL);
	return((mikro.tv_sec * 1000) + mikro.tv_usec / 1000);
}

void	ft_wait(long long milisec)
{
	int	i;

	i = 0;
	while (ft_get_time() < milisec)
	{
		usleep(500);
		i++;
	}
}