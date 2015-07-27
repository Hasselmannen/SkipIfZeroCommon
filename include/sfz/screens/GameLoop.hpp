#pragma once
#ifndef SFZ_SCREENS_GAME_LOOP_HPP
#define SFZ_SCREENS_GAME_LOOP_HPP

#include <chrono>
#include <memory>
#include <vector>

#include "sfz/screens/BaseScreen.hpp"
#include "sfz/sdl/Window.hpp"
#include "sfz/math/Vector.hpp"

namespace sfz {

using std::shared_ptr;
using std::vector;

class GameLoop final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	GameLoop() = delete;
	GameLoop(const GameLoop&) = delete;
	GameLoop& operator= (const GameLoop&) = delete;

	GameLoop(sdl::Window& window) noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	void run(shared_ptr<BaseScreen> currentScreen);

private:
	// Private methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	float calculateDelta() noexcept;

	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	sdl::Window& mWindow;
	std::chrono::high_resolution_clock::time_point mPreviousTime;
	vector<SDL_Event> mEvents;
};

} // namesapce sfz

#endif