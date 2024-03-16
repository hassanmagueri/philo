#include "philo.h"
#include <string.h>

void ft_philo_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->mutex_dead_flag);
	philo->is_ate = 1;
	pthread_mutex_unlock(&philo->monitor->mutex_dead_flag);
}

void ft_wait_all_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->mutex_philo_ready);
	philo->monitor->philo_ready += 1;
	while (philo->monitor->philo_ready != philo->num_philo)
	{
		pthread_mutex_unlock(&philo->monitor->mutex_philo_ready);
		;
		pthread_mutex_lock(&philo->monitor->mutex_philo_ready);
	}
	pthread_mutex_unlock(&philo->monitor->mutex_philo_ready);
}

void	*ft_routine(void *args)
{
	t_philo *philo;
	int	step;
	int	i;
	int num_meals;

	philo = (t_philo *)args;
	ft_wait_all_philos(philo);
	num_meals = 1;
	step = 0;
	i = 0;
	if(philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	if (philo->num_of_meals != -1)
	{
		num_meals = philo->num_of_meals;
		step = 1;
	}
	while (i < num_meals)
	{
		if (ft_eat(philo) == 0 || i + step == num_meals
			|| ft_philo_sleep(philo) == 0 || ft_philo_think(philo) == 0)
			break;
		i += step;
	}
	return (ft_philo_ate(philo), NULL);
}

int main(int argc, char const *argv[])
{
	t_philo	*philos;
	t_monitor monitor;
	int i;

	if (monitor_init(&monitor, argc, argv) == 0)
		return 1;
	i = 0;
	philos = monitor.philos;
	while (i < monitor.num_philo)
	{
		pthread_create(&philos[i].thread_id, NULL, &ft_routine, (void *) &philos[i]);
		i++;
	}
	pthread_create(&monitor.thread_id, NULL, &ft_monitor, (void *) &monitor);
	i = 0;
	while (i < monitor.num_philo)
		pthread_join(monitor.philos[i++].thread_id, NULL);
	pthread_join(monitor.thread_id, NULL);
	destroy_free_all(&monitor);
	return 0;
}
