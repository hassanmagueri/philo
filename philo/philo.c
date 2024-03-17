#include "philo.h"
#include <string.h>

int destroy_free_all(t_monitor *monitor)
{
	int i;
	pthread_mutex_t *mt;

	// i = monitor->num_philo;
	i = 0;
	free(monitor->forks_mt);
	free(monitor->philos);
	pthread_mutex_destroy(&monitor->mutex);
	mt = &monitor->forks_mt[0];
	pthread_mutex_destroy(mt);
	// while (i < monitor->num_philo)
	// 	pthread_mutex_destroy(&monitor->forks_mt[i++]);
	return 0;
}

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

int	ft_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->mutex_dead_flag);
	if(philo->is_dead)
	{
		pthread_mutex_unlock(&philo->monitor->mutex_dead_flag);
		return 1;
	}
	pthread_mutex_unlock(&philo->monitor->mutex_dead_flag);
	return 0;
}

void	*ft_routine(void *args)
{
	t_philo *philo;
	int	step;
	int	i;
	int num_meals;

	philo = (t_philo *)args;
	ft_wait_all_philos(philo);
	pthread_mutex_lock(&philo->monitor->mutex_printf);
	philo->monitor->time_start = get_current_time();
	pthread_mutex_unlock(&philo->monitor->mutex_printf);
	philo->last_meal = get_current_time();
	num_meals = 1;
	step = 0;
	i = 0;
	if(philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	if (philo->num_of_meals != -2)
	{
		num_meals = philo->num_of_meals;
		step = 1;
	}
	while (i < num_meals && !ft_philo_is_dead(philo))
	{
		if (ft_eat(philo) == 0)
			break;
		if (i + step == num_meals
			|| ft_philo_sleep(philo) == 0 || ft_philo_think(philo) == 0)
			break;
		i += step;
	}
	return (ft_philo_ate(philo),NULL);
}
void	leak(){system("leaks a.out");}

int main(int argc, char const *argv[])
{
	t_philo	*philos;
	t_monitor monitor;
	int i;

	// atexit(leak);
	if(argc != 5 && argc != 6)
		return print_error();
	if (monitor_init(&monitor, argc, argv) == 0)
		return (1);
	// exit()
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
