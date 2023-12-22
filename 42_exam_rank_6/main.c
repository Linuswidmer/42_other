#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <strings.h>


#define IP_ADDRESS 2130706433 // 127.0.0.1
#define MAX_CLIENTS 1024

typedef struct s_client {
	int		fd;
	int		id;
} t_client;

void	ft_error(char *str)
{
	write(2, str, strlen(str));
}

int accept_new_connection(int server_socket)
{
    int                 addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in  client_addr;
    int                 client_socket;


    client_socket = accept(server_socket, 
            (struct sockaddr *)&client_addr, 
            (socklen_t *)&addr_size);

	// make client socket non-blocking
	if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1) 
		return (-1);

    return (client_socket);
}

int	setup_server(int port)
{
	struct sockaddr_in	server_addr;
	int					server_socket;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1)
		return (-1);

	// make port reusable if it had been closed recently
	int on = 1;
	if ( setsockopt(server_socket, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT,
				&on, sizeof(int)) < 0 )

	// make server socket non-blocking
	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
		return (-1);

	bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(IP_ADDRESS);
    server_addr.sin_port = htons(port);

	if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        return (-1);
    
	if(listen(server_socket, 10) < 0)
        return (-1);

    return (server_socket);
}

void	init_clients(t_client *clients)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		clients[i].fd = -1;
		clients[i].id = -1;
	}
}

void  send_to_all(t_client *clients, int id_from, char *msg) {
	for (int i = 0; i < MAX_CLIENTS; i++) 
	{
		if (clients[i].id != -1 && clients[i].id != id_from)
		send(clients[i].fd, msg, strlen(msg), 0);
	}
}

int get_client_id(t_client *clients, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i].fd == fd)
			return (clients[i].id);
	}
	return (-1);
}

void	add_client(t_client *clients, int id, int fd)
{
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i].id == -1)
		{
			clients[i].id = id;
			clients[i].fd = fd;
			return ;
		}
	}
}

void	remove_client(t_client *clients, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i].fd == fd)
		{
			clients[i].id = -1;
			clients[i].fd = -1;
			return ;
		}
	}
}


int main(int argc, char **argv)
{
	int			server_socket;
	int			client_socket;
	fd_set		read_master_set, read_tmp_set;
	t_client	clients[MAX_CLIENTS];
	int			nb_clients = 0;
	char		msg[1000000];

	
	if (argc != 2)
		return (ft_error("Wrong number of arguments\n"), 1);

	init_clients(clients);
	server_socket = setup_server(atoi(argv[1]));
	if (server_socket== -1)
		return (ft_error("Fatal error\n"), 1);

	FD_ZERO(&read_master_set); // empty the set
	FD_SET(server_socket, &read_master_set); // add server_socket to the set

	while (42)
	{
		read_tmp_set = read_master_set;

		if (select(__FD_SETSIZE, &read_tmp_set, NULL, NULL, NULL) < 0)
            return (ft_error("Fatal error\n"), 1);
	
		for (int i = 0; i < __FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &read_tmp_set))
            {
                // 1. read on server socket -> new connection that we want to accept
                if (i == server_socket)
                {
                    client_socket = accept_new_connection(server_socket);
					if (client_socket == -1)
						return (ft_error("Fatal error\n"), 1);
					
					add_client(clients, nb_clients, client_socket);

					sprintf(msg, "server: client %d just arrived\n", nb_clients);
					send_to_all(clients, nb_clients, msg);
					
					nb_clients++;
					
                    FD_SET(client_socket, &read_master_set);
                }
                else // 2. read on client socket -> data from an existing connection
                {
                    char buffer[500000];
					int bytes_received = 1;
					
					bzero(buffer, sizeof(buffer));
					bzero(msg, sizeof(msg));
					while (bytes_received == 1)
					{
						bytes_received = recv(i, buffer + strlen(buffer), 1, 0);
						if (buffer[strlen(buffer) - 1] == '\n') // 2.1 message received
						{
							sprintf(msg, "client %d: %s", get_client_id(clients, i), buffer);
							send_to_all(clients,  get_client_id(clients, i), msg);
							break ;
						}
					}
					if (bytes_received == 0) // 2.2 client disconnected
					{
						sprintf(msg, "server: client %d just left\n", get_client_id(clients, i));
						send_to_all(clients,  get_client_id(clients, i), msg);
						remove_client(clients, i);
						close(i);
						FD_CLR(i, &read_master_set);
					} 
                }
            }
		}
	}
	return (0);
}
