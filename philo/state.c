/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/30 06:46:36 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_philo *philo, char *str)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->mutex_flag);
	if (philo->monitor->dead_flag == 1)
	{
		pthread_mutex_unlock(&monitor->mutex_flag);
		return (-1);
	}
	if (ft_strncmp(str, "is eating", 10) == 0)
		philo->num_eat += 1;
	printf("%zu %d %s\n", get_current_time() - philo->monitor->time_start,
		philo->id, str);
	pthread_mutex_unlock(&monitor->mutex_flag);
	return (1);
}

int	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(NULL, philo->time_to_die);
	pthread_mutex_lock(&philo->monitor->mutex_flag);
	philo->monitor->dead_flag = 1;
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->monitor->mutex_flag);
	print_state(philo, "died");
	return (0);
}

int	ft_eat(t_philo *philo)
{
	t_monitor	*monitor;
	int			right;
	int			left;

	right = philo->id % philo->num_philo;
	left = philo->id - 1;
	monitor = philo->monitor;
	if (philo->num_philo == 1)
		return (handle_one_philo(philo));
	pthread_mutex_lock(&monitor->forks[right]);
	if (print_state(philo, "has taken a fork") == -1)
		return (0);
	pthread_mutex_lock(&philo->monitor->forks[left]);
	if (print_state(philo, "has taken a fork") == -1)
		return (0);
	print_state(philo, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(&monitor->forks[right]);
	return (pthread_mutex_unlock(&monitor->forks[left]), 1);
}

int	ft_philo_sleep_think(t_philo *philo)
{
	int	res;

	res = print_state(philo, "is sleeping");
	if (res == -1)
		return (0);
	if (ft_usleep(philo, philo->time_to_sleep))
		return (0);
	print_state(philo, "is thinking");
	return (1);
}
