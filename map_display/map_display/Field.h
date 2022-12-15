#pragma once

#include"display_manager.h"
class Field {
private:
	Screen_Resizer& resizer;
	Vec2  FieldPos() {

	}

public:
	Field(Screen_Resizer& resizer):resizer(resizer){}

	void FieldDraw() {
		Print << resizer.toReal(RectF{ 0,0,1000,1000 }).draw();

		resizer.toReal(RectF{ 0,0,1000,1000 }).draw();
	}
};
