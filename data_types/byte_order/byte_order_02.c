/*
Conversion Between Byte Orders:
To ensure that data is correctly interpreted across different systems, you can use standard functions like:

htonl() / ntohl(): Convert 32-bit data from host byte order to network byte order and vice versa.
htons() / ntohs(): Convert 16-bit data from host byte order to network byte order and vice versa.
*/

#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned int host_value = 0x12345678;
    unsigned int network_value = htonl(host_value);
    
    printf("Host value: 0x%x\n", host_value);
    printf("Network value: 0x%x\n", network_value);
    
    return 0;
}
