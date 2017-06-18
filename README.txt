/* Author: Nikhil Patil
   Email: pailnikhils19@gmail.com
   Date: 8 June 2017 
*/

Server 127.0.0.1
Port number 36000

Compile

>gcc server.c -o server -lpthread

>gcc client.c -o client

run 

>./server

>./client


CLI Commands on client

fibonacci argument1

random argument1 argument2

sort argument1, ....... (Max 9 arguments).


Instruction

Design a TCP socket based application in c

Server: 
Create TCP socket server which creates socket and starts listening on the TCP port given
Client can connect to this TCP server on given port.
Client send the command to server over the server.
Server spawn a new thread to process each request.
Server sends reslt back to client after processing request.
Server also saves the command and results on common file in to file system.
 
Client:
Client is CLI command
Client connects to given server using IP address and port number.
User can type help to see user commands.
User can type command and argument to send to server.
Server response will be printed on CLI.
User can type more and more commands.
A special command "show history" gets all past commands and results stored on server and print them on CLI client.
User command "exit" will exit client.
multiple clients can connect to server in parallel. 

Following commands should be implemented
	fibonacci 10  <-- this commands returns the 10th fibonacci number from the fibonacci sequence
	sort 1 5 7 10  <-- this command returns the input numbers in descending sorted order	
	random 5 17  <-- this command returns a random integer between 5 and 17 inclusive.
Programmer should test his code by running two clients simultaneously.


