#ifndef ATCPIPSOCKET_H
# define ATCPIPSOCKET_H
# include <unistd.h>
# include <cstdio>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>

#ifndef MAXTCPPORTSRTRSIZE
# define MAXTCPPORTSTRSIZE 7
#endif

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
		ATcpIpSocket(IpSockProtocols ipProtocol, unsigned int port, unsigned int ipAddress);
		~ATcpIpSocket(void);
		void			initSocket(void);
		int				listenSocket(int maxConnections = SOMAXCONN);
		int				acceptOnSocket(void);
		void			connectSocket(void);
		void			closeSocket(void);
		std::string		getProtocolAsStr(void) const;
		std::string		getPortAsStr(void) const;
		std::string		getIpAsStr(void) const;
		unsigned int	getProtocolAsUInt(void) const;
		unsigned int	getPortAsUInt(void) const;
		unsigned int	getIpAsUInt(void) const;

		/* static functions */
		static bool isSocketFd(int fd);

	private:
		/* internal socket fd */
		int				_sockFd;
		IpSockProtocols	_ipProtocol;
		int				_port;
		int				_ipAddress;

		/* exceptions */
		class SocketFailedExcpetion : public std::runtime_error {
			public:
				SocketFailedExcpetion(std::string message);
		};
};

#endif
