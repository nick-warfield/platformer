#include "player.hpp"

Player make_player(
		int hp,
		sf::Vector2<float> position,
		sf::Vector2<int> frame_size,
		std::map<State, SpriteSheet> sprite_atlas
			= std::map<State, SpriteSheet>(),
		std::map<State, sf::Sound> sfx_atlas
			= std::map<State, sf::Sound>())
{
	Player player;
	player.hp = hp;
	player.position = position;
	player.velocity = sf::Vector2<float>(0.0f, 0.0f);
	player.state = State::IDLE;
	player.current_frame = 0;
	player.sprite_atlas = sprite_atlas;
	player.sfx_atlas = sfx_atlas;

	return player;
}

void next_frame(Player& player) {
	player.current_frame++;
	player.current_frame %= player.sprite_atlas[player.state].frame_count;
}
