﻿#include "gui_manager.hpp"
#include "gui_elements.hpp"

#include "gui_platform_defGameEngine.hpp"

using namespace def::gui;

class GUI_Testing : public def::GameEngine
{
public:
	GUI_Testing()
	{
		SetTitle("Testing GUI");
		UseOnlyTextures(true);
	}

	Platform_defGameEngine* platform;
	std::unique_ptr<Manager> manager;
	Panel *panel1, *panel2;

	Label* label;
	Button* button;
	TextEntry* textentry;
	List* list;
	Slider<float>* slider;

	Theme theme;

protected:
	static void Event_Button(Component* component, const Event& event, const std::any& userdata)
	{
		Button* button = static_cast<Button*>(component);
		GUI_Testing* app = std::any_cast<GUI_Testing*>(userdata);

		if (event.type == Event::Type::Mouse_Released)
			app->list->AddString(app->textentry->GetText());
	}

	bool OnUserCreate() override
	{
		theme.panelBackground = { 0, 55, 150 };
		theme.componentBackground = { 0, 0, 150 };
		theme.titleBar = { 220, 220, 220 };
		theme.border = { 220, 220, 200 };
		theme.textRegular = { 200, 200, 0 };
		theme.textTitle = { 32, 32, 32 };
		theme.cursor = { 200, 200, 200 };
		theme.placeholder = { 100, 100, 0 };
		theme.slider = { 200, 250, 0 };
		theme.focusedLightFactor = 1.5f;

		platform = new Platform_defGameEngine(this);
		manager = std::make_unique<Manager>(platform);

		panel1 = manager->AddPanel("Some title 1", { 10, 10 }, { 500, 200 });
		panel2 = manager->AddPanel("Some title 2", { 600, 300 }, { 300, 400 });

		label = new Label(panel1, "Some text", { 20, 20 }, { 20, 1 });
		button = new Button(panel1, "Add", { 200, 50 }, { 3, 1 });
		textentry = new TextEntry(panel1, { 20, 50 }, { 20, 1 });

		textentry->SetPlaceholder("Write here...");
		button->SetEventHandler(Event_Button, this);

		list = new List(panel1, { 20, 80 }, { 20, 10 });

		slider = new Slider<float>(panel1, { 250, 60 }, { 300, 60 }, { 5, 5 }, -50.0f, 50.0f, 0.0f);

		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
		manager->Update();

		ClearTexture(def::BLACK);
		manager->Draw(theme);

		DrawTextureString({ 10, 10 }, std::to_string(slider->GetValue()));

		return true;
	}
};

int main()
{
	GUI_Testing app;

	if (app.Construct(640, 360, 2, 2))
		app.Run();

	return 0;
}
