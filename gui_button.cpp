#include "gui_button.hpp"

namespace def::gui
{
	Button::Button(Panel* parent) : Label(parent)
	{
	}

	Button::Button(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Label(parent, text, pos, size)
	{
	}

	Button::~Button()
	{
	}

	bool Button::Update(Platform* platform)
	{
		UpdateText();

		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		if (IsPointInRect(mousePos, m_GlobalPosition, m_Size))
		{
			HandleEvent(this, { Event::Type::Mouse_Hover });

			if (mouse_leftButtonState.pressed)
			{
				m_IsFocused = true;
				HandleEvent(this, { Event::Type::Component_Focused });
			}

			Event mouseEvent;
			mouseEvent.type = Event::Type::None;

			if (mouse_leftButtonState.pressed)
				mouseEvent.type = Event::Type::Mouse_Pressed;
			else if (mouse_leftButtonState.held)
				mouseEvent.type = Event::Type::Mouse_Held;
			else if (mouse_leftButtonState.released)
			{
				mouseEvent.type = Event::Type::Mouse_Released;
				m_IsFocused = false;

				HandleEvent(this, { Event::Type::Component_Unfocused });
			}

			if (mouseEvent.type != Event::Type::None)
				HandleEvent(this, mouseEvent);

			return true;
		}
		else
		{
			if (mouse_leftButtonState.pressed && m_IsFocused)
			{
				m_IsFocused = false;
				HandleEvent(this, { Event::Type::Component_Unfocused });
			}
		}

		return false;
	}

	void Button::Draw(Platform* platform, const Theme& theme) const
	{
		if (m_EnableLight)
		{
			platform->FillRect(m_GlobalPosition, m_Size, theme.ApplyLight(theme.componentBackground));
			platform->DrawRect(m_GlobalPosition, m_Size, theme.ApplyLight(theme.border));
		}
		else
		{
			platform->FillRect(m_GlobalPosition, m_Size, theme.componentBackground);
			platform->DrawRect(m_GlobalPosition, m_Size, theme.border);
		}

		for (size_t i = 0; i < m_TextSplitted.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPosition + unit.offset;
			pos.y += Platform::CHAR_SIZE.y * i;

			if (m_EnableLight)
				platform->DrawText(pos, unit.text, theme.ApplyLight(theme.textRegular));
			else
				platform->DrawText(pos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}
}
