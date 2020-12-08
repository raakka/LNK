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

int main() {
	int client_socket;
	struct sockaddr_in server_addr;

	if (client_socket = socket(PF_INET, SOCK_STREAM, 0) < 0) {
		perror("Cannot Create Socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (connect(client_socket,
		(struct sockaddr*) &server_addr,
		sizeof(server_addr)) == -1) return 0;

	printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗");	
	printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗");
	printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║");
	printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║");
	printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝");
	printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝");
	printf("\n");
	printf("██╗     ███╗   ██╗██╗  ██╗");                                                          
	printf("██║     ████╗  ██║██║ ██╔╝");                                                          
	printf("██║     ██╔██╗ ██║█████╔╝");                                                           
	printf("██║     ██║╚██╗██║██╔═██╗");                                                           
	printf("███████╗██║ ╚████║██║  ██╗");                                                          
	printf("╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝");                                                          
	return 0;
}

