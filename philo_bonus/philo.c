/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:02 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/04 02:13:52 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_if_even(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo, philo->time_to_eat / 2);
}

void	*ft_philo_dead(void *args)
{
	int			r_fork;
	int			l_fork;
	size_t		time_die;
	t_philo		*philo;

	philo = (t_philo *)args;
	while (1)
	{
		time_die = (unsigned long)philo->time_to_die;
		r_fork = philo->id - 1;
		l_fork = philo->id % philo->num_philo;
		if (sem_wait(philo->monitor->sem_printf) < 0)
			print_error(1, philo->monitor);
		if (get_current_time() - philo->last_meal > time_die)
		{
			printf("%zu\t%d\tdied\n",
				get_current_time() - philo->monitor->time_start, philo->id);
			sem_post(philo->monitor->forks[l_fork]);
			sem_post(philo->monitor->forks[r_fork]);
			exit(1);
		}
		sem_post(philo->monitor->sem_printf);
	}
	return (NULL);
}

void	ft_routine(t_philo *philo)
{
	int		step;
	int		i;
	int		num_meals;

	num_meals = 1;
	step = 0;
	i = 0;
	philo->last_meal = get_current_time();
	ft_sleep_if_even(philo);
	if (philo->num_of_meals != -2)
	{
		num_meals = philo->num_of_meals;
		step = 1;
	}
	if (pthread_create(&philo->pid, NULL, &ft_philo_dead, (void *)philo) == -1)
		print_error(1, philo->monitor);
	while (i < num_meals)
	{
		if (ft_eat(philo) == 0
			|| i + step == num_meals
			|| ft_philo_sleep_think(philo) == 0)
			break ;
		i += step;
	}
	pthread_detach(philo->pid);
}
