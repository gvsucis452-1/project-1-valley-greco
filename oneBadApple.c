/**********************************************************
 *
 * oneBadApple.c
 * CIS 451 Project 1 (F25)
 *
 * !!! Name(s) !!!
 * Charlie Greco
 * Connor Valley
 *************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct apple {
    int recipient;
    char message[250];
};

int main(int argc, char *argv[]) {
    int message_size = 300;
    int k;
    printf("Enter how many processes should be in the ring? ");
    if (scanf("%d", &k) != 1){
        printf("Invalid Input.\n");
        exit(1);
    }
    getchar();
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
    
    struct apple apl;
    char message_input[message_size];
    int recipient;


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
    int next_node = (node_index +1) % k;

    for (int i = 0; i < k; i++) {
        if (i != node_index) {
            close(pipes[i][0]); // close all read ends except myself
        }
        if (i != next_node) {
            close(pipes[i][1]); // close all write ends besides the next node
        }
    }
    
    if (pid != 0) {
        sleep(1);   // parent waits for process creation

        // initial prompt for user input to start loop

        printf("Enter Message: ");
        fgets(message_input, sizeof(message_input), stdin);
        message_input[strcspn(message_input, "\n")] = '\0';

        printf("Enter Destination Node (0-%d): ", k-1);
        scanf("%d", &recipient);
        getchar();

        apl.recipient = recipient;
        strcpy(apl.message, message_input);

        write(pipes[next_node][1], &apl, sizeof(apl));
    }


    // main loop

    while(1) {

        read(pipes[node_index][0], &apl, sizeof(apl));
        
        if (strlen(apl.message) > 0) {
            if (apl.recipient == node_index) {
                printf("Node %d received message: %s\n", node_index, apl.message);

                apl.message[0] = '\0';
            } else {
                printf("Node %d forwarding message...\n", node_index);
            }

        } else {

            printf("Node %d sees empty message...\n", node_index);

            if (node_index == 0) {

                printf("Enter Message: ");
                fgets(message_input, sizeof(message_input), stdin);
                message_input[strcspn(message_input, "\n")] = '\0';

                printf("Enter Destination Node (0-%d): ", k-1);
                scanf("%d", &recipient);
                getchar();

                apl.recipient = recipient;
                strcpy(apl.message, message_input);
            }
        }



        write(pipes[next_node][1], &apl, sizeof(apl));

    }

    return 0;
}
