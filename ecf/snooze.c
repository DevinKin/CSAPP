#include <csapp.h>
unsigned int snooze(unsigned int secs)
{
    unsigned int rest_sec =  Sleep(secs);
    printf("Slept for %d of %d secs.", (secs-rest_sec), secs);
    return rest_sec;
}

void sigint_handler(int sig)    /* SIGINT handler */
{
    printf("Caught SIGINT!\n");
    return;
}

int main(int argc, char *argv[])
{
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");
    unsigned int secs = atoi(argv[1]);
    snooze(secs);
    return 0;
}