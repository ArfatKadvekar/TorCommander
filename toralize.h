#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PROXY "127.0.0.1"
#define PROXYPORT 9050

struct proxy_request
{
    int8_t vn;
    int8_t cd;
    int16_t dstport;
    int32_t dstip;
    unsigned char userid[8];
};

typedef struct proxy_request Req;

struct proxy_response
{
    int8_t vn;
    int8_t cd;
    int16_t _;
    int32_t __;
};

typedef struct proxy_request Req;
