#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    while (i < 3)
    {
        int pid = fork();
        if (pid == 0)
        {
            if (i != 2)
                sleep(10); // sleep one and ignore others
            printf("I am sleeping %d\n", getpid());
            exit(0);
        }
        i++;
    }
    
    i = 0;
    while (i < 3)
    {
        waitpid(-1, NULL, 0);
        kill(0, SIGINT);
        i++;
    }
    return 0;
}
