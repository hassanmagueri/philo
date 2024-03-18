/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:18 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/18 00:54:31 by emagueri         ###   ########.fr       */
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

	if (argc != 5 && argc != 6)
		return (print_error());
	if (monitor_init(&monitor, argc, argv) == 0)
		return (1);
	i = 0;
	philos = monitor.philos;
	while (i < monitor.num_philo)
	{
		pthread_create(&philos[i].thread_id, NULL,
			&ft_routine, (void *) &philos[i]);
		i++;
	}
	pthread_create(&monitor.thread_id, NULL, &ft_monitor, (void *) &monitor);
	i = 0;
	while (i < monitor.num_philo)
		pthread_join(monitor.philos[i++].thread_id, NULL);
	pthread_join(monitor.thread_id, NULL);
	destroy_free_all(&monitor);
	return (0);
}
