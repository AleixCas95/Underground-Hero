#include "j1App.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Module.h"
#include "p2Log.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UIObject.h"
#include "p2List.h"

j1Gui::j1Gui() : j1Module() {

	name.create("gui");

}


j1Gui::~j1Gui(){}

bool j1Gui::Awake(pugi::xml_node& conf) {

	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

bool j1Gui::Start() {

	atlas = App->tex->Load(atlas_file_name.GetString());
	return true;
}

bool j1Gui::PreUpdate() {


	return true;
}

bool j1Gui::Update(float dt) {

	for (int i = 0; i < UIObjects.count(); ++i) {

		if (UIObjects.At(i) != nullptr) {

			UIObjects.At(i)->data->Draw();
			UIObjects.At(i)->data->Update();
		}
	}

	return true;
}

bool j1Gui::PostUpdate() {

	return true;
}

bool j1Gui::CleanUp() {

	return true;
}


UIObject* j1Gui::CreateUIImage(int x, int y, SDL_Rect rect, SDL_Texture* texture) {

	if (texture == nullptr) {
		UIImage* image = new UIImage(x ,y, rect, atlas);

		UIObjects.add(image);
		return image;

	
	}
	else {
		UIImage* image = new UIImage(x, y, rect, texture);

		UIObjects.add(image);
		return image;


	}

	
}

UIObject* j1Gui::CreateUILabel(int x, int y, p2SString text) {

	UILabel* label = new UILabel(x, y, text);

	UIObjects.add(label);
	return label;

}

UIObject * j1Gui::CreateUIButton(int x, int y, SDL_Rect mouse_off, SDL_Rect mouse_on, SDL_Rect mouse_click, SDL_Texture * texture)
{
	UIButton* button = new UIButton(x, y, mouse_off, mouse_on, mouse_click, texture);
	UIObjects.add(button);
	return button;
}

