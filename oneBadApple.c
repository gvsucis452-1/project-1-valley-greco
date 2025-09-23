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
    int message_size = 300;
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
    char message_input[message_size];
    for (node_index=1;node_index<k;node_index++){
        if( (pid = fork()) < 0){
            perror("Fork Failure");
            exit(1);
        }else if(pid ==0){
            // Child should immediatly break out of the loop to prevent forking
            break;
        }
    }

    node_index = node_index % k;
    printf("This is node %d\n", node_index);
    int next_node = (node_index +1) %k;

    //Create a wait for all the processes to finish creating (not sure if this is needed)


    char temp_string[] = "Hellow there"; // Temporary string (replace with user input later)
    
    if(pid != 0){ // Also temporary (move inside of loop)
        close(pipes[next_node][0]);
        write(pipes[next_node][1], &temp_string, sizeof(temp_string));   
    }
    while (1){
        
        // If statement for the parent function to promt the user
        
        //Use read to wait for a message on pipes[node_index][0]
        close(pipes[node_index][1]); //Close the writing pipe
        read(pipes[node_index][0], &message_input, sizeof(message_input));
        printf("Received by node %d, message is: %s\n", node_index,message_input);
        
        // Add code to determine if the message is intended for this node

        //Write the message to the next pipe
        printf("Sending message to node %d\n", next_node);
        close(pipes[next_node][0]);
        write(pipes[next_node][1], &message_input, sizeof(message_input));
    }

    return 0;
}
