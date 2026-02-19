#include "NetworkManager.hpp"

#include "LumenEngine/core/Logger.hpp"

namespace Engine {

NetworkManager::NetworkManager() {};

NetworkManager::~NetworkManager() {
	Shutdown();
};

bool NetworkManager::Init() {
	if (enet_initialize() != 0) {
		Logger::Error("Failed to init ENet!");

		return false;
	};

	Logger::Info("ENet initalized!");

	m_client = enet_host_create(nullptr, 1, 2, 0, 0);

	if (m_client == nullptr) {
		Logger::Error("Failed to create ENet client host.");

		return false;
	};

	return true;
};

void NetworkManager::Shutdown() {
	if (m_client) {
		enet_host_destroy(m_client);
		m_client = nullptr;
	};

	enet_deinitialize();
};

bool NetworkManager::Connect(const std::string& hostAddress, int port) {
	ENetAddress address;
	ENetEvent event;

	enet_address_set_host(&address, hostAddress.c_str());
	address.port = port;

	m_serverPeer = enet_host_connect(m_client, &address, 2, 0);

	if (m_serverPeer == nullptr) {
		Logger::Error("No avaiable peers to init ENet connection.");

		return false;
	};

	if (enet_host_service(m_client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
		Logger::Info("Connected to: " + hostAddress);

		LoginPacket packet;
		packet.header.type = PacketType::Login;
		SendPacket(&packet, sizeof(LoginPacket), true);

		return true;
	};

	enet_peer_reset(m_serverPeer);

	Logger::Error("Failed to connect to", hostAddress);

	return false;
};

void NetworkManager::Update(std::function<void(PacketType, void*, size_t)> onPacketReceived) {
	ENetEvent event;

	while (enet_host_service(m_client, &event, 0) > 0) {
		switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				Logger::Info("Packet recieved, length: " + std::to_string(event.packet->dataLength));

				if (event.packet->dataLength >= sizeof(PacketHeader)) {
					auto* header = (PacketHeader*)event.packet->data;

					if (onPacketReceived) {
						onPacketReceived(header->type, event.packet->data, event.packet->dataLength);
					};
				};

				enet_packet_destroy(event.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Warn("Disconnected from server.");

				break;

			default:
				break;
		};
	};
};

void NetworkManager::SendPacket(const void* data, size_t size, bool reliable) {
	if (!m_serverPeer) return;

	ENetPacket* packet = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : 0);

	enet_peer_send(m_serverPeer, 0, packet);
};

} // namespace Engine