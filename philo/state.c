#include "philo.h"


int	print_state(t_philo *philo, char *str)
{
	t_monitor *monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->mutex_dead_flag);
	if (philo->monitor->dead_flag == 1)
	{
		pthread_mutex_unlock(&monitor->mutex_dead_flag);
		return (-1);
	}
	pthread_mutex_unlock(&monitor->mutex_dead_flag);
	pthread_mutex_lock(&monitor->mutex_printf);
	printf("%zu %d %s\n", get_current_time() - philo->monitor->time_start, philo->id, str);
	pthread_mutex_unlock(&monitor->mutex_printf);
	return (1);
}

int	ft_philo_dead(t_philo *philo)
{
	t_monitor *monitor;
	int r_fork;
	int l_fork;

	r_fork = philo->id % philo->num_philo;
	l_fork = philo->id - 1;
	monitor = philo->monitor;
	if (get_current_time() - philo->last_meal > (unsigned long)philo->time_to_die)
	{
		pthread_mutex_lock(&monitor->mutex_dead_flag);
		monitor->dead_flag = 1;
		philo->is_dead = 1;
		pthread_mutex_unlock(&monitor->mutex_dead_flag);
		pthread_mutex_unlock(&monitor->forks_mt[r_fork]);
		pthread_mutex_unlock(&monitor->forks_mt[l_fork]);
		return (1);
	}
	return (0);
}

int handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->time_to_die);
	print_state(philo, "died");
	return (0);
}

int    ft_eat(t_philo *philo)
{
	t_monitor *monitor;
	int res;
	int r_fork;
	int l_fork;

	r_fork = philo->id % philo->num_philo;
	l_fork = philo->id - 1;
	monitor = philo->monitor;
	if (philo->num_philo == 1)
		return (handle_one_philo(philo));
	pthread_mutex_lock(&monitor->forks_mt[r_fork]);
	philo->state = TAKE_ONE_FORK;
	if (print_state(philo, "has taken a fork") == -1)
		return (0);
	pthread_mutex_lock(&philo->monitor->forks_mt[l_fork]);
	if (ft_philo_dead(philo))
		return (0);
	res = print_state(philo, "has taken a fork");
	if (res == -1)
		return (0);
	print_state(philo, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&monitor->forks_mt[r_fork]);
	pthread_mutex_unlock(&monitor->forks_mt[l_fork]);
	return 1;
}

int    ft_philo_sleep(t_philo *philo)
{
	int res;

	res = print_state(philo, "is sleeping");
	if (res == -1)
		return 0;
	ft_usleep(philo->time_to_sleep);
	return 1;
}

int    ft_philo_think(t_philo *philo)
{
	int	res;

	res = print_state(philo, "is thinking");
	if (res == -1)
		return 0;
	return 1;
}
