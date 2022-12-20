#pragma once
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
	void Rect_judge(RoundRect rect, Color color) {
		if (resizer.toReal(rect).mouseOver())
			resizer.toReal(rect).draw();
		else
			resizer.toReal(rect).draw(color);
	}

};
