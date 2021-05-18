#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace pong
{
class PongEngine : public red::Engine
{
public:
	virtual bool Create() override;
};
}  // namespace pong