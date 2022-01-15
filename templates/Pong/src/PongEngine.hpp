#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace pong
{
class PongEngine : public red::Engine
{
public:
	bool Create() override;
	bool Destroy() override;

	std::string_view GetGameName() const;

	virtual bool RegisterComponentTypes() override;
};
}  // namespace pong