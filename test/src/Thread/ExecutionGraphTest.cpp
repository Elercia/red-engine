#include "RedEngine/Thread/ExecutionGraph.hpp"

#include <catch2/catch.hpp>

#include "TestModule.hpp"

using namespace red;

TEST_CASE( "Simple execution graph", "[Thread]" )
{
	auto graph = ExecutionGraph::New();

	int executionOrders[10];
	int executionIndex = 0;

	for( int i = 0; i < 10; i++ )
	{
		graph.AddStage( [&executionOrders, &executionIndex, i]() {
			executionOrders[i] = executionIndex;
			executionIndex++;
		} );
	}

	REQUIRE( executionIndex == 0 );

	graph.Run();

	for( int i = 0; i < 10; i++ )
	{
		REQUIRE( executionOrders[i] == i );
	}
}
