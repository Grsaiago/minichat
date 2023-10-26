#include "./include/ATcpIpSocket.hpp"

int	main(void)
{
	ATcpIpSocket	sock(IPV4, 1234, 0);

	sock.initSocket();
	sock.listenSocket();
	sock.acceptOnSocket();
	return (0);
}
