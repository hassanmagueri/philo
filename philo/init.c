#include "philo.h"

int print_error(void)
{
	write(2, "error\n", 6);
	return 0;
}

void    philo_init(t_philo *philo, int id, t_monitor *monitor)
{
	philo->id = id;
	philo->num_philo = monitor->num_philo;
	philo->time_to_die = monitor->time_to_die;
	philo->time_to_eat = monitor->time_to_eat;
	philo->time_to_sleep = monitor->time_to_sleep;
	philo->num_of_meals = monitor->num_of_meals;
	philo->forks_mt = monitor->forks_mt;
	philo->is_dead = 0;
	philo->is_ate = 0;
	philo->monitor = monitor;
	philo->last_meal = get_current_time();
}


int destroy_mutex(t_monitor *monitor, int i)
{
	if (i == -1)
		i = monitor->num_philo;
	free(monitor->philos);
	pthread_mutex_destroy(&monitor->mutex);
	while (i--)
		pthread_mutex_destroy(&monitor->forks_mt[i]);
	free(monitor->forks_mt);
	return 0;
}

int init_mutex(t_monitor *monitor)
{
	int	i;
	int res;

	i = 0;
	res = pthread_mutex_init(&monitor->mutex_philo_ready, NULL);
	res = pthread_mutex_init(&monitor->mutex_dead_flag, NULL);
	res = pthread_mutex_init(&monitor->mutex_printf, NULL);
	res = pthread_mutex_init(&monitor->mutex_is_ate, NULL);
	res = pthread_mutex_init(&monitor->mutex, NULL);
	if (res != 0)
		return 0;
	monitor->forks_mt = malloc(sizeof(pthread_mutex_t) * monitor->num_philo);
	if (!monitor->forks_mt)
	{
		pthread_mutex_destroy(&monitor->mutex);
		return 0;
	}
	while (i < monitor->num_philo)
	{
		res = pthread_mutex_init(&monitor->forks_mt[i], NULL);
		if (res != 0)
			return (destroy_mutex(monitor, i));
		i++;
	}
	return 1;
}

int    monitor_init(t_monitor *monitor, int argc, char const *argv[])
{
	int i;

	monitor->num_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->philo_ready = 0;
	monitor->dead_flag = 0;
	monitor->num_of_meals = -2;
	if (argc == 6)
		monitor->num_of_meals = ft_atoi(argv[5]);
	if (monitor->num_philo <= 0 || monitor->num_philo > 200 
		|| monitor->time_to_die <= -1 || monitor->time_to_eat <= -1
		|| monitor->time_to_sleep <= -1 || monitor->num_of_meals == -1)
		return (print_error());
	if (init_mutex(monitor) == 0)
		return (0);
	i = 0;
	monitor->philos = malloc(sizeof(t_philo) * monitor->num_philo);
	if (!monitor->philos)
		return destroy_mutex(monitor, -1);
	while (i++ < monitor->num_philo)
		philo_init(&(monitor->philos[i - 1]), i, monitor);
	return (monitor->time_start = get_current_time(), 1);
}
