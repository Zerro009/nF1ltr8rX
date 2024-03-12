#include "tcp_server.h"

int32_t _socket(int32_t domain, int32_t type, int32_t protocol) {
	return socket(domain, type, protocol);
}

int32_t _close(int32_t fd) {
	return close(fd);
}

int32_t _bind(int32_t sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	return bind(sockfd, addr, addrlen);
}

int32_t _listen(int32_t sockfd, int32_t backlog) {
	return listen(sockfd, backlog);
}

int32_t _connect(int32_t sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	return connect(sockfd, addr, addrlen);
}

int32_t _accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	return accept(sockfd, addr, addrlen);
}

int32_t _recv(int32_t sockfd, void *buf, int32_t len, int32_t flags) {
	return recv(sockfd, buf, len, flags);
}

int32_t _send(int32_t sockfd, const void *buf, int32_t len, int32_t flags) {
	return send(sockfd, buf, len, flags);
}
