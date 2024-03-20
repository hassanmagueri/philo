/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:09 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/20 13:58:20 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	destroy_free_all(t_monitor *monitor)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_destroy(&monitor->mutex_philo_ready);
// 	pthread_mutex_destroy(&monitor->mutex_dead_flag);
// 	pthread_mutex_destroy(&monitor->mutex_printf);
// 	while (i < monitor->num_philo)
// 		pthread_mutex_destroy(&monitor->forks[i++]);
// 	free(monitor->forks);
// 	free(monitor->philos);
// 	return (0);
// }

void	philo_init(t_philo *philo, int id, t_monitor *monitor)
{
	philo->id = id;
	philo->num_philo = monitor->num_philo;
	philo->time_to_die = monitor->time_to_die;
	philo->time_to_eat = monitor->time_to_eat;
	philo->time_to_sleep = monitor->time_to_sleep;
	philo->num_of_meals = monitor->num_of_meals;
	philo->forks = monitor->forks;
	philo->is_dead = 0;
	philo->is_ate = 0;
	philo->monitor = monitor;
	philo->last_meal = get_current_time();
}

int	destroy_semaphore(t_monitor *monitor, int i)
{
	char *sem_name;

	if (i == -1)
		i = monitor->num_philo;
	sem_end(monitor->sem_philo_ready, "/sem_philo_ready");
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	while (i--)
	{
		sem_name = strcat(sem_name, "-");
		sem_end(monitor->forks[i], "/sem_");
	}
	free(monitor->forks);
	return (0);
}

void	sem_end(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

int	init_sem(t_monitor *monitor)
{
	int	i;
	// char name[4];
	i = 0;
	sem_end(monitor->sem_philo_ready, "/sem_philo_ready");
	sem_end(monitor->sem_dead_flag, "/sem_dead_flag");
	sem_end(monitor->sem_printf, "/sem_print");
	char name[] = "aaaa";
	int j = 0;
	i = 0;
	monitor->forks = malloc(sizeof(sem_t *) * monitor->num_philo);
	while (i < 200)
	{
		sem_end(monitor->forks[i], name);
		// sem_post(monitor->forks[i]);
		i++;
		if (i % 50)
			j++;
		name[j]++;
	}
	// sem_unlink("/sem_");
	strcpy(name, "aaaa");
	monitor->sem_philo_ready = sem_open("/sem_philo_ready", O_CREAT, 0644, 1);
	if (monitor->sem_philo_ready == SEM_FAILED)
		return (print_error(), 0);
	monitor->sem_dead_flag = sem_open("/sem_dead_flag", O_CREAT, 0644, 1);
	if (monitor->sem_dead_flag == SEM_FAILED)
		return (sem_end(monitor->sem_philo_ready, "/sem_philo_ready"), 0);
	monitor->sem_printf = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (monitor->sem_printf == SEM_FAILED)
		return (sem_end(monitor->sem_philo_ready, "/sem_philo_ready"), 
			sem_end(monitor->sem_dead_flag, "/sem_dead_flag"), 0);
	if (!monitor->forks)
		return (destroy_semaphore(monitor, 0));
	// bzero(name, 3);///  libft
	// strcpy(name, "   ");
	j = 0;
	i = 0;
	while (i < monitor->num_philo)
	{
		monitor->forks[i] = sem_open(name, O_CREAT, 0644, 1);
		if (monitor->forks[i] == SEM_FAILED)
			return (destroy_semaphore(monitor, i), 0);
		i++;
		if (i % 50)
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
	monitor->philo_ready = 0;
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
	monitor->philos = malloc(sizeof(t_philo) * monitor->num_philo);
	if (!monitor->philos)
		return (destroy_semaphore(monitor, -1));
	while (i++ < monitor->num_philo)
		philo_init(&(monitor->philos[i - 1]), i, monitor);
	return 1;
}
