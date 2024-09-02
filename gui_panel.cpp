#include "gui_panel.hpp"
#include "gui_component.hpp"

namespace def::gui
{
	Panel::Panel()
	{
	}

	Panel::Panel(const std::string& title, const Vector2i& pos, const Vector2i& size)
		: m_Title(title), m_Position(pos), m_Size(size)
	{
	}

	Panel::~Panel()
	{
	}

	std::list<Component*>& Panel::GetComponents()
	{
		return m_Components;
	}

	std::string Panel::GetTitle() const
	{
		return m_Title;
	}

	void Panel::SetTitle(const std::string& title)
	{
		m_Title = title;
	}

	Vector2i Panel::GetPosition() const
	{
		return m_Position;
	}

	void Panel::SetPosition(const Vector2i& pos)
	{
		m_Position = pos;
	}

	Vector2i Panel::GetSize() const
	{
		return m_Size;
	}

	void Panel::SetSize(const Vector2i& size)
	{
		m_Size = size;
	}

	void Panel::Draw(Platform* platform, const Theme& theme) const
	{
		// TODO: Make thickness of title bar customisable
		platform->FillRect(m_Position, m_Size, theme.panelBackground);
		platform->DrawRect(m_Position, m_Size, theme.border);
		platform->FillRect(m_Position, { m_Size.x, 20 }, theme.titleBar);

		for (auto& component : m_Components)
			component->Draw(platform, theme);
	}
}