#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sysexits.h>
#include <err.h>
#include <sys/types.h>
#define MAX_LEN 1024

int main()
{
    char temp_line[MAX_LEN + 1];
    FILE *fp = stdin;
    char std1[MAX_LEN + 1];
    char std2[MAX_LEN + 1];
    int pid_status = -1;

    printf("shell_jr: ");
    fflush(stdout);
    while (fgets(temp_line, sizeof(temp_line), fp))
    {
        sscanf(temp_line, " %s%s", std1, std2);
        if (strcmp(std1, "hastalavista") == 0 || strcmp(std1, "exit") == 0)
        {
            printf("See you\n");
            fflush(stdout);
            exit(0);
        }
        else if (strcmp(std1, "cd") == 0)
        {
            pid_status = chdir(std2);
            if (pid_status != 0)
            {
                printf("shell_jr: Cannot change to directory %s\n", std1);
            }
        }
        else
        {
            int status;
            char *argv_check[] = {NULL, NULL, NULL};
            pid_t pid;
            argv_check[0] = std1;
            argv_check[1] = std2;
            if ((pid = fork()) < 0)
            {
                err(EX_OSERR, "fork error");
            }
            if (pid)
            {
                /*    print("This is parent PID %d, This id child PID %d\n", getpid(),pid); */
                wait(NULL);
            }
            else
            {

                status = execvp(argv_check[0], argv_check);
                /* printf("executed");*/
                if (status == -1)
                {
                    printf("Failed to execute %s\n", std1);
                    exit(EX_OSERR);
                }
            }
        }
        printf("shell_jr: ");
        fflush(stdout);
    }
    return 0;
}