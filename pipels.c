#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define READ_END 0
#define WRITE_END 1

int main (){
    char write_msg[BUFFER_SIZE] = "Greetings!";
    char read_msg[BUFFER_SIZE];
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1){
        printf("Pipe Failed\n");
    }

    pid = fork(); // Create a child process

    if (pid != 0){ //This is the parent process
        //The parent will not read from the pipe, so closing this pipe
        close(fd[WRITE_END]);

        while(read(fd[READ_END], read_msg, BUFFER_SIZE) != 0){
            //Program stays in this infinite loop until the child proc finishes
        }

        printf("The redirected output from the child process is: %s\n", read_msg);
        close(fd[READ_END]);
    }
    else{ //This is the child process
        close(fd[READ_END]);

        dup2(fd[WRITE_END], 1);
        dup2(fd[WRITE_END], 2);

        char *argv[] = {"ls", "-al", NULL};
        execvp(argv[0], argv);

        close(fd[WRITE_END]);
    }
    return 0;
}