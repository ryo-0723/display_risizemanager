﻿#pragma once
#include"display_manager.h"

class Button {
private:
	Screen_Resizer& resizer;
public:
	Button(Screen_Resizer& resizer) :resizer(resizer) {}

	void Rect_judge(RoundRect rect) {
		if (resizer.toReal(rect).leftPressed())
			resizer.toReal(rect).movedBy(resizer.Cal_Size({ 10,10 })).draw();
		else
			resizer.toReal(rect).drawShadow(resizer.Cal_Size({ 10,10 }), 0, 0).draw();
	}
	bool Rect_judge(RoundRect rect, Font font, String defaultstring, String pushstring, Color defaultcolor, Color pushcolor) {
		if (resizer.toReal(rect).mouseOver()&& resizer.toReal(rect).leftPressed()) {
				resizer.toReal(rect).draw(pushcolor);
				font(pushstring).drawAt(resizer.Cal_Pos(rect.center()), Palette::Skyblue);
			}
		else {
			resizer.toReal(rect).draw(defaultcolor);
			font(defaultstring).drawAt(resizer.Cal_Pos(rect.center()), Palette::Skyblue);
		}
		return 0;
	}

};
