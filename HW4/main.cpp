#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(void) {

    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    printf("pid = [%d] \n", pid);
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
    *         we can exit the parent process. */
    if (pid > 0) { // Child can continue to run even after the parent has finished executing
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */        

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    //Because daemons generally dont interact directly with user so there is no need of keeping these open
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* An infinite loop */
    while (1) {
        /* Do some task here ... */
        syslog(LOG_INFO, "daemoon loop!!!");
        sleep(2); /* wait 2 seconds */
    }
    exit(EXIT_SUCCESS);
}


