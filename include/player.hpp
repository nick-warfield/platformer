#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum State {
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK,
	ROLL,
	HURT,
	DEATH
};

struct SpriteSheet {
	int frame_count;
	sf::Vector2<int> frame_size;
	sf::Sprite sheet;
};

struct Player {
	int hp;
	sf::Vector2<float> position;
	sf::Vector2<float> velocity;

	State state;
	int current_frame;
	std::map<State, SpriteSheet> sprite_atlas;
	std::map<State, sf::Sound> sfx_atlas;
};

Player make_player(
		int,
		sf::Vector2<float>,
		sf::Vector2<int>,
		std::map<State, SpriteSheet>,
		std::map<State, sf::Sound>);
void update_sprite_atlas(Player&, State, sf::Sprite);
void update_sfx_atlas(Player&, State, sf::Sound);
void change_state(Player&, State);
void next_frame(Player&);

void move(Player&, sf::Vector2<float>, float);
void jump(Player&);
void attack(Player&);
void roll(Player&);

