#include "TicTacToe.h"


TicTacToe::State TicTacToe::nextState(const State state) {
	if (state == State::Cross)
		return State::Zero;
	if (state == State::Zero)
		return State::Cross;
	return State::None;
}

bool TicTacToe::set(int pos) {
	if (field[pos] == State::Cross || field[pos] == State::Zero)
		return false;
	field[pos] = current_state;
	current_state = nextState(current_state);
	return true;
}

std::optional<TicTacToe::State> TicTacToe::whoWins() const {
	if (isWinning(State::Cross))
		return State::Cross;
	if (isWinning(State::Zero))
		return State::Zero;
	// if all not equal to None then field is full
	const auto field_full = std::ranges::all_of(field, [](const State cellState) { return cellState != State::None; });
	if (field_full)
		return State::None;
	return std::nullopt;
}

void TicTacToe::clear() {
	std::ranges::fill(field, State::None);
	current_state = State::Cross;
}


bool TicTacToe::isWinning(TicTacToe::State state) const {
	constexpr std::array<std::array<int, 3>, 8> victory_table{
		// horizontal lines
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		// vertical lines
		0, 3, 6,
		1, 4, 7,
		2, 5, 8,
		// diagonal lines
		0, 4, 8,
		2, 4, 6
	};

	return std::ranges::any_of(victory_table, [this, state](const std::array<int, 3>& row) {
		return std::ranges::all_of(row, [this, state](int pos) {
			return field[pos] == state;
			}
		); }
	);
}