#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
	sf::TcpListener serverListener;
	if (serverListener.listen(4005) != sf::Socket::Done)
		cout << "Could not bind port!" << endl;

	while (true)
	{
		sf::TcpSocket client;
		if (serverListener.accept(client) != sf::Socket::Done)
		{
			// error...
		}
			cout << "Found a connection!" << endl;
			while (!client.Disconnected)
			{

			}
			cout << "Client disconnected!?" << endl;
	}

	return 0;
}