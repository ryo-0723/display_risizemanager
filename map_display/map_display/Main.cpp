﻿# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"Field.h"

SIV3D_SET(EngineOption::Renderer::PlatformDefault);

std::pair<RectF, RectF> Screen_SplitFixedRight(const RectF& raw, double px) {
	return std::make_pair(
		RectF{ 0,0,raw.w - px,raw.h },
		RectF{ raw.w-px,0,px,raw.h }
	);
}

void Main()
{
	Window::SetMinimumFrameBufferSize({ 1000, 700 });
	Window::Resize(1000, 1000);
	Screen_Resizer display1({ 8000,7500 });
	Screen_Resizer Menu({ 700,500 }, ScreenStyle::Keep);
	Field field(display1);
	display1.SetStyle(ScreenStyle::Center);
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを自由に大きさ変えれるやつ

	while (System::Update())
	{
		const auto [left, right] = Screen_SplitFixedRight(Scene::Rect(), 600);
		left.draw(ColorF{ 0.0, 0.5, 1.0, 0.1 });
		right.draw(ColorF{ 1.0, 0, 0, 0.1 });
		display1.Resize_Update(left);
		Menu.Resize_Update(right);



		ClearPrint();
		Print << Menu.Get_Pos();
		Print << Cursor::Pos();
		Print << right.pos.x;
		display1.toReal(RectF{ 0,0, 8000, 7500 }).draw(ColorF{ 0, 1.0, 0, 0.5 });
		//display2.toReal(RectF{ 0,0, 700, 1000 }).draw(ColorF{ 0.0, 0.5, 1.0, 0.5 });
		field.FieldDraw();

	}
}
