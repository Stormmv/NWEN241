#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Send HELLO message to client
    const char *hello_msg = "HELLO\n";
    send(client_socket, hello_msg, strlen(hello_msg), 0);

    // Receive message from client
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0)
        error("Error receiving message from client");
    buffer[bytes_received] = '\0'; // Null-terminate the received message

    // Process client's message
    if (strcasecmp(buffer, "BYE\n") == 0)
    { // Note the "\n" to match client's newline
        // Close connection if client sends "BYE"
        close(client_socket);
    }
    else if (strncasecmp(buffer, "GET ", 4) == 0)
    {
        // Extract filename from GET request
        char *filename = buffer + 4;
        // Remove newline character if present
        char *newline = strchr(filename, '\n');
        if (newline != NULL)
            *newline = '\0';
        // Open file and send response
        FILE *file = fopen(filename, "r");
        if (file != NULL)
        {
            // Send 200 OK response
            const char *ok_response = "SERVER 200 OK\n\n";
            send(client_socket, ok_response, strlen(ok_response), 0);
            // Send contents of file
            while (fgets(buffer, BUFFER_SIZE, file) != NULL)
            {
                send(client_socket, buffer, strlen(buffer), 0);
            }
            // Send two newlines
            send(client_socket, "\n\n", 2, 0);
            fclose(file);
        }
        else
        {
            // Send 404 Not Found response
            const char *not_found_response = "SERVER 404 Not Found\n";
            send(client_socket, not_found_response, strlen(not_found_response), 0);
        }
        // Close connection
        close(client_socket);
    }
    else if (strncasecmp(buffer, "PUT ", 4) == 0)
    {
        // Extract filename from PUT request
        char *filename = buffer + 4;
        // Remove newline character if present
        char *newline = strchr(filename, '\n');
        if (newline != NULL)
            *newline = '\0';
        // Open file and send response
        FILE *file = fopen(filename, "w");
        if (file != NULL)
        {
            // Send 201 Created response
            const char *created_response = "SERVER 201 Created\n";
            send(client_socket, created_response, strlen(created_response), 0);
            // Write contents to file
            while (1)
            {
                bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
                if (bytes_received < 0)
                    error("Error receiving message from client");
                buffer[bytes_received] = '\0'; // Null-terminate the received message
                // Write to file
                if (strcmp(buffer, "\n") == 0)
                {
                    // Write two newlines to file
                    fprintf(file, "\n\n");
                    break;
                }
                fprintf(file, "%s", buffer);
            }
            fclose(file);
        }
        else
        {
            // Send 501 Put Error response
            const char *put_error_response = "SERVER 501 Put Error\n";
            send(client_socket, put_error_response, strlen(put_error_response), 0);
        }
        // Close connection
        close(client_socket);
    }
    else
    {
        // Send 502 command error response for invalid request
        const char *error_response = "SERVER 502 Command Error\n";
        send(client_socket, error_response, strlen(error_response), 0);
        // Close connection
        close(client_socket);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int port = atoi(argv[1]);
    if (port < 1024)
    {
        fprintf(stderr, "Port number must be 1024 or greater\n");
        return -1;
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        error("Error opening socket");

    // Initialize server address struct
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        error("Error on binding");

    // Listen for incoming connections
    listen(server_socket, 5);

    // Accept connections and handle clients
    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
            error("Error on accept");
        handle_client(client_socket);
    }

    // Close server socket
    close(server_socket);

    return 0;
}