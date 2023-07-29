#include "RedEngine/Thread/ExecutionGraph.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"

namespace red
{
ExecutionGraph& ExecutionGraph::New()
{
    m_stages.clear();
    return *this;
}

ExecutionGraph& ExecutionGraph::AddStage(StageFunc&& fn)
{
    m_stages.push_back(std::move(fn));

    return *this;
}

void ExecutionGraph::Run()
{
    for (auto& fn : m_stages)
    {
        fn();
    }
}

void ExecutionGraph::Clear()
{
    m_stages.clear();
}

ExecutionGraph::ExecutionGraph() : m_stages()
{
}
}  // namespace red