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
	Vec2 range;
	double angle;
public:

	Meter(Screen_Resizer& resizer,Circle  MeterCircle,String Unit_string,Vec2 range)
		:resizer(resizer), MeterCircle(MeterCircle),Unit_string(Unit_string),range(range)
	{
		Needle = { {MeterCircle.center.x - MeterCircle.r/35,MeterCircle.center.y}
				,{MeterCircle.center.x,MeterCircle.center.y - MeterCircle.r*0.9}
				,{MeterCircle.center.x+ MeterCircle.r / 35,MeterCircle.center.y }
			};
	}

		void draw(double Value) {
		resizer.toReal(MeterCircle)
			.drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), 0, Palette::Black);
		/*-130 130*/
		//(x - in_min)* (out_max - out_min) / (in_max - in_min) + out_min;
		angle=(Value - range.x)* (130 +130) / (range.y - range.x) -130;
		resizer.toReal(Needle).rotatedAt(resizer.Cal_Pos(MeterCircle.center),ToRadians(angle))
			.draw(Palette::Red).drawFrame(resizer.Cal_Size(1), 0, Palette::Darkgrey);
		resizer.toReal(Circle{MeterCircle.center,MeterCircle.r / 45 })
			.draw(Palette::Red);
		Unit_Font(Unit_string)
			.drawBaseAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * 0.7 }), Palette::Limegreen);
		Value_Font(Value)
			.drawAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * -0.15 }), Palette::Blue);
		}

		void Set_Unit_sting(String Unit_string ) {
			this->Unit_string = Unit_string;
		}

};
