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
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>

typedef struct timeval		t_timeval;
typedef struct s_monitor	t_monitor;

typedef struct s_philo
{
	int				id;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				is_ate;
	size_t			last_meal;
	sem_t			**forks;
	pthread_t		thread_id;
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
	char			sem_name[6];
	t_philo			philos[200];
	size_t			time_start;
	sem_t			*sem_philo_ready;
	sem_t			*sem_dead_flag;
	sem_t			*sem_printf;
	sem_t			*forks[200];
};
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *str);
void	sem_end(sem_t *sem, char *name);
int		ft_atoi(const char	*str);
int		ft_usleep(size_t millisecond);
int		ft_eat(t_philo *philo);
int		ft_philo_sleep_think(t_philo *philo);
int		destroy_semaphore(t_monitor *monitor, int i);
int		init_sem(t_monitor *monitor);
int		monitor_init(t_monitor *monitor, int argc, char const *argv[]);
int		print_error(void);
int		destroy_all(t_monitor *monitor);
void	ft_routine(t_philo *philo);
void	print_state(t_philo *philo, char *str);
void	philo_init(t_philo *philo, int id, t_monitor *monitor);
size_t	get_current_time(void);

#endif
