/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/20 16:11:16 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_philo *philo, char *str)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	// pthread_mutex_lock(&monitor->mutex_dead_flag);
	sem_wait(monitor->sem_dead_flag);
	if (philo->monitor->dead_flag == 1)
	{
		// pthread_mutex_unlock(&monitor->mutex_dead_flag);
		sem_post(monitor->sem_dead_flag);
		return (-1);
	}
	// pthread_mutex_unlock(&monitor->mutex_dead_flag);
	sem_post(monitor->sem_dead_flag);
	// pthread_mutex_lock(&monitor->mutex_printf);
	sem_wait(monitor->sem_printf);
	printf("%zu %d %s\n", get_current_time() - philo->monitor->time_start,
		philo->id, str);
	// pthread_mutex_unlock(&monitor->mutex_printf);
	sem_post(monitor->sem_printf);
	return (1);
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
	if (get_current_time() - philo->last_meal > time_die)
	{
		// pthread_mutex_lock(&monitor->mutex_dead_flag);
		// print_state(philo, "died");
		
		sem_post(monitor->sem_dead_flag);
		// pthread_mutex_lock(&monitor->mutex_printf);
		sem_wait(monitor->sem_printf);
		printf("%zu %d died\n", get_current_time() - philo->monitor->time_start,
			philo->id);
		// sem_wait(monitor->sem_printf);
		monitor->dead_flag = 1;
		philo->is_dead = 1;
		kill(0, SIGINT);
		// pthread_mutex_unlock(&monitor->mutex_dead_flag);
		sem_post(monitor->sem_dead_flag);
		// pthread_mutex_unlock(&monitor->forks[r_fork]);
		sem_post(monitor->forks[r_fork]);
		// pthread_mutex_unlock(&monitor->forks[l_fork]);
		sem_post(monitor->forks[l_fork]);
		sem_wait(monitor->sem_dead_flag);
		sem_wait(monitor->sem_printf);
		return (1);
	}
	return (0);
}

int	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->time_to_die);
	// pthread_mutex_lock(&philo->monitor->mutex_dead_flag);
	sem_wait(philo->monitor->sem_dead_flag);
	philo->monitor->dead_flag = 1;
	philo->is_dead = 1;
	// pthread_mutex_unlock(&philo->monitor->mutex_dead_flag);
	sem_post(philo->monitor->sem_dead_flag);
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
	if (ft_philo_dead(philo))
		return (0);
	// pthread_mutex_lock(&monitor->forks[right]);
	sem_wait(monitor->forks[right]);
	// printf("philo %d\n", philo->id);
	if (ft_philo_dead(philo))
		return (0);
	if (print_state(philo, "has taken a fork") == -1)
		return (0);
	// pthread_mutex_lock(&philo->monitor->forks[left]);
	sem_wait(monitor->forks[left]);
	if (ft_philo_dead(philo))
		return (0);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	// pthread_mutex_unlock(&monitor->forks[right]);
	sem_post(monitor->forks[left]);
	// pthread_mutex_unlock(&monitor->forks[left]);
	sem_post(monitor->forks[right]);

	return (1);
}

int	ft_philo_sleep_think(t_philo *philo)
{
	int	res;

	res = print_state(philo, "is sleeping");
	if (res == -1)
		return (0);
	ft_usleep(philo->time_to_sleep);
	print_state(philo, "is thinking");
	return (1);
}
