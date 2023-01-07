#pragma once

#include"display_manager.h"

class List {
private:
	Screen_Resizer& resizer;
	RectF List_Frame;
	unsigned int List_Volume;
	double bar_size;
	Vec2  OneListSize = { 0,0 };
	Array<String> items;
	Vec2 Sidebutton[2];
	double pos;
	Optional<FilePath> path;
	const Texture Arrow_up{ 0xf151_icon, 100 };
	const Texture Arrow_down{ 0xf150_icon, 100 };
	const Texture Download{ 0xf07c_icon,100 };
	RoundRect ListImportFrame;
	RoundRect ListImportButton{ ListImportFrame.rightCenter().x
		,ListImportFrame.y
		,ListImportFrame.h,ListImportFrame.h,3 };
	CSV csv;
	const Font List_Font{ 20 };
	 String windowTitle;
public:
	/// @brief List.hのコンストラクタ
	/// @param resizer 表示画面
	/// @param ListImportFrame ファイル選択用の場所
	/// @param List_Frame リストの表示場所
	/// @param List_Volume 一度に表示するデータの数
	/// @param items 表示するリストファイルデータ
	/// @param bar_size 横のサイドバーの幅
	List(Screen_Resizer& resizer, RoundRect ListImportFrame, RectF List_Frame, unsigned int List_Volume, Array<String> items, double bar_size)
		:resizer(resizer),ListImportFrame(ListImportFrame), List_Frame(List_Frame), List_Volume(List_Volume), items(items), bar_size(bar_size) {
		OneListSize.y = List_Frame.h / List_Volume;
		Sidebutton[0] = { List_Frame.rightX() - bar_size,List_Frame.y };
		Sidebutton[1] = { List_Frame.rightX() - bar_size,List_Frame.bottomY() - bar_size };
		pos = OneListSize.y;
	}


	void draw() {
		/*ファイル指定欄*/
		resizer.toReal(ListImportFrame)
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		resizer.toReal(ListImportButton)
			.draw(resizer.toReal(ListImportButton).mouseOver() ? Color{ 0,255,255,50 } : Palette::White)
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		Download.resized(resizer.Cal_Size(ListImportButton.h * 0.8))
			.drawAt(resizer.Cal_Pos(ListImportButton.center()), Palette::Black);
		if (path.has_value()) 
		Print<<FileSystem::FileName(*path);
		if (resizer.toReal(ListImportButton).leftClicked()) {
			path = Dialog::OpenFile({ FileFilter::CSV() });
			//const CSV csv{ U"C:/Users/jlgif/Downloads/robot_move_ver0.0.csv"};
			if (path.has_value()) {
				csv.load(*path);
				if (not csv) // もし読み込みに失敗したら
					throw Error{ U"Failed to load" };
			}
		}

		/*リスト*/
		Arrow_up.resized(resizer.Cal_Size(bar_size)).draw(resizer.Cal_Pos({ Sidebutton[0].x, Sidebutton[0].y }), Palette::Black);
		Arrow_down.resized(resizer.Cal_Size(bar_size)).draw(resizer.Cal_Pos({ Sidebutton[1].x, Sidebutton[1].y }), Palette::Black);

		resizer.toReal(RoundRect{ List_Frame.pos, List_Frame.size.x - bar_size,List_Frame.size.y,3 })
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		for (int i = 0; i < List_Volume; i++) {
			resizer.toReal(RectF{ List_Frame.x,pos,List_Frame.w - bar_size ,OneListSize.y });
			if(not csv.isEmpty())
			 windowTitle = csv[1][0];

			List_Font(windowTitle).draw(resizer.Cal_Pos({ List_Frame.x, pos }),Palette::Black);
			//.drawFrame(resizer.Cal_Size(0.5), resizer.Cal_Size(0), Palette::Black);
			pos += OneListSize.y;
		}
		pos = List_Frame.y;


	}
};
