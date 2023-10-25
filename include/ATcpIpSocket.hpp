#ifndef ATCPIPSOCKET_H
# define ATCPIPSOCKET_H
# include <unistd.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>

/*
 * IPV4 | IPV6
 */
typedef enum IpSockProtocols
{
	IPV4 = AF_INET,
	IPV6 = AF_INET6
}	IpSockProtocols;

class ATcpIpSocket
{
	public:
		ATcpIpSocket(void);
		~ATcpIpSocket(void);
		int		sockListen(int maxConnections = SOMAXCONN);
		int		sockAccept(void);
		void	sockClose(void);
		void	sockConnect(void);

		/* static functions */
		static bool isSocketFd(int fd);

	private:
		/* internal socket fd */
		int			_sockFd;
		void		initSocket(IpSockProtocols protocol, unsigned int port, unsigned int ipAddress);

		/* exceptions */
		class SocketFailedExcpetion : public std::runtime_error {
			public:
				SocketFailedExcpetion(std::string message);
		};
};

#endif
