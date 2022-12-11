# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"display_manager.h"
void Main()
{
	Screen_Resizer display({ 1200,1000 });
	display.SetStyle(ScreenStyle::Center);
	//Scene::SetResizeMode(ResizeMode::Keep);
	//シーンサイズ固定 今回はこれは使わずにやる
	Window::SetStyle(WindowStyle::Sizable);
	//ウィンドウを自由に大きさ変えれるやつ
	//Rect{座標ｘ,座標y,大きさx,大きさy}.draw

	while (System::Update())
	{
		display.Resize_Update();
		RectF{ display.Cal_Pos({0,0}), display.Cal_Size({1200,1000}) }.draw(Palette::Aqua);

		//display.toReal(RectF{ 0,0, 1200, 1000 }).draw(Palette::Green);
		//display.toReal(Circle{ 1100,900,20 }).draw(Palette::Pink);
		//display.toReal(Circle{ 600,500,20 }).draw(Palette::Pink);
	}
}
