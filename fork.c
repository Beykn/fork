#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void create_process_tree(int level, int max_level){
    if( level > max_level){
        return;
    }
    
    pid_t left_child, right_child;
    left_child = fork();
    if(left_child == 0){
        printf("Left child(Level : %d)\nPID: %d,\nParent PID: %d\n",level,getpid(),getppid());
        create_process_tree(level + 1, max_level);
        exit(0);
    }else if(left_child > 0){
        right_child = fork();
        if(right_child == 0){
            printf("Right child(Level : %d)\nPID: %d,\nParent PID: %d\n",level,getpid(),getppid());
            create_process_tree(level + 1, max_level);
            exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
}

int main(){
    int max_level = 3;
    int count ;
    printf("Root Node, PID: %d\n\n",getpid());
    create_process_tree(1,max_level);
    return 0;
}