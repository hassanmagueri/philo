/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:02 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/22 14:57:21 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_if_even(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
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
	while (i < num_meals)
	{
		if (ft_eat(philo) == 0 || i + step == num_meals
			|| ft_philo_sleep_think(philo) == 0)
			break ;
		i += step;
	}
}
