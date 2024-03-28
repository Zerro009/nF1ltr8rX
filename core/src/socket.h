#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>

#include <unistd.h>

int32_t _socket(int32_t domain, int32_t type, int32_t protocol);
int32_t _close(int32_t fd);
int32_t _bind(int32_t sockfd, const struct sockaddr *addr, socklen_t addrlen);
int32_t _listen(int32_t sockfd, int32_t backlog);
int32_t _connect(int32_t sockfd, const struct sockaddr *addr, socklen_t addrlen);
int32_t _accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen);
int32_t _recv(int32_t sockfd, void *buf, int32_t len, int32_t flags);
int32_t _send(int32_t sockfd, const void *buf, int32_t len, int32_t flags);

#endif
