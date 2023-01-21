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
		, button(resizer, TCP_box, U"begin", U"end")
		, slider(resizer, Feildpick, Palette::Red, Palette::Blue)
		, list(resizer, TrajectoryImportFrame, trajectory_frame, 15, 30)
		, Speedmeter(resizer, SpeedMeter, U"m/s", { 0,30 })
		, Movetimer(resizer, MoveTimer, U"/s", { 0,10 }) {}

	const Font RobotPos{ 25 };
	const Font Machine_Font{ 20 };
	const Texture Signal_max{ 0xf08fa_icon ,100 };
	const Texture Signal_good{ 0xf08f8_icon ,100 };
	const Texture Signal_fair{ 0xf08f6_icon ,100 };
	const Texture Signal_week{ 0xf08f4_icon ,100 };
	const Texture Signal_slash{ 0xf08fc_icon ,100 };
	bool status[5] = { false,true,false,true,true };

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
		mechanism_state(4000, 45, status);
		TCP_status(0);
		list.InportFramedraw();
		list.List_draw();
	}
	bool slider_jadge() {
		return slider.Slider_jadge();
	}

	void TCP_status(int status) {
		switch (status) {
		case 0:
			Signal_slash
				.resized(resizer.Cal_Size(30))
				.draw(resizer.Cal_Pos({ 900, 50 }), Palette::Black);
			break;
		case 1:
			Signal_week
				.resized(resizer.Cal_Size(30))
				.draw(resizer.Cal_Pos({ 900, 50 }), Palette::Black);
			break;
		case 2:
			Signal_fair
				.resized(resizer.Cal_Size(30))
				.draw(resizer.Cal_Pos({ 900, 50 }), Palette::Black);
			break;
		case 3:
			Signal_good
				.resized(resizer.Cal_Size(30))
				.draw(resizer.Cal_Pos({ 900, 50 }), Palette::Black);
			break;
		case 4:
			Signal_max
				.resized(resizer.Cal_Size(30))
				.draw(resizer.Cal_Pos({ 900, 50 }), Palette::Black);
			break;
		}

	}

	void robotposition_show(int x, int y, int yaw) {
		resizer.toReal(RobotPos_showFrame).drawFrame(resizer.Cal_Size(1), 0, Palette::Black);
		const auto f = [&](String&& str, double deltaY) {
			RobotPos(str).draw(resizer.Cal_Pos({ RobotPos_showFrame.x + 40,RobotPos_showFrame.y + deltaY }), Palette::Black);
		};
		f(U"Position", 15);
		f(U"X:{}"_fmt(x), 70);
		f(U"Y:{}"_fmt(y), 110);
		f(U"θ:{}"_fmt(yaw), 150);
	}

	void mechanism_state(int rpm, int angle, bool status[5]) {
		resizer.toReal(mechanism_state_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		Machine_Font(U"ペットボトル発射機構")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 2,mechanism_state_frame.topY() }), Palette::Black);
		Machine_Font(U"回転数 : ", rpm, U"rpm")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() }), Palette::Black);
		Machine_Font(U"角度　: ", angle, U"°")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 2 }), Palette::Black);

		Machine_Font(U"ハット発射機構")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 2 ,mechanism_state_frame.topY() + Machine_Font.height() * 4 }), Palette::Black);
		Machine_Font(U"発射準備  : ", status[0])
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 5 }), Palette::Black);

		Machine_Font(U"ペットボトル装填機構")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 2 ,mechanism_state_frame.topY() + Machine_Font.height() * 7 }), Palette::Black);
		Machine_Font(U"装填準備  : ", status[1])
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 8 }), Palette::Black);

		Machine_Font(U"ハット装填機構")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 2 ,mechanism_state_frame.topY() + Machine_Font.height() * 10 }), Palette::Black);
		Machine_Font(U"装填準備  : ", status[2])
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 11 }), Palette::Black);

		Machine_Font(U"回収機構")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 2 ,mechanism_state_frame.topY() + Machine_Font.height() * 13 }), Palette::Black);
		Machine_Font(U"奥側回収準備  : ", status[3])
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 14 }), Palette::Black);
		Machine_Font(U"棚、倉庫回収準備  : ", status[4])
			.draw(resizer.Cal_Pos({ mechanism_state_frame.leftX() + Machine_Font.spaceWidth() * 15,mechanism_state_frame.topY() + Machine_Font.height() * 15 }), Palette::Black);
	}

};
