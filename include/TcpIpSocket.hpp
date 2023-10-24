#ifndef TCPIPSOCKET_H
# define TCPIPSOCKET_H
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

/*
 * IPV4 | IPV6
 */
typedef enum IpSockProtocols
{
	IPV4 = AF_INET,
	IPV6 = AF_INET6
}	IpSockProtocols;

class TcpIpSocket
{
	public:
		TcpIpSocket(IpSockProtocols protocol, unsigned int port, unsigned int ipAddress);
		~TcpIpSocket(void);
		int	sockListen(int maxConnections = SOMAXCONN);
		int	sockAccept(void);
	private:
		int	_sockFd;
};

#endif
