#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 25
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
        close(fd[READ_END]);

        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        close(fd[WRITE_END]);
    }
    else{ //This is the child process
        close(fd[WRITE_END]);

        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child received the message: %s\n", read_msg);

        close(fd[READ_END]);
    }
    return 0;
}