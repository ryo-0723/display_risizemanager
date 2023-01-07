﻿# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"Field.h"
#include"Menu.h"

SIV3D_SET(EngineOption::Renderer::Direct3D11);
Array<String>items = {U"hello",U"good"};
std::pair<RectF, RectF> Screen_SplitFixedRight(const RectF& raw, double px) {
	return std::make_pair(
		RectF{ 0,0,raw.w - px,raw.h },
		RectF{ raw.w - px,0,px,raw.h }
	);
}

void Main()
{
	Window::SetMinimumFrameBufferSize({ 1200, 700 });
	Window::Resize(1400, 700);
	Screen_Resizer display1({ 4000,7500 });
	Screen_Resizer display2({ 1100,700 }, ScreenStyle::Keep);
	Button b(display2);
	Slider slider(display2);
	List list(display2, TrajectoryImportFrame, trajectory_frame,15,items,30);
	Field field(display1);
	Menu menu(display2, b,slider,list);

	display1.SetStyle(ScreenStyle::Center);
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを自由に大きさ変えれるやつ

	while (System::Update())
	{
		const auto [left, right] = Screen_SplitFixedRight(Scene::Rect(), 1100);
		//left.draw(ColorF{ 0.0, 0.5, 1.0, 0.1 });
		right.draw(Palette::Whitesmoke);
		display1.Resize_Update(left);
		display2.Resize_Update(right);



		ClearPrint();
		Print << display2.Get_Pos();
		Print << Cursor::Pos();
		Print << right.pos.x;
		display1.toReal(RectF{ 0,0, 4000, 7500 }).draw(ColorF{ 0, 1.0, 0, 0.5 });
		//display2.toReal(RectF{ 0,0, 700, 1000 }).draw(ColorF{ 0.0, 0.5, 1.0, 0.5 });
		//
		//
		menu.MenuFrameDraw();
		menu.MenuUIDraw();

		if (slider.Slider_jadge(Feildpick, { 255,0,0 }, { 0,0,255 }))
			field.blue();
		else field.red();
	}
}
