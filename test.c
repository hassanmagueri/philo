#include <libc.h>
#include <time.h>

void f()
{
    int n;
    printf(" n = %d\n",n);
    n = 10;
}

typedef struct timeval t_timeval;

size_t get_current_time(void)
{
    t_timeval time;

    if (gettimeofday(&time, NULL))
        return (0);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int argc, char const *argv[])
{
    // struct timeval  current_time;
    // gettimeofday(&current_time, NULL);
    // printf("seconds : %ld\n", current_time.tv_sec);
    // printf("micro seconds : %ld\n", (long)current_time.tv_usec);
    // printf("hour : %ld\n", (current_time.tv_sec / (60 * 60)) % 12 );
    // printf("min : %ld\n", (current_time.tv_sec / (60)) % 60 );
    // printf("min : %ld\n", current_time.tv_sec / (60 * 60 * 24 * 365));
    // get_current_time();
    int i = 0;
    while (-1)
    {
        printf("%d\n", i);
        usleep(1 * 1000);
        i += 100;
    }
    
    return 0;
}
//1709981396000000 + 515103