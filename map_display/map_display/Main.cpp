# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include"display_manager.h"
void Main()
{

	screen_resizer display(1200,1000);
	double scalling_x,scalling_y;
	double scall;
	//Scene::SetResizeMode(ResizeMode::Keep);
	//シーンサイズ固定 今回はこれは使わずにやる
	Window::SetStyle(WindowStyle::Sizable);
	//ウィンドウを自由に大きさ変えれるやつ
	//Rect{座標ｘ,座標y,大きさx,大きさy}.draw

	while (System::Update())
	{
		display.resizer();
		//Rect{300,300, 200,300 }.draw();
		scalling_x = Scene::Size().x / 1200.0;
		scalling_y= Scene::Size().y / 1000.0;
		scall=scalling_x < scalling_y ? scalling_x : scalling_y;


		//RectF{display.pointer().x,0,100,100}.draw();
		RectF{ display.pointer().x,display.pointer().y, 1200.0 * scall,1000.0 * scall}.draw(Palette::Aqua);
		ClearPrint();
		Print << Scene::Size().x;
		Print << Scene::Size().y;
		Print << Scene::Height();
		Print << Scene::Width();
		Print << 1200 * scall;
	}
}
