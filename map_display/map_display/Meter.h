#pragma once


#include"display_manager.h"

class Meter {
private:
	Screen_Resizer& resizer;
	Circle  MeterCircle;
	const Font Value_Font{ 100,Resource(U"engine/font/DSEG7ModernMini-Bold.ttf") };
	const Font Unit_Font{ 50,Typeface::CJK_Regular_JP };
	Triangle Needle;
	String Unit_string;
public:

	Meter(Screen_Resizer& resizer,Circle  MeterCircle,String Unit_string,Vec2 )
		:resizer(resizer), MeterCircle(MeterCircle),Unit_string(Unit_string)
	{
		Needle = { MeterCircle.center
			,{0,0}
		,MeterCircle.center };
	}

		void draw(double Value) {
		resizer.toReal(MeterCircle)
			.drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), resizer.Cal_Size(0), Palette::Black);
		resizer.toReal(Needle).rotatedAt(resizer.Cal_Pos({ 190, 900 }), 30_deg)
			.draw(Palette::Red).drawFrame(resizer.Cal_Size(1), 0, Palette::Darkgrey);
		Unit_Font(Unit_string)
			.drawBaseAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * 0.7 }), Palette::Limegreen);
		Value_Font(Value)
			.drawAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * -0.15 }), Palette::Blue);
		}

		void Set_Unit_sting(String Unit_string ) {
			this->Unit_string = Unit_string;
		}

};
