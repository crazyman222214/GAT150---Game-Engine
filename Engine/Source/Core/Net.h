#pragma once
#include "Json.h"
#include <enet/enet.h>

class Net //named Net to avoid confusion with the library
{
public:
	bool Initialize();
	bool Shutdown();

	bool CreateServer();
	bool CreateClient(ENetHost* client, ENetPeer* server);
	bool ConnectClient(ENetHost* client, ENetPeer* server);

	void sendMessage(const char* data, size_t s, ENetPeer* to);
	void HostCheckForConnection();
	void ClientFunction();

	void sendMessageToHost(std::string message);
	void sendMessageToClient(std::string message);

	bool connection = false;
private:
	ENetAddress address;
	ENetHost* server{ nullptr };
	ENetPeer* client{ nullptr };
	
	ENetHost* clientClient{ nullptr };
	ENetPeer* clientServer{ nullptr };
	//ENetPeer* peer; //Assuming one client for test purposes, will develop with vectors and clean up

};