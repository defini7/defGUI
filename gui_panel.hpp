#pragma once

#include <list>
#include <string>
#include <memory>

#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_eventhandler.hpp"
#include "gui_component.hpp"

namespace def::gui
{
	class Panel : public Component
	{
	public:
		Panel(Component* parent = nullptr);
		Panel(Component* parent, const std::string& title, const Vector2i& pos, const Vector2i& size);
		~Panel();

	public:
		const std::string& GetTitle() const;
		void SetTitle(const std::string& title);

		bool Update(Platform* platform);
		void Draw(Platform* platform, const Theme& theme) const;

		void ShowTitleBar(bool enable);
		void ShowTitle(bool enable);

		void FixPosition(bool enable);

	private:
		std::string m_Title;

		Vector2i m_DragOffset;
		bool m_Drag = false;

		bool m_FixedPos = false;

		bool m_ShowTitleBar = true;
		bool m_ShowTitle = true;

	public:
		static constexpr int TITLE_BAR_WIDTH = 20;

	};
}
