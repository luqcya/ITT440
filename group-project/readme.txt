Case 1: If c-client container not running
- c-client container will be on loop restart state with an error of "Error connecting to the server: Network is unreachable"
    - this is due to c-client is unable to resolve the hostname for the c-server
- Inspect the c-server IP: docker inspect c-server | grep IP
- Modify the client.c <const char *serverHostname = "c-server";> to <const char *serverHostname = "<IP of c-server>";>
    - example: const char *serverHostname = "172.20.0.3";
- Create debug container: Uncomment the section for "DEBUG CONTAINER FOR C CLIENT"
- copy the client.c in c-client/client.c to the container "debug-ubuntu"
    - docker cp c-client/client.c debug-ubuntu:/root
- compile the C 
    - gcc -o /root/client /root/client.c
- run the code
    - root/client

