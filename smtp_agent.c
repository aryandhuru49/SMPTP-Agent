#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/sans.h" 

int smtp_agent(const char* host, int port) {
    int socket_id;
    int rec_pkt;
    char buffer_size[1024];
    char email[256];
    char file_path[256];
    FILE *email_file;

    printf("Enter your email address: ");
    scanf("%255s", email); 
    
    printf("Enter the path to the email file: ");
    scanf("%255s", file_path);  

    socket_id = sans_connect(host, port, IPPROTO_TCP);
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
 

    snprintf(buffer_size, sizeof(buffer_size), "HELO %s\r\n",email);
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }


    snprintf(buffer_size, sizeof(buffer_size), "MAIL FROM: <%s>\r\n", email);
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }

    snprintf(buffer_size, sizeof(buffer_size), "RCPT TO: <%s>\r\n", email);
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }

    snprintf(buffer_size, sizeof(buffer_size), "DATA\r\n");
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }
   

    email_file = fopen(file_path, "r");
    
    
    while (fgets(buffer_size, sizeof(buffer_size), email_file)) {
        sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));

    }

    fclose(email_file);

    snprintf(buffer_size, sizeof(buffer_size), "\r\n.\r\n");
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));

    //printf("buffer_size: %s\n", buffer_size);
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }

    snprintf(buffer_size, sizeof(buffer_size), "QUIT\r\n");
    sans_send_pkt(socket_id, buffer_size, strlen(buffer_size));
    rec_pkt=sans_recv_pkt(socket_id, buffer_size, sizeof(buffer_size));
    
    if (rec_pkt > 0) {
        buffer_size[rec_pkt] = '\0';
        printf("%s", buffer_size);
    }

    sans_disconnect(socket_id);

    return 0;
}