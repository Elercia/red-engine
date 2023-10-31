#include "EngineTest.hpp"

#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Configuration/CVar.hpp"

namespace red
{

EngineTest::EngineTest() = default;
EngineTest::~EngineTest() = default;

bool EngineTest::Create()
{
    auto cvar = CVarManager::GetInstance().GetFromName<int>("Engine_Thread_ThreadCount");
    
    cvar.ChangeValue(1);

    m_scheduler.Init();

    InitAllocator();

    return true;
}
bool EngineTest::Destroy()
{
    red_free(m_frameAllocator);

    m_scheduler.Finalize();

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


#include <catch2/catch.hpp>

int main(int argc, char* argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}