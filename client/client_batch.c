#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT "88888"
#define DEFAULT_ADDR "192.168.50.80"
#define DEFAULT_FOLDER "requests5.txt"


int main (int argc, char *argv[])
{
    FILE *fptr;
    int sockfd, len;
    char buf[BUFSIZ];
    struct sockaddr_in serv;
    int port;

    if ((sockfd = socket (PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }



    if ((fptr = fopen(DEFAULT_FOLDER, "r")) == NULL){
        printf("Error opening file");
        exit(1);
    }
    serv.sin_family = PF_INET;
    port = strtol(DEFAULT_PORT, NULL, 10);
    serv.sin_port = htons(port);
    inet_aton(DEFAULT_ADDR, &serv.sin_addr);



    if (connect (sockfd,(struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }


    while (EOF != fscanf(fptr, "%[^\n]\n", buf))
    {
        printf("==> ");
        printf("%s\n", buf);
        len = send (sockfd, buf, strlen(buf), 0);
        len = recv (sockfd, buf, 200, 0);
        buf[len] = '\0';
        printf("<== %s\n", buf);
    }

    
    close (sockfd);
    fclose(fptr);
    return 0;
}