#pragma once

#include "RedEngine/Core/Engine.hpp"

namespace red
{
class EngineTest : public red::Engine
{
public:
    EngineTest();
    virtual ~EngineTest();

    virtual bool Create() override;
    virtual bool Destroy() override;

    virtual std::string_view GetGameName() const override;

    virtual bool RegisterComponentTypes() override;

    virtual void SetupLogger() override;
};

}  // namespace red