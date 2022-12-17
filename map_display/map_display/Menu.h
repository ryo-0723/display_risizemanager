#pragma once
#include"display_manager.h"
#include"MenuConstant.h"
# include <Siv3D.hpp>
class Menu {
	private:
		Screen_Resizer& resizer;
public:
	Menu(Screen_Resizer& resizer) :resizer(resizer) {}
		const Font font{ 20 };

	void MenuFrameDraw() {
		resizer.toReal(Line{0,0,0,500}).draw();
		resizer.toReal(Line{ 5,50,5,resizer.GetNowSize().y-100}).draw();
		Print << resizer.GetNowSize();
		//メニュー画面の左側に線を書きたいけどあと回し
	}
	void MenuUIDraw() {
		resizer.toReal(box).draw();
		if(resizer.toReal(TCP_box).mouseOver()){
			resizer.toReal(TCP_box).movedBy(10,10).draw();
		}
		else {
			resizer.toReal(TCP_box).drawShadow(Vec2{ 10,10 }, 2, 2).draw();

		}
		font(U"C++").drawAt(resizer.Cal_Pos(box.center()), Palette::Skyblue);
	}



};
