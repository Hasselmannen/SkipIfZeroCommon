#pragma once
#ifndef SFZ_SCREENS_BASE_SCREEN_HPP
#define SFZ_SCREENS_BASE_SCREEN_HPP

#include <memory>
#include <vector>

#include "sfz/SDL.hpp"
#include "sfz/math/Vector.hpp"

namespace sfz {

using std::shared_ptr;
using std::vector;

class BaseScreen; // Forward declaration for ScreenUpdateOp

// ScreenUpdateOp
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

enum class ScreenUpdateOpType {
	NO_OPERATION,
	SWITCH_SCREEN,
	QUIT_APPLICATION
};

struct ScreenUpdateOp final {
	ScreenUpdateOp() noexcept = default;
	ScreenUpdateOp(const ScreenUpdateOp&) noexcept = default;
	ScreenUpdateOp& operator= (const ScreenUpdateOp&) noexcept = default;
	inline ScreenUpdateOp(ScreenUpdateOpType type, shared_ptr<BaseScreen> screen = nullptr) noexcept
	:
		type{type},
		newScreen{screen}
	{ }

	ScreenUpdateOpType type;
	shared_ptr<BaseScreen> newScreen;
};

// BaseScreen
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

class BaseScreen {
public:
	virtual ~BaseScreen() = default;

	virtual ScreenUpdateOp update(const vector<SDL_Event>& events, float delta) = 0;
	virtual void render(float delta) = 0;

	virtual void onQuit();
	virtual void onResize(vec2 dimensions);
};

inline void BaseScreen::onQuit() { /* Default empty implementation. */ }
inline void BaseScreen::onResize(vec2) { /* Default empty implementation. */ }

} // namespace sfz

#endif