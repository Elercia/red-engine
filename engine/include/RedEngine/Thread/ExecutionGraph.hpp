#pragma once

#include "RedEngine/Core/Container/Array.hpp"

#include <functional>

namespace red
{
	class ExecutionGraph
	{
	public:
		static ExecutionGraph New();

		using StageFunc = std::function<void( void )>;

		ExecutionGraph& AddStage( StageFunc&& fn );

		void Clear();
		void Run();

	private:
		ExecutionGraph();
		ExecutionGraph( ExecutionGraph&& ) = delete;
		ExecutionGraph& operator=( ExecutionGraph&& ) = delete;

	private:
		Array<StageFunc> m_stages;
	};
}