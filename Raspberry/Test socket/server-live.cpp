#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>	   //write
#include <iostream>

int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;
	char recv_message[255];
	bool accepted = false;
	int n = 0;

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
		printf("Could not create socket");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while (!accepted && (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
	{
		accepted = true;
		puts("Connection accepted");

		//Reply to the client
		message = "Hello Client , I have received your connection. But I have to go now, bye\n";
		write(new_socket, message, strlen(message));
	}
	if (new_socket < 0)
	{
		perror("accept failed");
		return 1;
	}

	puts("write done ....");

	bzero(recv_message, 256);
	puts("1");
	while (true)
	{
		while ((n = recv(new_socket, recv_message, 255, 0)) < 1)
		{
		}
		if (n <= -1)
			puts("error");
		else
		{
			puts(recv_message);
		}
	}

	return 0;
}
