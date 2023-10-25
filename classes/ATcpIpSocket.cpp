#include "../include/ATcpIpSocket.hpp"

/* docs: constructor only initialized _sockFd to 0 */
ATcpIpSocket::ATcpIpSocket(void) : _sockFd(-1) { }

ATcpIpSocket::~ATcpIpSocket(void)
{
	this->sockClose();
	return ;
}

/* !throws! docs: socket() with protocol, SOCK_STREAM, 0 -
* setsockopt() with SOL_SOCKET, SO_REUSEADDR, 1 - 
* bind() with protocol, ntohs(port), ntohs(ipAddress)
*/
void	ATcpIpSocket::initSocket(IpSockProtocols protocol, unsigned int port, unsigned int ipAddress)
{
	struct sockaddr_in	socketConf = {};
	int					val = 1;

	this->_sockFd = socket(protocol, SOCK_STREAM, 0);
	if (this->_sockFd < 0)
		throw new SocketFailedExcpetion("Failed to get socket\n");

	if (setsockopt(this->_sockFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) != 0)
		throw new SocketFailedExcpetion("Failed to setup socket\n");
	socketConf.sin_family = protocol;
	socketConf.sin_port = ntohs(port);
	socketConf.sin_addr.s_addr = ntohs(ipAddress);

	if (bind(this->_sockFd, (const sockaddr *)&socketConf, sizeof(socketConf)))
		throw new SocketFailedExcpetion("Failed to bind socket\n");
	return ;
}

/*
 * !throws! docs: Use listen() on the class _sockFd
 * with default to maxConnections is unistd SOMAXCONN 
 */
int	ATcpIpSocket::sockListen(int maxConnections)
{
	if (this->_sockFd < 0 || listen(this->_sockFd, maxConnections) != 0)
		throw new SocketFailedExcpetion("Failed to listen on socket\n");
	return (0);
}

/* !throws! docs: use accept() to fetch an fd for the next connection */
int	ATcpIpSocket::sockAccept(void)
{
	int					retFd;
	struct sockaddr_in	conf = { };
	socklen_t			confLen = sizeof(conf);

	retFd = accept(this->_sockFd,(struct sockaddr *)&conf, &confLen); 
	return (retFd);
}

/* docs: close() the internal socketfd, it is safe to call multiple times */
void	ATcpIpSocket::sockClose(void)
{
	if (this->_sockFd > 0)
		close(this->_sockFd);
	this->_sockFd = -1;
	return ;
}

/* docs: test if the fd is a socket */
bool	ATcpIpSocket::isSocketFd(int fd)
{
	struct stat statbuff;
	char		ret;

	ret = fstat(fd, &statbuff);
	if (ret < 0 || S_ISSOCK(statbuff.st_mode))
		return (false);
	return (true);
}

/* exceptions */

ATcpIpSocket::SocketFailedExcpetion::SocketFailedExcpetion(std::string message)
	: std::runtime_error(message) { } 
