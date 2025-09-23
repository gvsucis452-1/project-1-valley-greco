/**********************************************************
 *
 * oneBadApple.c
 * CIS 451 Project 1 (F25)
 *
 * !!! Name(s) !!!
 *************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    /* Do stuff */
    int k;
    printf("Enter how many processes I should be in the ring? ");
    if (scanf("%d", &k) != 1){
        printf("Invalid Input.\n");
        exit(1);
    }
    printf("Creating a ring with %d processes\n", k);
    
    //Create an array that holds all the pipes
    //Node i will read from index i and write to index (i+1)%k
    int pipes[k][2];
    for(int i=0;i<k;i++){
        if(pipe(pipes[i]) == -1){
            perror("Error while creating a pipe\n");
            exit(1);
        }
    }

    int node_index; //Keep track of the nodes index for the pipes array
    pid_t pid;
    for (node_index=1;node_index<k;node_index++){
        if( (pid = fork()) < 0){
            perror("Fork Failure");
            exit(1);
        }else if (pid == 0){
            //Use read to wait for a message on pipes[node_index][0]
            break;
        }else{

        }
    }
    node_index = node_index % k;

    printf("Node index %d\n", node_index);
    
    //Create a wait for all the processes to finish creating

    // Promt the user for a string and which node to send it too
    return 0;
}
