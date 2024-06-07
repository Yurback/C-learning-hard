#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>
#include <lcthw/ringbuffer.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// short sock_create()
// {
//     printf("Start creating socket...");
//     short sock = 0;
//     sock = socket(AF_INET, SOCK_STREAM, 0);
//     return sock;
// }
// int bindCreateSocket(int sock)
// {
//     int port = 7899;
//     struct sockaddr_in remote = {0};
//     // address family
//     remote.sin_family = AF_INET;
//     remote.sin_addr.s_addr = htonl(INADDR_ANY);
//     remote.sin_port = htons(port);
//     int rc = bind(sock, (struct sockaddr *)&remote, sizeof(remote));
//     check(rc == 0, "Bind doesn't work");

//     return sock;
// error:
//     return -1;
// }

// int main(void)
// {
//     printf("hello");
//     int client_sock;

//     RingBuffer *buf = NULL;
//     buf = RingBuffer_create(1024 * 4);

//     struct sockaddr_in client;
//     int clientLen = sizeof(struct sockaddr_in);

//     // Create socket
//     int socket = sock_create();
//     // Bind
//     bindCreateSocket(socket);
//     // Listen
//     int rc = listen(socket, 10);
//     check(rc == 0, "Listen doesn't work");

//     while (1)
//     {
//         printf("Waiting for upcomming connection");
//         client_sock = accept(socket, (struct sockaddr *)&client, (socklen_t *)&clientLen);
//         // while (1)
//         // {
//         //     int rc = recv(client_sock, RingBuffer_starts_at(buf), RingBuffer_available_space(buf), 0);
//         //     RingBuffer_commit_write(buf, rc);
//         //     bstring mes = RingBuffer_get_all(buf);
//         //     if (buf->end == buf->start)
//         //     {
//         //         buf->start = buf->end = 0;
//         //     }
//         //     printf("The client say: %s", bdata(mes));

//         //     // prepare sended block
//         //     mes = bgets((bNgetc)fgetc, stdin, '\n');
//         //     check_debug(mes != NULL, "stdin closed");
//         //     rc = send(client_sock, bdata(mes), blength(mes), 0);
//         //     check(rc >= 0, "Fail to send message to the client");
//         //     if (bstrcmp(mes, bfromcstr("By")))
//         //     {
//         //         close(client_sock);
//         //         break;
//         //     }
//         // }
//     }
//     return 0;
// error:
//     return -1;
// }

short socketCreate(void)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}

int bindCreateSocket(int hSocket)
{
    int iRetval = -1;
    int clientPort = 12345;

    struct sockaddr_in remote = {0};

    /*Internet address family*/
    remote.sin_family = AF_INET;

    // Any incoming interface
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(clientPort); // Local port

    iRetval = bind(hSocket, (struct sockaddr *)&remote, sizeof(remote));
    return iRetval;
}

int main(void)
{
    int socket_desc = 0,
        sock = 0, clientLen = 0, n = 0;
    struct sockaddr_in client;
    // char client_message[4096] = {0};
    // char message[4096] = {0};

    RingBuffer *buf = NULL;
    buf = RingBuffer_create(1024 * 4);

    // Create socker
    socket_desc = socketCreate();
    if (socket_desc == -1)
    {
        printf("Could not create socket");
        return 1;
    }

    printf("Socket created\n");

    // Bind
    if (bindCreateSocket(socket_desc) < 0)
    {
        // print the error message
        perror("bind failed.");
        return 1;
    }

    printf("bind done\n");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    while (1)
    {
        printf("Waiting for incoming connections...\n");
        clientLen = sizeof(struct sockaddr_in);

        // accept connection from an incoming client
        sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&clientLen);

        if (sock < 0)
        {
            perror("accept failed");
            return 1;
        }

        printf("Connection accepted\n");
        // memset(client_message, '\0', sizeof(client_message));

        while (n = recv(sock, RingBuffer_starts_at(buf), RingBuffer_available_space(buf), 0) > 0 && strstr(buf->buffer, "\r\n\r\n") == 0)
        {
            // for (int i = 0; i < 10; i++)
            // {
            //     fprintf(stdout, "%d\n", (unsigned char)buf->buffer[i]);
            // }
            fprintf(stdout, "%d : %d\n", n, strlen(buf->buffer));
            fprintf(stdout, "%s", RingBuffer_starts_at(buf));
            RingBuffer_commit_write(buf, strlen(buf->buffer) - (buf->start));
            RingBuffer_commit_read(buf, strlen(buf->buffer) - (buf->start));
            fprintf(stdout, "%s", buf->buffer);
            // if (client_message[n - 1] == '\n')
            // {
            //     break;
            // }
            // memset(client_message, 0, 4096);
        }
        if (n < 0)
            printf("ERROR occured");

        RingBuffer_commit_read(buf, RingBuffer_available_data(buf));
        RingBuffer_write(buf, "HTTP/1.0 200 OK\r\n\r\nHello", strlen("HTTP/1.0 200 OK\r\n\r\nHello"));
        // now send a response.
        // snprintf((char *)message, sizeof(message), "HTTP/1.0 200 OK\r\n\r\nHello");

        write(sock, RingBuffer_starts_at(buf), RingBuffer_available_data(buf));
        memset(buf->buffer, 0, 4096);
        buf->start = 0;
        buf->end = 0;
        close(sock);
    }
}