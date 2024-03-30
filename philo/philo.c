/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:02 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/30 19:54:34 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	ft_philo_ate(t_philo *philo)
{
	if (philo->num_of_meals < 0)
		return ;
	pthread_mutex_lock(&philo->monitor->mutex_flag);
	philo->is_ate = 1;
	pthread_mutex_unlock(&philo->monitor->mutex_flag);
}

void	ft_wait_all_philos(t_philo *philo)
{
	int	a;

	a = 0;
	pthread_mutex_lock(&philo->monitor->mutex_philo_ready);
	philo->monitor->philo_ready += 1;
	while (philo->monitor->philo_ready != philo->num_philo)
	{
		pthread_mutex_unlock(&philo->monitor->mutex_philo_ready);
		a++;
		pthread_mutex_lock(&philo->monitor->mutex_philo_ready);
	}
	pthread_mutex_unlock(&philo->monitor->mutex_philo_ready);
}

int	ft_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->mutex_flag);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&philo->monitor->mutex_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->mutex_flag);
	return (0);
}

void	ft_sleep_if_even(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo, philo->time_to_eat / 2);
}

void	*ft_routine(void *args)
{
	t_philo	*philo;
	int		step;
	int		i;
	int		num_meals;

	philo = (t_philo *)args;
	num_meals = 1;
	step = 0;
	i = 0;
	ft_wait_all_philos(philo);
	philo->last_meal = get_current_time();
	ft_sleep_if_even(philo);
	if (philo->num_of_meals != -2)
	{
		num_meals = philo->num_of_meals;
		step = 1;
	}
	while (i < num_meals)
	{
		if (ft_eat(philo) == 0 || i + step == num_meals
			|| ft_philo_sleep_think(philo) == 0)
			break ;
		i += step;
	}
	return (ft_philo_ate(philo), NULL);
}
