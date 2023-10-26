#include "../include/ATcpIpSocket.hpp"

/* docs: constructor only initialized _sockFd to 0 */
ATcpIpSocket::ATcpIpSocket(IpSockProtocols ipProtocol, unsigned int port, unsigned int ipAddress) :
	_sockFd(-1),
	_ipProtocol(ipProtocol),
	_port(port),
	_ipAddress(ipAddress) 
{ };

ATcpIpSocket::~ATcpIpSocket(void)
{
	this->closeSocket();
	return ;
}

/* !throws! docs: socket() with protocol, SOCK_STREAM, 0 -
* setsockopt() with SOL_SOCKET, SO_REUSEADDR, 1 - 
* bind() with protocol, ntohs(port), ntohs(ipAddress)
*/
void	ATcpIpSocket::initSocket(void)
{
	struct sockaddr_in	socketConf = {};
	int					val = 1;

	this->_sockFd = socket(this->_ipProtocol, SOCK_STREAM, 0);
	if (this->_sockFd < 0)
		throw new SocketFailedExcpetion("Failed to get socket\n");

	if (setsockopt(this->_sockFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) != 0)
		throw new SocketFailedExcpetion("Failed to setup socket\n");
	socketConf.sin_family = this->_ipProtocol;
	socketConf.sin_port = ntohs(this->_port);
	socketConf.sin_addr.s_addr = INADDR_ANY;
	// socketConf.sin_addr.s_addr = ntohl(this->_ipAddress);

	if (bind(this->_sockFd, (const sockaddr *)&socketConf, sizeof(socketConf)))
		throw new SocketFailedExcpetion("Failed to bind socket\n");
	return ;
}

/*
 * !throws! docs: Use listen() on the class _sockFd
 * with default to maxConnections is unistd SOMAXCONN 
 */
int	ATcpIpSocket::listenSocket(int maxConnections)
{
	if (this->_sockFd < 0 || listen(this->_sockFd, maxConnections) != 0)
		throw new SocketFailedExcpetion("Failed to listen on socket\n");
	return (0);
}

/* !throws! docs: use accept() to fetch an fd for the next connection */
int	ATcpIpSocket::acceptOnSocket(void)
{
	int					retFd;
	struct sockaddr_in	conf = { };
	socklen_t			confLen = sizeof(conf);

	retFd = accept(this->_sockFd,(struct sockaddr *)&conf, &confLen); 
	return (retFd);
}

/* docs: close() the internal socketfd, it is safe to call multiple times */
void	ATcpIpSocket::closeSocket(void)
{
	if (this->_sockFd >= 0)
		close(this->_sockFd);
	this->_sockFd = -1;
	return ;
}

void	ATcpIpSocket::connectSocket(void)
{
	return ;
}

/* docs: returns the ipProtocol of this socket as a string */
std::string	ATcpIpSocket::getProtocolAsStr(void) const
{
	switch (this->_ipProtocol)
	{
		case (IPV4):
			return std::string("IPV4");
			break ;
		case (IPV6):
			return (std::string("IPV6"));
			break ;
	}
	return (std::string());
}

/* docs: returns the port of this socket as a string */
std::string		ATcpIpSocket::getPortAsStr(void) const
{
	char	buff[MAXTCPPORTSTRSIZE];

	snprintf(buff, MAXTCPPORTSTRSIZE - 1, "%d", this->_port);
	return (std::string(buff));
}

/* docs: returns the ip of this socket as a string */
std::string		ATcpIpSocket::getIpAsStr(void) const
{
	return (std::string("Ainda não implementei"));
}

/* docs: returns the ipProtocol of this socket as an int*/
unsigned int	ATcpIpSocket::getProtocolAsUInt(void) const { return (this->_ipProtocol); }

/* docs: returns the port of this socket as an int*/
unsigned int	ATcpIpSocket::getPortAsUInt(void) const { return (this->_port); }

unsigned int	ATcpIpSocket::getIpAsUInt(void) const { return (this->_ipAddress); }
/* static functions */

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
