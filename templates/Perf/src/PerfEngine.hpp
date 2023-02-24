#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace perf
{
class PerfEngine : public red::Engine
{
public:
	bool Create() override;
	bool Destroy() override;

	std::string_view GetGameName() const override;
};
}  // namespace pong