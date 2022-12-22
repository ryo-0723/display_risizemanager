#pragma once


#include"display_manager.h"
#include"MenuConstant.h"
#include"Button.h"
#include"Slider.h"
# include <Siv3D.hpp>
class Menu {
private:
	Screen_Resizer& resizer;
	Button& button;
	Slider& slider;
public:
	Menu(Screen_Resizer& resizer, Button& button, Slider& slider)
		:resizer(resizer), button(button), slider(slider) {}
	const Font Feildpickfont{ 20 };
	const Font TCP{ 20 };
	const Font speed{ 50 };
	const Font speed_num{ 100,Typeface::CJK_Regular_JP };
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
		speedmeter();
		movetimer();
		robotposition_show();
		TCP_show();
		trajectory();
	}
	void speedmeter() {
		resizer.toReal(Speedmeter).drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), resizer.Cal_Size(0), Palette::Aqua);
		speed(U"m/s").drawBaseAt(resizer.Cal_Pos({ Speedmeter.center.x,Speedmeter.center.y + Speedmeter.r * 0.7 }), Palette::Limegreen);
		//speed_num(10.3).drawAt(resizer.Cal_Pos( Speedmeter.center), Palette::Limegreen);
		resizer.toReal(Speedneedle).rotatedAt(resizer.Cal_Pos({ 190, 900 }), 30_deg).draw(Palette::Aqua);
		speed_num(10.3).drawAt(resizer.Cal_Pos({ Speedmeter.center.x,Speedmeter.center.y + Speedmeter.r * -0.15 }), Palette::Limegreen);
	}
	void movetimer() {
		resizer.toReal(Movetimer).drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), resizer.Cal_Size(0), Palette::Aqua);
	}
	void robotposition_show() {
		resizer.toReal(RobotPos_show1).draw(resizer.Cal_Size(0.5), Palette::Black);
		resizer.toReal(RobotPos_show2).draw(resizer.Cal_Size(0.5), Palette::Black);
		RobotPos(U"現在座標").draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y + 50 }), Palette::Black);
		RobotPos(U"X:", 1020).draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y+130 }), Palette::Black);
		RobotPos(U"Y:", 1020).draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y + 200 }), Palette::Black);
		RobotPos(U"YAW:", 1020).draw(resizer.Cal_Pos({ RobotPos_show1.begin.x + 100,RobotPos_show1.end.y + 270 }), Palette::Black);
	}
	void TCP_show() {
		if (button.Rect_judge(TCP_box, TCP, U"Connect to", U"Connected", { 0,0,127 }, { 120,0,0 })) {
		}
	}
	void trajectory() {
		resizer.toReal(trajectory_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0),Palette::Black);
	}


};
