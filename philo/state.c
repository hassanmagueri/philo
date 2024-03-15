#include "philo.h"

int	print_state(t_philo *philo, char *str)
{
	t_monitor *monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->mutex);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(&monitor->mutex);
		return (-1);
	}
	else
		printf("%zu %d %s\n", get_current_time()  - philo->monitor->time_start , philo->id, str);
	pthread_mutex_unlock(&monitor->mutex);
	return (1);
}

int    ft_eat(t_philo *philo)
{
	t_fork *fork_l;
	t_fork *fork_r;
	t_monitor *monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&philo->monitor->forks_mt[philo->id % philo->num_philo]);
	philo->state = TAKE_ONE_FORK;
	print_state(philo, "has taken a fork");
	if (philo->num_philo == 1)
	{
		print_state(philo, "died");
		return 0;
	}
	pthread_mutex_lock(&philo->monitor->forks_mt[philo->id -1]);
	if (get_current_time() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&monitor->mutex);
		monitor->dead_flag = 1;
		philo->is_dead = 1;
		pthread_mutex_unlock(&monitor->mutex);
		pthread_mutex_unlock(&philo->monitor->forks_mt[philo->id % philo->monitor->num_philo]);
		pthread_mutex_unlock(&philo->monitor->forks_mt[philo->id -1]);
		return 0;
	}
	philo->last_meal = get_current_time();
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->monitor->forks_mt[philo->id % philo->monitor->num_philo]);
	pthread_mutex_unlock(&philo->monitor->forks_mt[philo->id -1]);
	return 1;
}

void    ft_philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void    ft_philo_think(t_philo *philo)
{
	philo->state = THINKING;
	print_state(philo, "is thinking");
}
