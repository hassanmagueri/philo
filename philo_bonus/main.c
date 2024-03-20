/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:48:18 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/20 15:04:25 by emagueri         ###   ########.fr       */
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
	int			pid;

	if (argc != 5 && argc != 6)
		return (print_error());
	if (monitor_init(&monitor, argc, argv) == 0)
		return (1);
	
	philos = monitor.philos;
	i = 0;
	while (i < monitor.num_philo)
	{
		pid = fork();
		if(pid == 0)
		{
			ft_routine(&philos[i]);
			exit(1);
		}
		i++;
	}
	for (i = 0; i < monitor.num_philo; i++) 
    {
        wait(NULL);
    }
	i = 0;
	while (i < monitor.num_philo)
	{
		if (philos[i].is_dead)
			printf("%zu %d died\n", get_current_time() - monitor.time_start,monitor.philos[i].id);
		i++;
	}
	
	// ft_monitor(&monitor);
	// sleep(5);
    // Close and unlink the semaphore
    // sem_close(sem);
    // sem_unlink(SEMAPHORE_NAME);
	// i = 0;
	// destroy_free_all(&monitor);
	return (0);
}
