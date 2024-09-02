#include "gui_label.hpp"

namespace def::gui
{
	Label::Label(Panel* parent) : Component(parent)
	{
		SetTextAlign(Align::LEFT);
	}

	Label::Label(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size) : Component(parent, pos)
	{
		m_Text = text;
		SetTextAlign(Align::LEFT);
		SetSize(size);
	}

	Label::~Label()
	{
	}

	std::string Label::GetText() const
	{
		return m_Text;
	}

	void Label::SetText(const std::string& text)
	{
		m_Text = text;
		SetTextAlign(m_Align);
	}

	void Label::Update(Platform* platform)
	{
	}

	void Label::Draw(Platform* platform, const Theme& theme) const
	{
		platform->FillRect(m_GlobalPosition, m_PhysicalSize, theme.componentBackground);
		platform->DrawRect(m_GlobalPosition, m_PhysicalSize, theme.border);

		for (size_t i = 0; i < m_TextSplitted.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPosition + unit.offset;
			pos.y += 8 * i;

			platform->DrawText(pos, unit.text, theme.text);
		}
	}

	Vector2i Label::GetSize() const
	{
		return m_CharsSize;
	}

	void Label::SetSize(const Vector2i& size)
	{
		m_CharsSize = size;
		m_PhysicalSize = { size.x * 8 + 4, size.y * 8 + 2 };
	}

	Align Label::GetTextAlign() const
	{
		return m_TextAlign;
	}

	void Label::SetTextAlign(Align align)
	{
		std::vector<std::string> lines;
		size_t linesCount = 1;

		if (m_Text.find('\n') == std::string::npos)
		{
			// No '\n' symbols so no new lines either
			lines.push_back(m_Text);
		}
		else
		{
			for (auto c : m_Text)
			{
				if (c == '\n')
					linesCount++;
			}

			lines.reserve(linesCount);

			std::string buffer;

			for (auto c : m_Text)
			{
				if (c == '\n')
				{
					lines.push_back(buffer);
					buffer.clear();
				}
				else
					buffer += c;
			}

			if (!buffer.empty())
				lines.push_back(buffer);
		}

		m_TextSplitted.clear();
		m_TextSplitted.resize(linesCount);

		for (size_t i = 0; i < linesCount; i++)
		{
			auto& unit = m_TextSplitted[i];
			unit.text = lines[i];

			int length = lines[i].length();

			switch (align)
			{
			case Align::LEFT: unit.offset = { 0, 0 }; break;
			case Align::CENTRE: unit.offset = { m_PhysicalSize.x / 2 - length * 4 - 2, 0 }; break;
			case Align::RIGHT: unit.offset = { m_PhysicalSize.x - length * 8 - 2, 0 }; break;
			}

			unit.offset += 2;
		}

		m_TextAlign = align;
	}
}
