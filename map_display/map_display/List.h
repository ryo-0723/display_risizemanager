#pragma once

#include"display_manager.h"

class List {
private:
	Screen_Resizer& resizer;
	RectF List_Frame;
	unsigned int List_Volume;
	double bar_size;
	Vec2  OneListSize = {0,0};
	Array<String> items;
	RoundRect Sidebutton_r[2];
	Triangle Sidebutton_t[2];
	double pos;

 public:

	List(Screen_Resizer& resizer,RectF List_Frame, unsigned int List_Volume,Array<String> items,double bar_size)
		:resizer(resizer),List_Frame(List_Frame),List_Volume(List_Volume),items(items),bar_size(bar_size) {
		OneListSize.y = List_Frame.h / List_Volume;
		Sidebutton_r[0] = { List_Frame.rightX() - bar_size,List_Frame.y,bar_size,bar_size,bar_size / 15 };
		Sidebutton_r[1] = { List_Frame.rightX() - bar_size,List_Frame.bottomY() - bar_size,bar_size,bar_size,bar_size / 10 };
		Sidebutton_t[0] = { Sidebutton_r[0].center(),bar_size/1.5 };
		Sidebutton_t[1] = { Sidebutton_r[1].center(),bar_size/1.5,180_deg };
		pos = OneListSize.y;
	}


	void draw() {
		for (int i = 0; i < 2;i++) {
			resizer.toReal(Sidebutton_r[i]).draw(Palette::Dimgray).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
			resizer.toReal(Sidebutton_t[i]).draw();
		}
		resizer.toReal(List_Frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		for (int i = 0; i < List_Volume;i++) {
			resizer.toReal(RectF{ List_Frame.x,pos,List_Frame.w - bar_size ,OneListSize.y })
				.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
			pos += OneListSize.y;
		}
		pos = List_Frame.y;
	}
	void Set_item() {


	}





};
