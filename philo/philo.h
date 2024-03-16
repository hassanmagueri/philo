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
	int				id;
	int 			num_philo;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			num_of_meals;
	int				is_ate;
	int				is_dead;
	int				is_ready;
	size_t			last_meal;
	t_state			state;
	pthread_mutex_t	*forks_mt;
	pthread_t		thread_id;
	size_t			delay;
	t_monitor		*monitor;
} t_philo;

struct s_monitor
{
	pthread_t		thread_id;
	int 			num_philo;
    int 			time_to_die;
	int				philo_ready;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			num_of_meals;
	int				dead_flag;
	int				threads_ready;
	t_philo			*philos;
	t_fork			*forks;
	size_t			time_start;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_philo_ready;
	pthread_mutex_t	mutex_dead_flag;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_is_ate;
	pthread_mutex_t	*forks_mt;
};


int		ft_atoi(const char	*str);
int		ft_usleep(size_t millisecond);
int		ft_eat(t_philo *philo);
int		ft_philo_sleep(t_philo *philo);
size_t	get_current_time(void);
int		ft_philo_think(t_philo *philo);

void	*ft_routine(void *args);
int		print_state(t_philo *philo, char *str);

void    philo_init(t_philo *philo, int id, t_monitor *monitor);
int		destroy_free_all(t_monitor *monitor);
int		destroy_mutex(t_monitor *monitor, int i);
int 	init_mutex(t_monitor *monitor);
int    	monitor_init(t_monitor *monitor, int argc, char const *argv[]);
void	*ft_monitor(void *args);