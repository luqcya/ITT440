#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
struct servent *serv;

if (argc < 4) {
puts("Incorrect parameters. Use:");
puts(" key gsbnm service-name protocol-name");
return EXIT_FAILURE;
}

/* getservbyname() - opens the etc.services file and returns the */
/* values for the requested service and protocol. */
char *a = "dontforgetmynameisshahadan";
char *b = argv[1];

if (strncmp(b,a,26) == 0){
serv = getservbyname(argv[2], argv[3]);
if (serv == NULL) {
printf("Service %s not found for protocol %s\n",
argv[2], argv[3]);
return EXIT_FAILURE;
}

/* Print it. */
printf("Name: %-15s Port: %5d Protocol: %-6s\n",
serv->s_name,ntohs(serv->s_port),serv->s_proto);
return EXIT_SUCCESS;
}
else{
printf("You forgot the key!\n");
}
}