/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:24 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/30 19:54:40 by emagueri         ###   ########.fr       */
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
		if (philo[i].num_eat != philo->num_of_meals)
			return (0);
		i++;
	}
	return (1);
}

int	loop_stop(t_monitor *monitor, t_philo *philo)
{
	if (check_all_philos_ate(monitor->philos, monitor->num_philo))
	{
		// printf("all philos eat\n");
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		pthread_mutex_unlock(&monitor->mutex_flag);
		return (1);
	}
	else if (philo->is_dead)
	{
		monitor->dead_flag = 1;
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		printf("%zu %d died\n",
			get_current_time() - philo->monitor->time_start, philo->id);
		pthread_mutex_unlock(&monitor->mutex_flag);
		return (1);
	}
	return (0);
}

int	ft_philo_dead(t_philo *philo)
{
	t_monitor	*monitor;
	int			r_fork;
	int			l_fork;
	size_t		time_die;

	time_die = (unsigned long)philo->time_to_die;
	r_fork = philo->id % philo->num_philo;
	l_fork = philo->id - 1;
	monitor = philo->monitor;
	if (get_current_time() - philo->last_meal >= time_die)
	{
		monitor->dead_flag = 1;
		philo->is_dead = 1;
		pthread_mutex_unlock(&monitor->mutex_flag);
		pthread_mutex_unlock(&monitor->forks[r_fork]);
		pthread_mutex_unlock(&monitor->forks[l_fork]);
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
			// if (check_all_philos_ate(monitor->philos, monitor->num_of_meals) && 
			ft_philo_dead(&monitor->philos[i]);
				// return (NULL);
			pthread_mutex_unlock(&monitor->mutex_flag);
			i++;
		}
	}
	return (NULL);
}
