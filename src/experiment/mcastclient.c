// https://www.tenouk.com/Module41c.html
/* Receiver/client multicast Datagram example. */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
int datalen;
char databuf[1024];

int main(int argc, char *argv[])
{
    /* Create a datagram socket on which to receive. */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("Opening datagram socket error");
        exit(1);
    }
    else
    {
        printf("Opening datagram socket....OK.\n");
    }

    /* Enable SO_REUSEADDR to allow multiple instances of this */
    /* application to receive copies of the multicast datagrams. */
    {
        int reuse = 1;
        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
        {
            perror("Setting SO_REUSEADDR error");
            close(sd);
            exit(1);
        }
        else
        {
            printf("Setting SO_REUSEADDR...OK.\n");
        }
    }

    /* Bind to the proper port number with the IP address specified as INADDR_ANY. */
    // Why Bind?
    memset((char *)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(4321);       // receive port
    localSock.sin_addr.s_addr = INADDR_ANY; // any address's package is ok, like filter rule
    if (bind(sd, (struct sockaddr *)&localSock, sizeof(localSock)))
    {
        perror("Binding datagram socket error");
        close(sd);
        exit(1);
    }
    else
    {
        printf("Binding datagram socket...OK.\n");
    }

    /* Join the multicast group 226.1.1.1 on the local 127.0.0.1 */
    /* interface. Note that this IP_ADD_MEMBERSHIP option must be */
    /* called for each local interface over which the multicast */
    /* datagrams are to be received. */
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
    group.imr_interface.s_addr = inet_addr("127.0.0.1"); // INADDR_ANY: an appropriate interface is chosen by the system, same with sender
    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
    {
        perror("Adding multicast group error");
        close(sd);
        exit(1);
    }
    else
    {
        printf("Adding multicast group...OK.\n");
    }

    /* Read from the socket. */
    datalen = sizeof(databuf);
    if (read(sd, databuf, datalen) < 0)
    {
        perror("Reading datagram message error");
        close(sd);
        exit(1);
    }
    else
    {
        printf("Reading datagram message...OK.\n");
        printf("The message from multicast server is: \"%s\"\n", databuf);
    }
    return 0;
}