#pragma once

#include <cstdint>

namespace Engine {

enum class PacketType : uint8_t { Login = 1, Welcome = 2, PlayerMove = 3 };

#pragma pack(push, 1)

struct PacketHeader {
	PacketType type;
};

struct LoginPacket {
	PacketHeader header;
};

struct WelcomePacket {
	PacketHeader header;

	uint32_t assignedPlayerID;

	float spawnX;
	float spawnY;
};

struct PlayerMovePacket {
	PacketHeader header;

	uint32_t playerID;

	float x;
	float y;
};

#pragma pack(pop)

} // namespace Engine