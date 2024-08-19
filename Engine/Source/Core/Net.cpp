#include "Net.h"
#include <iostream>

bool Net::Initialize()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet.\n";
        return false;
    }

    CreateServer();
    return true;
}

bool Net::Shutdown()
{
    return false;
}

bool Net::CreateServer()
{
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */

    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1233. */
    address.port = 1233;

    server = enet_host_create(
        &address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */
    );

    if (!server)
    {
        std::cerr << "An error occurred while trying to create an ENet server host.\n";
        return false;
    }

    return true;
}



bool Net::CreateClient(ENetHost* client, ENetPeer* server)
{
    
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    if (!client)
    {
        std::cerr << "An error occurred while trying to create an ENet client host.\n";
        return false;
    }
    
    return ConnectClient(client, server);
}

bool Net::ConnectClient(ENetHost* client, ENetPeer* server)
{

    enet_address_set_host(&address, "localhost");
    address.port = 1233;

    server = enet_host_connect(client, &address,2,0);
    if (!server)
    {
        std::cerr << "An error occurred while trying to connect to ENet Server\nAddress: " << &address;

        enet_host_destroy(client);
    }
    else
    {
        ENetEvent event = {};
        if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        {
            std::cout << "Connection Started!";
            while (true)
            {
                ENetEvent event;
                while (enet_host_service(client, &event, 10) > 0)
                {
                    switch (event.type)
                    {
                    case ENET_EVENT_TYPE_CONNECT:
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        std::cout << "A packet has hit the pentagon";
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        std::cout << "server disconnected";
                        break;
                    }
                }

                std::string message = "";
                std::cin >> message;

                if (!message.empty())
                {
                    sendMessage(message.c_str(), message.size() + 1, server);
                }
            }
        }
        else 
        {
            std::cout << "Failed to Connect (Internally Crying)\n" << event.type << "\n " << ENET_EVENT_TYPE_NONE;

        }
        enet_peer_reset(server);
        enet_host_destroy(client);
    }
    return true;
}

void Net::sendMessage(const char* data, size_t s, ENetPeer* to)
{
    ENetPacket* packet = enet_packet_create(data, s, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(to, 0, packet);
}

void Net::HostCheckForConnection()
{
    ENetEvent event = {};

    /* Wait up to 10 milliseconds for an event. */
    while (enet_host_service(server, &event, 10) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "wow";
            std::cout << "A new client connected from %x:%u.\n" <<
                event.peer->address.host << " " <<
                event.peer->address.port;

            /* Store any relevant client information here. */
            client = event.peer;

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "A packet of length %u containing %s was received from %s on channel %u.\n" <<
                event.packet->dataLength <<
                event.packet->data <<
                event.peer->data<<
                event.channelID;

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);


            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "%s disconnected.\n";

            /* Reset the peer's client information. */

            client = 0;
        }
    }
    if (client)
    {
        std::string d;
        std::cout << "OMG CLIENT\n";
        std::cin >> d;
        
        sendMessage(d.c_str(), d.size() + 1, client);

    }
}

void Net::ClientFunction()
{
    ENetHost* client{ nullptr };
    ENetPeer* server{ nullptr };
    CreateClient(client, server);
}
