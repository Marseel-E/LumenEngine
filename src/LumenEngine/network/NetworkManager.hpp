#pragma once

#include <enet/enet.h>

#include <functional>
#include <string>

#include "Protocol.hpp"

namespace Engine {

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();

	bool Init();
	void Shutdown();

	void Update(std::function<void(PacketType, void*, size_t)> onPacketReceived);

	bool Connect(const std::string& host, int port);
	void SendPacket(const void* data, size_t size, bool reliable = true);

private:
	ENetHost* m_client = nullptr;
	ENetPeer* m_serverPeer = nullptr;
};

} // namespace Engine