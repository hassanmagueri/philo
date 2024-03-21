/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:09 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/21 15:07:43 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_end(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

int	destroy_all(t_monitor *monitor)
{
	int	i;
	int index;

	index = 0;
	i = 0;
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	sem_end(monitor->sem_printf, "/sem_printf");
	i = 0;
	char name[5] = "aaaa";
	while (i < 200)
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
	philo->is_ate = 0;
	philo->monitor = monitor;
	philo->last_meal = get_current_time();
}

int	destroy_semaphore(t_monitor *monitor, int i)
{
	char *sem_name;

	if (i == -1)
		i = monitor->num_philo;
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	while (i--)
	{
		sem_name = strcat(sem_name, "-");
		sem_end(monitor->forks[i], "/sem_");
	}
	return (0);
}

int	init_sem(t_monitor *monitor)
{
	int	i;
	char name[5];
	int j;

	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	sem_end(monitor->sem_printf, "/sem_print");
	i = 0;
	j = 0;
	ft_strlcpy(name, "    ", 5);
	while (i < 200)
	{
		sem_end(monitor->forks[i], name);
		i++;
		if (i % 50 == 0)
			j++;
		name[j]++;
	}
	ft_strlcpy(name, "    ", 5);
	monitor->sem_dead_flag = sem_open("/sem_dead_flag", O_CREAT, 0644, 1);
	if (monitor->sem_dead_flag == SEM_FAILED)
		return (sem_end(monitor->sem_philo_ready, "/sem_philo_ready"), 0);
	monitor->sem_printf = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (monitor->sem_printf == SEM_FAILED)
		return (sem_end(monitor->sem_philo_ready, "/sem_philo_ready"), 
			sem_end(monitor->sem_dead_flag, "/sem_dead_flag"), 0);
	j = 0;
	i = 0;
	while (i < monitor->num_philo)
	{
		monitor->forks[i] = sem_open(name, O_CREAT, 0644, 1);
		if (monitor->forks[i] == SEM_FAILED)
			return (destroy_semaphore(monitor, i), 0);
		i++;
		if (i % 50 == 0)
			j++;
		name[j]++;
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
	monitor->dead_flag = 0;
	monitor->num_of_meals = -2;
	monitor->time_start = get_current_time();
	if (argc == 6)
		monitor->num_of_meals = ft_atoi(argv[5]);
	if (monitor->num_philo <= 0 || monitor->num_philo > 200
		|| monitor->time_to_die <= 0 || monitor->time_to_eat <= 0
		|| monitor->time_to_sleep <= 0 || monitor->num_of_meals == -1
		|| monitor->num_of_meals == 0)
		return (print_error());
	if (init_sem(monitor) == 0)
		return (0);
	i = 0;
	while (i++ < monitor->num_philo)
		philo_init(&(monitor->philos[i - 1]), i, monitor);
	return (1);
}
