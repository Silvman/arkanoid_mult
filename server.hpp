//
// Created by alex on 29.04.17.
//

#include <SFML/Network.hpp>
#include <iostream>


////////////////////////////////////////////////////////////
/// Launch a server, wait for an incoming connection,
/// send a message and wait for the answer.
///
////////////////////////////////////////////////////////////
void runTcpServer(unsigned short port)
{
	// Create a server socket to accept new connections
	sf::TcpListener listener;
	// Listen to the given port for incoming connections
	if (listener.listen(2888) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	// Wait for a connection
	sf::TcpSocket socket;
	if (listener.accept(socket) != sf::Socket::Done)
		return;
	std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;

	// Send a message to the connected client
	const char out[] = "Hi, I'm the server";
	if (socket.send(out, sizeof(out)) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

	// Receive a message back from the client
	char in[128];
	std::size_t received;
	if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
		return;
	std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;
}
