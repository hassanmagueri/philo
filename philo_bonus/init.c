/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:09 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/24 16:08:08 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_all(t_monitor *monitor)
{
	int		i;
	int		index;
	char	name[6];

	ft_strlcpy(name, "/    ", 6);
	i = 0;
	index = 1;
	sem_end(monitor->sem_printf, "/sem_printf");
	while (i < monitor->num_philo)
	{
		sem_end(monitor->forks[i], name);
		i++;
		if (i % 50 == 0)
			index++;
		name[index]++;
	}
	return (0);
}

void	philo_init(t_philo *philo, int id, t_monitor *monitor)
{
	philo->id = id;
	philo->num_philo = monitor->num_philo;
	philo->time_to_die = monitor->time_to_die;
	philo->time_to_eat = monitor->time_to_eat;
	philo->time_to_sleep = monitor->time_to_sleep;
	philo->num_of_meals = monitor->num_of_meals;
	philo->forks = monitor->forks;
	philo->monitor = monitor;
	philo->last_meal = get_current_time();
}

int	destroy_semaphores(t_monitor *monitor, int size)
{
	int		i;
	int		j;

	j = 1;
	i = 0;
	sem_end(monitor->sem_printf, "/sem_print");
	ft_strlcpy(monitor->sem_name, "/    ", 6);
	while (i < size)
	{
		sem_end(monitor->forks[i], monitor->sem_name);
		i++;
		if (i % 50 == 0)
			j++;
		monitor->sem_name[j]++;
	}
	return (0);
}

int	init_sem(t_monitor *monitor)
{
	int	i;
	int	j;

	destroy_semaphores(monitor, monitor->num_philo);
	ft_strlcpy(monitor->sem_name, "/    ", 6);
	monitor->sem_printf = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (monitor->sem_printf == SEM_FAILED)
		return (sem_end(monitor->sem_philo_ready, "/sem_philo_ready"), 0);
	j = 1;
	i = 0;
	while (i < monitor->num_philo)
	{
		monitor->forks[i] = sem_open(monitor->sem_name, O_CREAT, 0644, 1);
		if (monitor->forks[i] == SEM_FAILED)
			return (destroy_semaphores(monitor, i), 0);
		i++;
		if (i % 50 == 0)
			j++;
		monitor->sem_name[j]++;
	}
	return (1);
}

int	monitor_init(t_monitor *monitor, int argc, char const *argv[])
{
	int	i;

	monitor->num_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->num_of_meals = -2;
	if (argc == 6)
		monitor->num_of_meals = ft_atoi(argv[5]);
	if (monitor->num_philo <= 0 || monitor->num_philo > 200
		|| monitor->time_to_die <= 0 || monitor->time_to_eat <= 0
		|| monitor->time_to_sleep <= 0 || monitor->num_of_meals == -1
		|| monitor->num_of_meals == 0)
		return (print_error(0, NULL));
	if (init_sem(monitor) == 0)
		return (0);
	i = 0;
	while (i++ < monitor->num_philo)
		philo_init(&(monitor->philos[i - 1]), i, monitor);
	monitor->time_start = get_current_time();
	return (1);
}
