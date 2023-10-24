#include "../include/TcpIpSocket.hpp"

TcpIpSocket::TcpIpSocket(IpSockProtocols protocol, unsigned int port, unsigned int ipAddress)
{
	struct sockaddr_in	socketConf = {};
	int					val = 1;

	this->_sockFd = socket(protocol, SOCK_STREAM, 0);
	// guard clause for socket initialization

	setsockopt(this->_sockFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	socketConf.sin_family = protocol;
	socketConf.sin_port = ntohs(port);
	socketConf.sin_addr.s_addr = ntohs(ipAddress);

	(void)bind(this->_sockFd, (const sockaddr *)&socketConf, sizeof(socketConf));
	// guard clause here too
	return ;
}

TcpIpSocket::~TcpIpSocket(void)
{
	if (this->_sockFd >= 0)
		close(this->_sockFd);
}

/*
 * Use listen() on the class _sockFd
 * with default SOMAXCONN to max connections
 */
int	TcpIpSocket::sockListen(int maxConnections)
{
	listen(this->_sockFd, maxConnections);
	return (0);
}

/*
 * use accept() to fetch an fd for the next connection
 */
int	TcpIpSocket::sockAccept(void)
{
	int					retFd;
	struct sockaddr_in	conf = { };
	socklen_t			confLen = sizeof(conf);

	retFd = accept(this->_sockFd,(struct sockaddr *)&conf, &confLen); 
	return (retFd);
}
