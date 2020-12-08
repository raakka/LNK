#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MSGSIZE 1024

void * recdataloop(void * sockID) {
	int client_socket = *((int *) sockID);

	while(1){
		char recdata[1024];
		int read = recv(client_socket, recdata, 1024, 0);
		//recdata[read] = '\0'; //<- Why adding null???
		printf("%s\n", recdata);
	}
}

int main() {
	char usr[64], pwd[64];
	int client_socket;
	struct sockaddr_in server_addr, this_addr;

	if ((client_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Cannot Create Socket!");
		exit(EXIT_FAILURE);
	}
	
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&this_addr, 0, sizeof(this_addr));

	// the person we are sending to	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// this client's address 
	this_addr.sin_family = AF_INET;
	this_addr.sin_port = htons(8888);
	this_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	

	// TODO(XVI) add a thing if this goes bad...
	// binding the client so we know it has a place
	bind(client_socket, (struct sockaddr *)&this_addr, sizeof(this_addr));

	// connect the client socket!
	if (connect(client_socket, (struct sockaddr*) &server_addr,	sizeof(server_addr)) == -1) {
		perror("Cannot Connect to Server!");	
		exit(EXIT_FAILURE);
	}

	printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗\n");	
	printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗\n");
	printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║\n");
	printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║\n");
	printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝\n");
	printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝\n");
	printf("\n");
	printf("██╗     ███╗   ██╗██╗  ██╗\n");                                                       
	printf("██║     ████╗  ██║██║ ██╔╝\n");                                                          
	printf("██║     ██╔██╗ ██║█████╔╝\n");                                                           
	printf("██║     ██║╚██╗██║██╔═██╗\n");                                                           
	printf("███████╗██║ ╚████║██║  ██╗\n");                                                          
	printf("╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝\n\n");                                                          
	sleep(1);
	printf("╔════════════════════╗\n");
	printf("║       LOGIN        ║\n");
	printf("╚════════════════════╝\n");
	printf("PTR USRNAME: ");
	scanf("%s", usr);
	printf("PTR ACC PWD: ");
	fflush(stdin);
	scanf("%s", pwd);	
	
	sleep(1);
	printf("SYSTEM LOGIN SUCCESSFUL\n");
	printf("STARTING THREADS\n\n");
	sleep(1);
	printf("MESSAGES ════════════════════════════════════════════════\n");

	//running our rec function in another thread so we can tx/rx
	pthread_t recthread;
	pthread_create(&recthread, NULL, recdataloop, (void *) &client_socket);

	while(1) {
		// TODO(XVI): make the buffer sizes dynamic having 1024 limit is dumb
		char msg[1024];
		fgets(msg, 1024, stdin);
		//scanf("%s", msg);	
		send(client_socket, (const char *)msg, 1024, 0);
	}

}

