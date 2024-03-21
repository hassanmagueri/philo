/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:18 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/21 17:42:16 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(void)
{
	write(2, "error\n", 6);
	return (0);
}

void	leak(void)
{
	system("leaks a.out");
}

int	main(int argc, char const *argv[])
{
	t_philo		*philos;
	t_monitor	monitor;
	int			i;
	int			j;
	int			pid[200];

	if (argc != 5 && argc != 6)
		return (print_error());
	if (monitor_init(&monitor, argc, argv) == 0)
		return (1);
	philos = monitor.philos;
	i = 0;
	while (i < monitor.num_philo)
	{
		pid[i] = fork();
		if(pid[i] == 0)
		{
			ft_routine(&philos[i]);
			exit(1);
		}
		i++;
	}
	waitpid(-1, NULL, 0);
	while (j < monitor.num_of_meals)
	{
		kill(pid[i], SIGINT);
		j++;
	}
	destroy_all(&monitor);
	return (0);
}
