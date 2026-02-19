#include "GraphicsContext.hpp"

#include "LumenEngine/core/Logger.hpp"

#if defined(__APPLE__)
#include "LumenEngine/systems/platform/metal/MetalContext.hpp"
#elif defined(_WIN32)
...
#endif

namespace Engine {

GraphicsContext* GraphicsContext::Create(Window& window) {
#if defined(__APPLE__)
	return new MetalContext(window);
#elif defined(_WIN32)
		Logger::Error("Windows/DirectX not implemented yet!");

		return nullptr;
#else
	Logger::Error("Unknown platform!");

	return nullptr;
#endif
};

} // namespace Engine