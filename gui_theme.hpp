#pragma once

#include "gui_utils.hpp"

namespace def::gui
{
	struct Theme
	{
		Colour ApplyLight(const Colour& colour) const;

		Colour border;
		Colour componentBackground;
		Colour panelBackground;
		Colour textRegular;
		Colour textTitle;
		Colour placeholder;
		Colour titleBar;
		Colour cursor;
		Colour slider;

		float focusedLightFactor = 0.0f;
		bool forceUsingPlaceholder = false;
	};
}
