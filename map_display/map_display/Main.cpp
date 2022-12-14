# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"display_manager.h"
SIV3D_SET(EngineOption::Renderer::OpenGL);

std::pair<RectF, RectF> Screen_SplitFixedRight(const RectF& raw, double px) {
	return std::make_pair(
		RectF{ 0,0,raw.w - px,raw.h },
		RectF{ raw.w-px,0,px,raw.h }
	);
}

void Main()
{
	Window::SetMinimumFrameBufferSize({ 800, 600 });
	Window::Resize(1000, 1000);
	Screen_Resizer display1({ 8000,7500 });
	Screen_Resizer display2({ 700,500 }, ScreenStyle::Keep);
	display1.SetStyle(ScreenStyle::Center);
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを自由に大きさ変えれるやつ

	while (System::Update())
	{
		const auto [left, right] = Screen_SplitFixedRight(Scene::Rect(), 600);
		left.draw(ColorF{ 0.0, 0.5, 1.0, 0.2 });
		right.draw(ColorF{ 1.0, 0, 0, 0.2 });

		display1.Resize_Update(left);
		display2.Resize_Update(right);
		ClearPrint();
		Print << display2.Get_Pos();
		Print << Cursor::Pos();
		Print << right.pos.x;
		//Print<<Scene::DeltaTime();
		display1.toReal(RectF{ 0,0, 8000, 7500 }).draw(Palette::Green);
		//display2.toReal(RectF{ 0,0, 700, 1000 }).draw(ColorF{ 0.0, 0.5, 1.0, 0.5 });

		//RectF{0,0, 400,400 }.draw(Palette::Aqua);

		display1.toReal(Circle{ 8000,7500,100 }).draw(Palette::Pink);
		display2.toReal(Circle{ 350,250,80 }).draw(Palette::Pink);
		display1.toReal(Circle{ 4000,3750,100 }).draw(Palette::Pink);
		display2.toReal(Circle{ 700,500,20 }).draw(Palette::Pink);
		display2.toReal(Circle{ 0,0,20 }).draw(Palette::Pink);

	}
}
