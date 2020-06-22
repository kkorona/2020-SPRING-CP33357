#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <utmp.h>
#include <time.h>
#include <string>
#include <map>
using namespace std;

int main(void) {

    char LOGDIR_PATH[] = "/tmp/201624476";
    char LOG_PATH[] = "/tmp/201624476/cse201624476";
    FILE *fStream;

    struct utmp *utx;
    time_t the_time;
    struct tm *tm_ptr;
    char now_local_time[50];

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
    printf("starting daemon...\n");
    map <string, int> user_state;
    /* An infinite loop */
    int cnt = 15;
    while (1) {
        char log_buff[40];
        /* Do some task here ... */
        for(auto& c : user_state) {
            c.second = -1;
        }
        fStream = fopen(LOG_PATH, "a");
        setutent();
        while((utx = getutent()) != NULL) {
            if(utx->ut_type != USER_PROCESS) continue;
            the_time = utx->ut_time;
            tm_ptr = localtime(&the_time);
            sprintf(now_local_time, "%d/%02d/%02d %02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min);
            if(user_state[string(utx->ut_name)] == 0) {
                sprintf(log_buff, "%10s login : %s\n", utx->ut_name, now_local_time);
                fwrite(log_buff, strlen(log_buff), 1, fStream);
                user_state[string(utx->ut_name)] = 1;
            }
            else {
                user_state[string(utx->ut_name)] = 1;
            }
        }
        time(&the_time);
        tm_ptr = localtime(&the_time);
        sprintf(now_local_time, "%d/%02d/%02d %02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min);
        for(auto c : user_state) {
            if(c.second == -1) {
                char ch[100];
                strcpy(ch,(c.first).c_str());
                sprintf(log_buff, "%10s logout : %s\n", ch, now_local_time);
                fwrite(log_buff, strlen(log_buff), 1, fStream);
                user_state.erase(c.first);
            }
        }
        fclose(fStream);
        sleep(2); /* wait 2 seconds */
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
            free(buffer);
            cnt = 0;
         }
         else  {
             cnt++;
         }
    }
    fclose(fStream);
    exit(EXIT_SUCCESS);
}


