#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../tic_tac_toe/TicTacToe.h"
#include "../tic_tac_toe/TicTacToe.cpp" // do not compiles without it


TEST_CASE("set test", "[TicTacToe]") {
	TicTacToe game;
	REQUIRE(game.set(0));
	REQUIRE_FALSE(game.set(0));

	REQUIRE(game.set(8));
	REQUIRE_FALSE(game.set(8));
}

TEST_CASE("winner test", "[TicTacToe]") {
	TicTacToe game;
	int tactic[]{ 0, 3, 1, 4, 2 }; // for cross
	for (const auto step : tactic)
		REQUIRE(game.set(step));
	const auto winner = game.whoWins();
	REQUIRE(winner.has_value());
	REQUIRE(winner.value() == TicTacToe::State::Cross);
}

TEST_CASE("state test", "[TicTacToe]") {
	TicTacToe game;

	REQUIRE(game.getCurrentState() == TicTacToe::State::Cross);
	game.set(0);
	REQUIRE(game.getCurrentState() == TicTacToe::State::Zero);
}