# Design Document

## Overview

This project has the user input a specified number of processes `k`, and the program creates `k-1` processes (with the parent as process 0) and forms a ring with pipes connecting each of the processes to the next. The parent process prompts the user for a message and destination, and the message is sent around the ring until the destination node receives it and wipes the message, then sends the empty string back around to the parent which then prompts for another message and destination node. 

## Initialization

At the beginning of the program, we prompt the user for how many processes should be in the ring (`k`), and we validate their input to ensure an integer value. Then proceed with the following steps:

1. Create an array of `k` pipes
2. Setup variables `node_index`, `pid`, and our structure to hold the message and recipient `struct apple apl`
3. Use `fork()` to create `k-1` processes from the parent process
4. Each child then writes 1 bit to the `ready_pipe` to signal to the parent that they are done building
5. Each process then prints it's number, so the user can see the processes are successfully created
6. Within each process, close all unused pipe ends, each process only needs one read end (from the previous process) and one write end (to the next process)
7. In the parent process, read `k-1` bits from the `ready_pipe` to ensure all pipes are done building and a signal to handle the `^C` exit signal
8. Prompt the user for the first message and recipient

## Enter Loop

After all of the processes and pipes have been initialized and all the unused pipe ends are closed. We prompt the user for the first message and send that into the first pipe from the parent to the next process in the ring. Once the first message is sent, the loop starts. Within the loop, each process:

1. Blocks on reading the pipe from the previous process, continues once something is sent through to their read end
2. Reads from the pipe, and pulls the `apl` struct
3. Checks to see if the message is empty:
	- If so, print "node `i` sees empty message" and move to step 5
	- If not, continue to step 4
4. Check the `recipient` value in `apl`:
	- If `recipient` is the same as `node_index`, print the message from the recipient node and wipe the message string in `apl`
	- If not, continue to step 5
5. Forward `apl` through the process' write end, to the next process
6. Once the parent receives the `apl` back from it's read end, prompt the user again for a new message and recipient
7. Update `apl` with the new values, and write it through the first pipe to the next node and restart the loop from 1

Because all nodes block on read(), the ring stays synchronized automatically. Only the node holding the apple (`apl`) is active at any given time.

## Shutdown

When the program receives the shutdown signal `^C` from the user, handle the signal and begin graceful shutdown.

1. All children processes are terminated
2. Ensure all child processes are fully terminated and removed from the process table
3. Send confirmation message that all children are terminated
4. The parent is then terminated and the program is shutdown
