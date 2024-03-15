#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

typedef struct timeval t_timeval;

typedef enum e_state
{
	NOTHING,
	THINKING,
	TAKE_ONE_FORK,
	EATING,
	SLEEPING
} t_state;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
} t_fork;

typedef struct s_monitor t_monitor;

typedef struct s_philo
{
	int	id;
	int 				num_philo;
    int 				time_to_die;
    int 				time_to_eat;
    int 				time_to_sleep;
    int 				num_of_meals;
	int					is_ate;
	int	is_dead;
	size_t			last_meal;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_state			state;
	pthread_mutex_t	*forks_mt;
	pthread_t			thread_id;
	t_monitor		*monitor;
} t_philo;

struct s_monitor
{
	pthread_t		thread_id;
	int 			num_philo;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			num_of_meals;
	int				dead_flag;
	int				threads_ready;
	t_philo			*philos;
	t_fork			*forks;
	size_t			time_start;
	pthread_mutex_t	threads_ready_mutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks_mt;
	pthread_mutex_t	time_start_mutex;
	pthread_mutex_t	mutex_pid;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	is_ate_mutex;
};


int	ft_atoi(const char	*str);
int ft_usleep(size_t millisecond);
int    ft_eat(t_philo *philo);
void    ft_philo_sleep(t_philo *philo);
size_t	get_current_time(void);
void    ft_philo_think(t_philo *philo);

void *ft_routine(void *args);
int	print_state(t_philo *philo, char *str);
