#include "philo.h"

int	set_all_philos_dead(t_philo *philo, int num_philo)
{
	int i;

	i = 0;
	while (i < num_philo)
	{
		philo[i].is_dead = 1;
		i++;
	}
	return 1;
}

int	check_all_philos_ate(t_philo *philo, int num_philo)
{
	int i;

	i = 0;
	while (i < num_philo)
	{
		if(philo[i].is_ate == 0)
			return 0;
		i++;
	}
	return 1;
}

int	loop_stop(t_monitor *monitor, t_philo *philo)
{
	size_t time;

	if (philo->is_dead)
	{
		monitor->dead_flag = 1;
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		pthread_mutex_unlock(&monitor->mutex_dead_flag);
		time = get_current_time();
		usleep(100); // to stop make other mutex run before
		// usleep(100); // to stop make other mutex run before
		pthread_mutex_lock(&monitor->mutex_printf);
		printf("%zu %d died\n", (time) - philo->monitor->time_start, philo->id);
		pthread_mutex_unlock(&monitor->mutex_printf);
		return (1);
	}
	else if (check_all_philos_ate(monitor->philos, monitor->num_philo))
	{
		set_all_philos_dead(monitor->philos, monitor->num_philo);
		pthread_mutex_unlock(&monitor->mutex_dead_flag);
		return (1);
	}
	return (0);
}

int	monitor_loop(t_monitor *monitor)
{
	t_philo *philo;
	int		i;

	i = 0;
	while (i < monitor->num_philo)
	{
		pthread_mutex_lock(&monitor->mutex_dead_flag);
		philo = &monitor->philos[i];
		if (loop_stop(monitor, philo))
			return 0;
		pthread_mutex_unlock(&monitor->mutex_dead_flag);
		i++;
	}
	return 1;
}
void	*ft_monitor(void *args)
{
	t_monitor *monitor;
	t_philo *philo;
	int i;

	monitor = (t_monitor *)args;
	while (1)
	{
		if (monitor_loop(monitor) == 0)
			return NULL;
	}
	return NULL;
}