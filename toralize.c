#include "toralize.h"

Req *request(struct sockaddr_in *sock2) {
    Req *req = malloc(reqsize);
    if (!req) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    req->vn = 4;  // SOCKS4 Version
    req->cd = 1;  // Connect Command
    req->dstport = sock2->sin_port;              // Target Port
    req->dstip = sock2->sin_addr.s_addr;         // Target IP
    memset(req->userid, 0, sizeof(req->userid)); // Clear UserID
    strncpy(req->userid, USERNAME, 8);           // SOCKS4 UserID

    return req;
}

int connect(int s2, const struct sockaddr *sock2, socklen_t addrlen) {
    int s;
    struct sockaddr_in sock;
    Req *req;
    Res res;
    char buf[ressize];
    int (*real_connect) (int, const struct sockaddr *, socklen_t);

    // Load the real connect() function
    real_connect = dlsym(RTLD_NEXT, "connect");

    // Create a socket for the proxy
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        return -1;
    }

    // Set up the proxy address (Tor SOCKS4 proxy)
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    // Connect to the proxy
    if (real_connect(s, (struct sockaddr *)&sock, sizeof(sock)) < 0) {
        perror("connect to proxy");
        close(s);
        return -1;
    }
    printf("[+] Connected to Tor SOCKS4 Proxy\n");

    // Send SOCKS4 request
    req = request((struct sockaddr_in *)sock2);
    if (write(s, req, reqsize) < 0) {
        perror("write to proxy");
        free(req);
        close(s);
        return -1;
    }
    free(req);

    // Read SOCKS4 response
    if (read(s, &res, ressize) < ressize) {
        perror("read from proxy");
        close(s);
        return -1;
    }

    // Check SOCKS4 response code (CD = 90 means success)
    if (res.cd != 90) {
        fprintf(stderr, "[-] SOCKS4 proxy error: %d\n", res.cd);
        close(s);
        return -1;
    }

    printf("[+] Connection established through Tor!\n");

    // Redirect communication to the target socket
    dup2(s, s2);
    return 0;
}