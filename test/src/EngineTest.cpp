#include "EngineTest.hpp"

namespace red
{
EngineTest::EngineTest() = default;
EngineTest::~EngineTest() = default;

bool EngineTest::Create()
{
    return true;
}
bool EngineTest::Destroy()
{
    return true;
}

std::string_view EngineTest::GetGameName() const
{
    return "TestEngine";
}

bool EngineTest::RegisterComponentTypes()
{
    return true;
}

void EngineTest::SetupLogger()
{
}

}  // namespace red