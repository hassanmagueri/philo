/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:09 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/25 16:58:11 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_free_all(t_monitor *monitor)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&monitor->mutex_philo_ready);
	pthread_mutex_destroy(&monitor->mutex_flag);
	while (i < monitor->num_philo)
		pthread_mutex_destroy(&monitor->forks[i++]);
	free(monitor->forks);
	free(monitor->philos);
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
	philo->is_dead = 0;
	philo->is_ate = 0;
	philo->monitor = monitor;
	philo->last_meal = get_current_time();
}

int	destroy_mutex(t_monitor *monitor, int i)
{
	if (i == -1)
		i = monitor->num_philo;
	pthread_mutex_destroy(&monitor->mutex_philo_ready);
	pthread_mutex_destroy(&monitor->mutex_flag);
	while (i--)
		pthread_mutex_destroy(&monitor->forks[i]);
	free(monitor->forks);
	return (0);
}

int	init_mutex(t_monitor *monitor)
{
	int	i;
	int	res;

	i = 0;
	res = pthread_mutex_init(&monitor->mutex_philo_ready, NULL);
	if (res != 0)
		return (0);
	res = pthread_mutex_init(&monitor->mutex_flag, NULL);
	if (res != 0)
		return (pthread_mutex_destroy(&monitor->mutex_philo_ready), 0);
	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->num_philo);
	if (!monitor->forks)
		return (pthread_mutex_destroy(&monitor->mutex_philo_ready),
			pthread_mutex_destroy(&monitor->mutex_flag), 0);
	while (i < monitor->num_philo)
	{
		res = pthread_mutex_init(&monitor->forks[i], NULL);
		if (res != 0)
			return (destroy_mutex(monitor, i), 0);
		i++;
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
	if (argc == 6)
		monitor->num_of_meals = ft_atoi(argv[5]);
	if (monitor->num_philo <= 0 || monitor->num_philo > 200
		|| monitor->time_to_die <= 0 || monitor->time_to_eat <= 0
		|| monitor->time_to_sleep <= 0 || monitor->num_of_meals == -1)
		return (print_error());
	if (init_mutex(monitor) == 0)
		return (0);
	i = 0;
	monitor->philos = malloc(sizeof(t_philo) * monitor->num_philo);
	if (!monitor->philos)
		return (destroy_mutex(monitor, -1));
	while (i++ < monitor->num_philo)
		philo_init(&(monitor->philos[i - 1]), i, monitor);
	monitor->time_start = get_current_time();
	return (1);
}
