#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, ret_exec, status;
    pid = fork();

    switch (pid)
    {

    case -1:
        /* code for case -1 */
        printf("Error\n");
        exit(1);
    case 0:
        /* code for case 0 */
        ret_exec = execl("/bin/ps", "ps", "-A", NULL);
        if (ret_exec == -1)
        {
            printf("Error executing exec\n");
        }
        break;

    default:
        /* code for case default */
        pid = wait(&status);
        if (WIFEXITED(status))
        {
            printf("Parent process ID: %d\n", getpid());
            printf("Child process ID: %d\n", pid);
            printf("Child process terminated with status: %d\n", WEXITSTATUS(status));
        }
        break;
    }
}