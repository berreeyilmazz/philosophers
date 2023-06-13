/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:17:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/13 10:28:20 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main (int ac, char **av)
{
	t_table	table;

	if (!(ft_take_argv(&table, av, ac)))
		return (0);
	if (!(ft_create_thread(&table)))
		return (0);
	if (!ft_create_thread(&table))
		return (0);
	return (1);
}
