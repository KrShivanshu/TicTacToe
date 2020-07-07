#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "AssetMan.h"
#include "InputMan.h"
#include "StateMan.h"
using namespace std;
using namespace sf;
namespace Engine {
	struct Content
	{
		unique_ptr<AssetMan>_assets;
		unique_ptr<InputMan>_inputs;
		unique_ptr<StateMan>_states;
		unique_ptr<RenderWindow>_window;

		Content()
		{
			_assets = make_unique<AssetMan>();
			_states = make_unique<StateMan>();
			_inputs = make_unique<InputMan>();
			_window = make_unique<RenderWindow>();

		}
	};
	class Game
	{
	private:
		shared_ptr<Content>_content;
		const Time TIME_PER_FRAME = seconds(1.f / 60.f);

	public:
		Game();
		~Game();
		void Run();
	};
}

