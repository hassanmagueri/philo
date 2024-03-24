/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:38:31 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/18 01:38:52 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct timeval		t_timeval;
typedef struct s_monitor	t_monitor;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				is_ate;
	int				is_dead;
	size_t			last_meal;
	pthread_mutex_t	*forks;
	t_monitor		*monitor;
}	t_philo;

struct s_monitor
{
	pthread_t		thread_id;
	int				num_philo;
	int				time_to_die;
	int				philo_ready;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				dead_flag;
	int				threads_ready;
	t_philo			*philos;
	size_t			time_start;
	pthread_mutex_t	mutex_philo_ready;
	pthread_mutex_t	mutex_dead_flag;
	pthread_mutex_t	*forks;
};

int		ft_atoi(const char	*str);
int		ft_usleep(t_philo *philo, size_t millisecond);
int		ft_philo_dead(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_philo_sleep_think(t_philo *philo);
int		destroy_free_all(t_monitor *monitor);
int		destroy_mutex(t_monitor *monitor, int i);
int		init_mutex(t_monitor *monitor);
int		monitor_init(t_monitor *monitor, int argc, char const *argv[]);
int		print_error(void);
int		print_state(t_philo *philo, char *str);

void	*ft_routine(void *args);
void	philo_init(t_philo *philo, int id, t_monitor *monitor);
void	*ft_monitor(void *args);
size_t	get_current_time(void);

#endif
