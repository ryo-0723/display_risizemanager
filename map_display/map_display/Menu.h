#pragma once


#include"display_manager.h"
#include"MenuConstant.h"
#include"Button.h"
#include"Slider.h"
# include <Siv3D.hpp>
class Menu {
private:
	Screen_Resizer& resizer;
	Button& button;
	Slider& slider;
public:
	Menu(Screen_Resizer& resizer, Button& button,Slider& slider)
		:resizer(resizer), button(button),slider(slider) {}
	const Font font{ 20 };
	const Font Feildpickfont{ 20 };

	void MenuFrameDraw() {
		resizer.toReal(Line{ 0,0,0,500 }).draw();
		resizer.toReal(Line{ 5,50,5,resizer.GetNowSize().y - 100 }).draw();
		Print << resizer.GetNowSize();
		//メニュー画面の左側に線を書きたいけどあと回し
	}
	void MenuUIDraw() {

		resizer.toReal(box).draw();
		button.Rect_judge(TCP_box, { 0,0,127 });
		//button.Rect_judge(Wifi_box,10,{0.0,1.0,0.3,0.9});
		font(U"C++").drawAt(resizer.Cal_Pos(box.center()), Palette::Skyblue);


		//resizer.toReal(Feildpick).draw(Palette::Darkgrey);
		Feildpickfont(U"red").drawAt(resizer.Cal_Pos(Feildpick.leftCenter()), Palette::Red);
		Feildpickfont(U"blue").drawAt(resizer.Cal_Pos(Feildpick.rightCenter()), Palette::Aqua);
		Print<<slider.Slider_jadge(Feildpick,{255,0,0},{0,0,255});
	}

};
