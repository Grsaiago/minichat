#include "./include/TcpIpSocket.hpp"

int	main(void)
{
	TcpIpSocket	sock(IPV4, 1234, 0);
	sock.sockListen();
	sock.sockAccept();
	return (0);
}
