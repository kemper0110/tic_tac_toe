#pragma once

#include <array>
#include <algorithm>
#include <ranges>
#include <optional>


class TicTacToe {
public:
	enum class State {
		None, Cross, Zero
	};
private:
	std::array<State, 9> field{};
	State current_state = State::Cross;
public:
	static State nextState(const State state);
	inline State getCurrentState() const {
		return current_state;
	}
	bool set(int pos);
	std::optional<State> whoWins() const;
	void clear();
private:
	bool isWinning(State state) const;
};