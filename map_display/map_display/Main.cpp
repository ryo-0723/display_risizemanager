# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"Screen_Builder.h"
void Main()
{
	Screen_Resizer display({ 1200,1000 });
	Screen_build display1({200,1000}, display);
	display.SetStyle(ScreenStyle::Center);
	//Scene::SetResizeMode(ResizeMode::Keep);
	//シーンサイズ固定 今回はこれは使わずにやる
	Window::SetStyle(WindowStyle::Sizable);
	//ウィンドウを自由に大きさ変えれるやつ
	//Rect{座標ｘ,座標y,大きさx,大きさy}.draw

	while (System::Update())
	{
		display.Resize_Update();
		//Print<<Scene::DeltaTime();
		display.toReal(RectF{ 0,0, 1200, 1000 }).draw(Palette::Green);
		//RectF{0,0, 400,400 }.draw(Palette::Aqua);

		//display.toReal(Circle{ 1100,900,20 }).draw(Palette::Pink);
		//display.toReal(Circle{ 600,500,20 }).draw(Palette::Pink);
	}
}
