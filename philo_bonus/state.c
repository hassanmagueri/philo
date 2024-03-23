/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/22 17:51:13 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *str)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	sem_wait(monitor->sem_printf);
	printf("%zu\t%d\t%s\n", get_current_time() - philo->monitor->time_start,
		philo->id, str);
	sem_post(monitor->sem_printf);
}

int	ft_philo_dead(t_philo *philo)
{
	t_monitor	*monitor;
	int			r_fork;
	int			l_fork;
	size_t		time_die;

	time_die = (unsigned long)philo->time_to_die;
	r_fork = philo->id - 1;
	l_fork = philo->id % philo->num_philo;
	monitor = philo->monitor;
	if (get_current_time() - philo->last_meal >= time_die)
	{
		sem_post(monitor->sem_dead_flag);
		sem_wait(monitor->sem_printf);
		printf("%zu\t%d\tdied\n", get_current_time() - monitor->time_start,
			philo->id);
		sem_post(monitor->sem_dead_flag);
		sem_post(monitor->forks[r_fork]);
		sem_post(monitor->forks[l_fork]);
		exit(1);
	}
	return (0);
}

int	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(NULL, philo->time_to_die);
	sem_wait(philo->monitor->sem_dead_flag);
	sem_post(philo->monitor->sem_dead_flag);
	print_state(philo, "died");
	exit (0);
}

int	ft_eat(t_philo *philo)
{
	t_monitor	*monitor;
	int			right;
	int			left;

	right = philo->id - 1;
	left = philo->id % philo->num_philo;
	monitor = philo->monitor;
	if (philo->num_philo == 1)
		return (handle_one_philo(philo));
	ft_philo_dead(philo);
	sem_wait(monitor->forks[right]);
	if (ft_philo_dead(philo))
		return (0);
	print_state(philo, "has taken a fork");
	sem_wait(monitor->forks[left]);
	if (ft_philo_dead(philo))
		return (0);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo, philo->time_to_eat);
	sem_post(monitor->forks[left]);
	sem_post(monitor->forks[right]);
	return (1);
}

int	ft_philo_sleep_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo, philo->time_to_sleep);
	print_state(philo, "is thinking");
	return (1);
}
