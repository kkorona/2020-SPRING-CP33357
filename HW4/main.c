#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <utmpx.h>

int main(void) {

    char LOGDIR_PATH[] = "/tmp/201624476";
    char LOG_PATH[] = "/tmp/201624476/cse201624476";
    FILE *fStream;

    struct utmpx *utx;

    if(access(LOGDIR_PATH, R_OK | W_OK) != 0) {
        if(mkdir(LOGDIR_PATH, 0777) == -1 && errno != EEXIST) {
            fprintf(stderr, "directory create error: %s\n", strerror(errno));
            return -1;
        }
    }

    fStream = fopen(LOG_PATH, "a+");
    fclose(fStream); 
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
    /* Daemon-specific initialization goes here */

    /* An infinite loop */
    int cnt = 1;
    while (1) {
        char log_buff[40];
        /* Do some task here ... */
        fStream = fopen(LOG_PATH, "a");
        while((utx = getutxent()) != NULL) {
            if(utx->ut_type != USER_PROCESS) continue;
            sprintf(log_buff, "%10s %s\n", utx->ut_user, ctime(&utx->ut_tv.tv_sec));
            fwrite(log_buff, strlen(log_buff), 1, fStream);
        }
        fclose(fStream);
        sleep(2); /* wait 2 seconds */
        cnt++;
        if(cnt == 15) {
            /* display logwatchdog every 30 secs */
            printf("\n---------------\n");
            printf("* logwatchdog *\n");
            printf("---------------\n");
                
            fStream = fopen(LOG_PATH, "r");
            fseek(fStream, 0, SEEK_END);
            int lSize = ftell(fStream);
            rewind(fStream);

            char* buffer = (char*)malloc(sizeof(char) * lSize);
            fread(buffer, 1, lSize, fStream);
            printf("%s", buffer);
            fclose(fStream);
            cnt = 0;
         }
    }
    fclose(fStream);
    exit(EXIT_SUCCESS);
}


