/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:24 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/25 17:21:05 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_all_philos_dead(t_philo *philo, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		philo[i].is_dead = 1;
		i++;
	}
	return (1);
}

int	check_all_philos_ate(t_philo *philo, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (philo[i].is_ate == 0)
			return (0);
		i++;
	}
	return (1);
}

int	loop_stop(t_monitor *monitor, t_philo *philo)
{
	if (philo->is_dead)
	{
		monitor->dead_flag = 1;
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		printf("%zu %d died\n",
			get_current_time() - philo->monitor->time_start, philo->id);
		pthread_mutex_unlock(&monitor->mutex_flag);
		return (1);
	}
	else if (check_all_philos_ate(monitor->philos, monitor->num_philo))
	{
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		pthread_mutex_unlock(&monitor->mutex_flag);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *args)
{
	t_monitor	*monitor;
	t_philo		*philo;
	int			i;

	monitor = (t_monitor *)args;
	while (1)
	{
		i = 0;
		while (i < monitor->num_philo)
		{
			pthread_mutex_lock(&monitor->mutex_flag);
			philo = &monitor->philos[i];
			if (loop_stop(monitor, philo))
				return (NULL);
			pthread_mutex_unlock(&monitor->mutex_flag);
			i++;
		}
	}
	return (NULL);
}
