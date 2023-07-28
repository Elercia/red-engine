#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace perf
{
class PerfEngine : public red::Engine
{
public:
	bool Create() override;
	bool Destroy() override;

	StringView GetGameName() const override;
};
}  // namespace pong