
<h1 style="border-bottom:none;">CIS 452 Operating Systems</h1>

## Project One: “One Bad Apple”

For this project, you will design a circular communication system where `k` processes will form
a ring where each node is only connected to its direct neighbor. For example, node 1 will
have a one-way write connection to node 2 which has a one-way write connection to node 3
etc. Node `k` will have a write connection to node 0. Node 0 will also have a read connection
from node `k` which will have a read connection from node `k-1`, etc.

Node 0 will prompt the user for a destination node and a message. The nodes will then pass 
the message around the ring to the destination.  A node can only send a message in response
to receiving a message. Thus, the messages are used to synchronize the system --- kind of 
like passing an apple in a group discussion to prevent everybody from talking at once.


When a node receives the apple (i.e., a message), it should determine if it is the 
intended recipient of the message. If so, it processes the message and sets the header 
to `<empty>`. If not, the 
node should send it on to the next node. Display verbose diagnostic messages
so a viewer can follow what the system is doing (e.g., who is
sending/receiving data, where the data is heading to, when a process is created/closed,
etc.).

When the apple (with an `<empty>` header) returns to node 0, node 0 prompts the user for
the next destination and message.


When the user presses Control-C, the original process should use signals to gracefully
shut down the simulation. 

You must use the process management and IPC system calls that
were covered in class for the implementation (`fork`, `signal`, `pipe`, etc.).
The parent process should request from the user the value for `k` and spawn that many
processes (the parent is node 0 and included in the ‘ring’). After the processes have
completed spawning, the parent process should prompt the user for a string message and
what node they would like to send it to.

Use descriptive variable names using the snake_case convention. Code should
be self-documenting where possible with only essential documentation within the code.

Additional Notes:
1. The system should be able to handle messages of more than one word
2. Do not use the `sleep` system call or any busy-waiting loops.

In addition to your code, please also submit:

1. A design document clearly describing your project as well as the implementation
2. A screenshot of the execution which clearly shows where the apple is and what nodes
are sending/receiving etc. At least two messages must be sent to different nodes from
the parent (send one message, after it is received and the apple returns to the parent,
send a second message). The screenshots should be from a terminal where the output is
easy to read (e.g., not a screenshot of visual studio code executing the code).

Project designed by Prof. Bobeldyk# cis452-project-one-bad-apple
