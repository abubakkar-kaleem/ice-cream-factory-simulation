#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid > 0)  // parent process
    {
        wait(NULL);  // wait for child execution
        long int s = syscall(335);  // 335 is the system call number 
        execlp("./script_main.sh", "./script_main.sh", (char *)0);
    }
    else  // child process
    {
        execlp("./script_title.sh", "./script_title.sh", (char *)0);
    }

    return 0;
}
