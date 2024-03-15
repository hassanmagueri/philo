#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "error\n", 6);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	while (1)
// 	{
// 		size_t s = get_current_time();
// 		printf("time => %zu\n", s);
// 		usleep(100);
// 	}
	
// 	return (0);
// }
