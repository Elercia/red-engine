#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace pong
{
class PongEngine : public red::Engine
{
public:
	bool Create() override;
	bool Destroy() override;
};
}  // namespace pong