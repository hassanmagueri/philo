#include "philo.h"
#include <string.h>

void    philo_init(t_philo *philo, int id, t_monitor *monitor)
{
	philo->id = id;
	philo->num_philo = monitor->num_philo;
	philo->time_to_die = monitor->time_to_die;
	philo->time_to_eat = monitor->time_to_eat;
	philo->time_to_sleep = monitor->time_to_sleep;
	philo->num_of_meals = monitor->num_of_meals;
	philo->l_fork = &monitor->forks[id % monitor->num_philo];
	philo->r_fork = &monitor->forks[id - 1];
	philo->forks_mt = monitor->forks_mt;
	philo->last_meal = get_current_time();
	philo->is_dead = 0;
	philo->is_ate = 0;
	// philo->last_meal = 0;
	philo->monitor = monitor;
}

// int	init_mutex_init(t_monitor *monitor)
// {
// 	int res;

// 	res = pthread_mutex_init(&monitor->mutex, NULL);
// 	if (res != 0)
// 		return 0;
// 	res = pthread_mutex_init(&monitor->is_ate_mutex, NULL);
// }



int init_forks(t_monitor *monitor)
{
	int	i;
	int res;

	i = 0;
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
		pthread_mutex_init(&monitor->forks_mt[i], NULL);
		i++;
	}
	return 1;
}

void    monitor_init(t_monitor *monitor, int argc, char const *argv[])
{
	int i;

	i = 0;
	monitor->num_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->threads_ready = 0;
	monitor->dead_flag = 0;
	monitor->num_of_meals = -1;
	if (argc == 6)
		monitor->num_of_meals = ft_atoi(argv[5]);
	i = 0;
	monitor->philos = malloc(sizeof(t_philo) * monitor->num_philo);
	while (i < monitor->num_philo)
	{
		philo_init(&(monitor->philos[i]), i + 1, monitor);
		i++;
	}
	monitor->time_start = get_current_time();
}

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

void	*ft_monitor(void *args)
{
	t_monitor *monitor;
	t_philo *philo;
	int i;
	int is_dead;

	is_dead = 0;
	monitor = (t_monitor *)args;
	while (1)
	{
		pthread_mutex_lock(&monitor->mutex);//! dead lock
		i = 0;
		while (i < monitor->num_philo)
		{
			philo = &monitor->philos[i];
			if (philo->is_dead)
			{
				set_all_philos_dead(monitor->philos, monitor->num_philo);
				printf("%zu %d died\n", get_current_time()  - philo->monitor->time_start , philo->id);
				pthread_mutex_unlock(&monitor->mutex);
				// exit(1);
				return NULL;
			}
			else if (check_all_philos_ate(monitor->philos, monitor->num_philo))
			{
				set_all_philos_dead(monitor->philos, monitor->num_philo);
				pthread_mutex_unlock(&monitor->mutex);
				return NULL;
			}
			i++;
		}
		pthread_mutex_unlock(&monitor->mutex);
	}
	return NULL;
}

void	*ft_routine(void *args)
{
	t_philo *philo;
	int	step;
	int	i;
	int num_meals;

	philo = (t_philo *)args;
	num_meals = 1;
	step = 0;
	i = 0;
	if(philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	if(philo->num_of_meals != -1)
	{
		num_meals = philo->num_of_meals;
		step = 1;
	}
	while (i < num_meals)
	{
		// printf("philo %d is dead %d\n", philo->id, philo->is_dead);
		pthread_mutex_lock(&philo->monitor->mutex);
		if (philo->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->monitor->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->monitor->mutex);
		if (ft_eat(philo) == 0 || i + step == num_meals)
			break;
		// if(i >= num_meals)
		// 	break;
		ft_philo_sleep(philo);
		i += step;
		ft_philo_think(philo);
	}
	pthread_mutex_lock(&philo->monitor->mutex);
	philo->is_ate = 1;
	pthread_mutex_unlock(&philo->monitor->mutex);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t *ths_ph;
	t_philo	*philo;
	t_monitor monitor;
	int i;

	monitor_init(&monitor, argc, argv);
	// printf("%d", philo->num_of_meals);
	i = 0;
	while (i < monitor.num_philo)
	{
		philo = &monitor.philos[i];
		pthread_create(&philo->thread_id, NULL, &ft_routine, (void *) philo);
		i++;
	}
	pthread_create(&monitor.thread_id, NULL, &ft_monitor, (void *) &monitor);
	i = 0;
	// sleep(1);
	// printf("-------is_dead : %d\n", monitor.philos[0].is_dead);
	// printf("-------is_dead : %d\n", monitor.philos[1].is_dead);
	// printf("-------is_dead : %d\n", monitor.philos[2].is_dead);
	// printf("-------is_dead : %d\n", monitor.philos[3].is_dead);
	while (i < monitor.num_philo)
		pthread_join(monitor.philos[i++].thread_id, NULL);
	pthread_join(monitor.thread_id, NULL);
	return 0;
}
