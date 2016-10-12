#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int sock;
	int yes = 1;

	char buf[1024];
	char inbuf[1024];

	if ((sock0 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		perror("bind");
		return 1;
	}
	if (listen(sock0, 5) != 0) {
		perror("listen");
		return 1;
	}

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf),
	    "HTTP/1.0 200 OK\r\n"
	    "Content-Length: 20\r\n"
	    "Content-Type: text/html\r\n"
	    "HELLO\r\n");

	listen(sock0, 5);
	while (1) {
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0) {
			perror("accept");
			break;
		}
		memset(inbuf, 0, sizeof(inbuf));
		recv(sock, inbuf, sizeof(inbuf), 0);
		printf("%s", inbuf);
		send(sock, buf, (int)strlen(buf), 0);
		close(sock);
	}

	return 0;
}
