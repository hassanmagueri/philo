/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:48:01 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/18 00:39:06 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char	*str)
{
	long long	num;
	int			sign;
	int			i;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - 48;
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i] != 0)
		return (-1);
	return (num * sign);
}
