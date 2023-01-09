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
	Button& button;
	Slider& slider;
	List& list;
	Meter& meter;
public:
	Menu(Screen_Resizer& resizer, Button& button, Slider& slider,List& list,Meter& meter)
		:resizer(resizer), button(button), slider(slider),list(list),meter(meter) {}
	const Font Feildpickfont{ 20 };
	const Font TCP{ 20 };
	const Font speed{ 50,Typeface::CJK_Regular_JP };
	
	const Font RobotPos{ 40 };
	void MenuFrameDraw() {
		resizer.toReal(Line{ 0,0,0,500 }).draw();
		resizer.toReal(Line{ 5,50,5,resizer.GetNowSize().y - 100 }).draw();
		Print << resizer.GetNowSize();
		//メニュー画面の左側に線を書きたいけどあと回し
	}
	void MenuUIDraw() {

		//resizer.toReal(box).draw();

		//resizer.toReal(Feildpick).draw(Palette::Darkgrey);
		//Feildpickfont(U"red").drawAt(resizer.Cal_Pos(Feildpick.leftCenter()), Palette::Red);
		//Feildpickfont(U"blue").drawAt(resizer.Cal_Pos(Feildpick.rightCenter()), Palette::Aqua);
		meter.draw(20.9);
		movetimer();
		robotposition_show();
		TCP_show();
		trajectory();
		mechanism_state();
	}

	void movetimer() {
		resizer.toReal(Movetimer).drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), resizer.Cal_Size(0), Palette::Aqua);
	}
	void robotposition_show() {
		resizer.toReal(RobotPos_show1).draw(resizer.Cal_Size(0.5), Palette::Black);
		resizer.toReal(RobotPos_show2).draw(resizer.Cal_Size(0.5), Palette::Black);

		const auto f = [&](String&& str, double deltaY) {
			RobotPos(str).draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y + deltaY }), Palette::Black);
		};
		f(U"現在座標",        15);
		f(U"X:{}"_fmt(123),   70);
		f(U"Y:{}"_fmt(123),   130);
		f(U"θ:{}"_fmt(1000), 190);

	}
	void TCP_show() {
		if (button.Rect_judge(TCP_box, TCP, U"Connect to", U"Connected", { 0,0,127 }, { 120,0,0 })) {
		}
	}
	void trajectory() {
		//resizer.toReal(trajectory_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0),Palette::Black);
		list.draw();
	}
	void mechanism_state() {
		resizer.toReal(mechanism_state_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);

	}

};
