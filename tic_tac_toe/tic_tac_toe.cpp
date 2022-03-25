#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <array>
#include <algorithm>
#include <ranges>
#include <optional>
#include <iostream>
#include <memory>

#include "TicTacToe.h"

#ifdef _DEBUG
constexpr auto debug = true;
#else
constexpr auto debug = false;
#endif


int main()
{
	using namespace nana;

	form fm(API::make_center(480, 480),
		appear::decorate<appear::taskbar, appear::floating, appear::minimize>()
	);
	fm.caption("Tic-Tac-Toe");

	fm.div(
		"vert"
		"<move_label weight=10%>"
		"<keys margin=2 grid=[3, 3] gap=2>"
	);

	label move_label(fm, "cross moves");
	move_label.typeface(paint::font("", 15));
	move_label.text_align(align::center);


	const paint::image cross_image("cross.png");
	const paint::image zero_image("zero.png");

	TicTacToe game;

	std::vector<std::unique_ptr<button>> keys;
	paint::font keyfont("", 10, true);

	for (int i = 0; i < 9; ++i) {
		auto& key = *keys.emplace_back(std::make_unique<button>(fm));
		key.typeface(keyfont);
		key.events().click([pos = i, &game, &keys, &cross_image, &zero_image, &move_label, &fm](const nana::arg_click& arg) {
			if constexpr (debug)
				std::cout << "user clicked " << pos << "\n";
			const auto state = game.getCurrentState();

			const auto success = game.set(pos);
			if (not success)
				return;

			switch (state) {
			case TicTacToe::State::Cross:
				keys[pos].get()->icon(cross_image);
				move_label.caption("Zero moves");
				break;
			case TicTacToe::State::Zero:
				keys[pos].get()->icon(zero_image);
				move_label.caption("Cross moves");
				break;
			}
			const auto winner = game.whoWins();
			if (not winner.has_value())
				return;

			std::string winner_name;
			switch (winner.value()) {
			case TicTacToe::State::Cross: winner_name = "Cross"; break;
			case TicTacToe::State::Zero: winner_name = "Zero";  break;
			case TicTacToe::State::None: winner_name = "Nobody";  break;
			}

			msgbox msg(fm, "Game ended", msgbox::button_t::yes_no);
			msg << winner_name << " wins. Restart the game?\n";
			const auto picked = msg();
			switch (picked) {
			case msgbox::pick_t::pick_yes:
				move_label.caption("cross moves");
				// erase images from all buttons
				std::ranges::for_each(keys,
					[](button* but) { but->icon(paint::image()); },
					&std::unique_ptr<button>::get);
				game.clear();
				break;
			case msgbox::pick_t::pick_no:
				fm.close();
			}
			}
		);
		fm["keys"] << key;
	}
	fm["move_label"] << move_label;
	fm.collocate();
	fm.show();
	exec();
}
