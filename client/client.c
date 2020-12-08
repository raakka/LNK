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
	struct sockaddr_in server_addr;

	if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Cannot Create Socket!");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
	printf("PWD: ");
	fflush(stdin);
	scanf("%s", pwd);	

	//running our rec function in another thread so we can tx/rx
	pthread_t recthread;
	pthread_create(&recthread, NULL, recdataloop, (void *) &client_socket);

	while(1) {
		// TODO(XVI): make the buffer sizes dynamic having 1024 limit is dumb
		char msg[1024];
		scanf("%s: %s", usr, msg);	
		send(client_socket,msg,1024,0);
	}

}

