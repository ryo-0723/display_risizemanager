#pragma once

#include"display_manager.h"

class Slider {
private:
	Screen_Resizer& resizer;
	bool slider = false;//スライダーの現在の位置
public:

	Slider(Screen_Resizer& resizer) :resizer(resizer) {}


	/// @brief スライダーの判定を返す関数
	/// @param rect スライダー全体の四角
	/// @return 0=左,1=右
	bool Slider_jadge(RoundRect rect, Color left_color, Color right_color) {//スライダーっぽいスイッチ
		resizer.toReal(rect).drawFrame(resizer.Cal_Size(1), 0, Palette::Purple);//ボタンの外枠
		RoundRect _rect{ rect.rect.pos,rect.rect.size.x / 2.2,rect.rect.size.y,rect.r };

		if (resizer.toReal(_rect).mouseOver() && resizer.toReal(_rect).leftPressed())
			slider = 0;//左
		else if (resizer.toReal(_rect.movedBy({ rect.rect.size.x - _rect.rect.size.x,0 })).mouseOver()
			&& resizer.toReal(_rect.movedBy({ rect.rect.size.x - _rect.rect.size.x,0 })).leftPressed())
			slider = 1;//右
		if (not slider)
			resizer.toReal(_rect).draw(left_color);
		else
			resizer.toReal(_rect.movedBy({ rect.rect.size.x - _rect.rect.size.x,0 })).draw(right_color);

		return slider;
	}
};
