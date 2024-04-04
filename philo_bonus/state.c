/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/04 00:57:02 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *str)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	if (sem_wait(monitor->sem_printf) < 0)
		print_error(1, monitor);
	printf("%zu\t%d\t%s\n", get_current_time() - philo->monitor->time_start,
		philo->id, str);
	if (sem_post(monitor->sem_printf) < 0)
		print_error(1, monitor);
}

int	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(NULL, philo->time_to_die);
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
	if (sem_wait(monitor->forks[right]) < 0)
		print_error(1, monitor);
	print_state(philo, "has taken a fork");
	if (sem_wait(monitor->forks[left]) < 0)
		print_error(1, monitor);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	if (sem_wait(monitor->sem_printf) < 0)
		print_error(1, monitor);
	philo->last_meal = get_current_time();
	sem_post(monitor->sem_printf);
	ft_usleep(philo, philo->time_to_eat);
	if (sem_post(monitor->forks[left]) < 0
		|| sem_post(monitor->forks[right]) < 0)
		print_error(1, monitor);
	return (1);
}

int	ft_philo_sleep_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo, philo->time_to_sleep);
	print_state(philo, "is thinking");
	return (1);
}
