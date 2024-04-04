/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:18 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/04 00:53:05 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(void)
{
	write(2, "error\n", 6);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_philo		*philos;
	t_monitor	monitor;
	int			i;

	if (argc != 5 && argc != 6)
		return (print_error());
	if (monitor_init(&monitor, argc, argv) == 0)
		return (1);
	i = 0;
	philos = monitor.philos;
	while (i < monitor.num_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				ft_routine, (void *) &philos[i]) == -1)
			return (destroy_free_all(&monitor), 1);
		i++;
	}
	if (pthread_create(&monitor.thread_id, NULL,
			&ft_monitor, (void *) &monitor) == -1)
		return (destroy_free_all(&monitor), 1);
	i = 0;
	while (i < monitor.num_philo)
		pthread_join(monitor.philos[i++].thread_id, NULL);
	pthread_join(monitor.thread_id, NULL);
	destroy_free_all(&monitor);
}
