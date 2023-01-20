#pragma once


#include"display_manager.h"
#include"MenuConstant.h"
#include"Button.h"
#include"Slider.h"
#include"List.h"
#include"Meter.h"
# include <Siv3D.hpp>
class Menu {
private:
	Screen_Resizer& resizer;
	Button button;
	Slider slider;
	Meter Speedmeter;
	Meter Movetimer;
	List list;

public:
	Menu(Screen_Resizer& resizer)
		:resizer(resizer)
		, button(resizer, TCP_box, U"Connect to", U"Connected")
		, slider(resizer, Feildpick, Palette::Red, Palette::Blue)
		, list(resizer, TrajectoryImportFrame, trajectory_frame, 15, 30)
		, Speedmeter(resizer, SpeedMeter, U"m/s", { 0,30 })
		, Movetimer(resizer, MoveTimer, U"/s", { 0,10 }) {}

	const Font Feildpickfont{ 20 };
	const Font speed{ 50,Typeface::CJK_Regular_JP };
	const Font RobotPos{ 40 };
	const Texture Signal_max{ 0xf690_icon ,100 };
	const Texture Signal_good{ 0xf693_icon ,100 };
	const Texture Signal_fair{ 0xf692_icon ,100 };
	const Texture Signal_week{ 0xf691_icon ,100 };
	const Texture Signal_slash{ 0xf694_icon ,100 };

	void MenuFrameDraw() {
		resizer.toReal(Line{ 0,0,0,500 }).draw();
		resizer.toReal(Line{ 5,50,5,resizer.GetNowSize().y - 100 }).draw();
		//Print << resizer.GetNowSize();
		//メニュー画面の左側に線を書きたいけどあと回し
	}
	void Update() {
		slider.Update();
		button.Update();
	}
	void MenuUIDraw() {
		Speedmeter.draw(30);
		Movetimer.draw(0.97);
		robotposition_show(100, 200, 360);
		slider.draw();
		button.draw();
		mechanism_state();
		list.draw();

	}

	void robotposition_show(int x, int y, int yaw) {
		resizer.toReal(RobotPos_show1).draw(resizer.Cal_Size(0.5), Palette::Black);
		resizer.toReal(RobotPos_show2).draw(resizer.Cal_Size(0.5), Palette::Black);

		const auto f = [&](String&& str, double deltaY) {
			RobotPos(str).draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y + deltaY }), Palette::Black);
		};
		f(U"現在座標", 15);
		f(U"X:{}"_fmt(x), 70);
		f(U"Y:{}"_fmt(y), 130);
		f(U"θ:{}"_fmt(yaw), 190);
	}

	void mechanism_state() {
		resizer.toReal(mechanism_state_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);

	}

};
