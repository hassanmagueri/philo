/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:18 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:47 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_end(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

int	print_error(void)
{
	write(2, "error\n", 6);
	return (0);
}

void	kill_child_process(t_monitor *monitor, int *pid)
{
	int	i;

	if (monitor->num_of_meals > 0)
		ft_usleep(monitor->time_to_eat + monitor->time_to_sleep);
	i = 0;
	while (i < monitor->num_philo)
		kill(pid[i++], SIGINT);
}

int	main(int argc, char const *argv[])
{
	t_philo		*philos;
	t_monitor	monitor;
	int			i;
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
		if (pid[i] < 0)
			return (print_error(), 1);
		if (pid[i] == 0)
			return (ft_routine(&philos[i]), 0);
		i++;
	}
	waitpid(-1, NULL, 0);
	kill_child_process(&monitor, pid);
	destroy_all(&monitor);
	return (0);
}
