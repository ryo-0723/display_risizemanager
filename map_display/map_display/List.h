#pragma once

#include"display_manager.h"
#define Item_value 10

class List {
private:
	Screen_Resizer& resizer;
	RectF List_Frame;
	RectF Drawing_Frame;
	RoundRect ListImportFrame;
	RoundRect ListImportButton{ ListImportFrame.rightCenter().x
		,ListImportFrame.y
		,ListImportFrame.h,ListImportFrame.h,3 };

	unsigned int List_Volume;
	double bar_size;
	Vec2  OneListSize = { 0,0 };
	Vec2 Sidebutton[2];
	Vec2 pos;
	Optional<FilePath> File_path;
	const Texture Arrow_up{ 0xf151_icon, 100 };
	const Texture Arrow_down{ 0xf150_icon, 100 };
	const Texture Download{ 0xf07c_icon,100 };
	const Font List_Font{ 17 };
	const Font Item_string_Font{ 15 };

	CSV csv;

	String windowTitle;
	String List_item_string[Item_value] = {
		U"Value",U"Type",U"開始座標x",U"開始座標y",U"終点座標x"
		,U"終点座標y",U"開始速度",U"終点速度",U"加速度",U"円の半径"
	};
public:
	/// @brief List.hのコンストラクタ
	/// @param resizer 表示画面
	/// @param ListImportFrame ファイル選択用の場所
	/// @param List_Frame リストの表示場所
	/// @param List_Volume 一度に表示するデータの数
	/// @param items 表示するリストファイルデータ
	/// @param bar_size 横のサイドバーの幅
	List(Screen_Resizer& resizer, RoundRect ListImportFrame, RectF List_Frame, unsigned int List_Volume, double bar_size)
		:resizer(resizer), ListImportFrame(ListImportFrame), List_Frame(List_Frame), List_Volume(List_Volume), bar_size(bar_size) {
		OneListSize.y = List_Frame.h / List_Volume;
		OneListSize.x = (List_Frame.w - bar_size) / Item_value;
		Sidebutton[0] = { List_Frame.rightX() - bar_size,List_Frame.y };
		Sidebutton[1] = { List_Frame.rightX() - bar_size,List_Frame.bottomY() - bar_size };
		pos.y = OneListSize.y;
		pos.x = OneListSize.x;
		Drawing_Frame = { List_Frame.pos,OneListSize };
	}


	void InportFramedraw() {
		/*ファイル指定欄*/
		resizer.toReal(ListImportFrame)
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		resizer.toReal(ListImportButton)
			.draw(resizer.toReal(ListImportButton).mouseOver() ? Color{ 0,255,255,50 } : Palette::White)
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		Download.resized(resizer.Cal_Size(ListImportButton.h * 0.8))
			.drawAt(resizer.Cal_Pos(ListImportButton.center()), Palette::Black);

		if (File_path) {
			List_Font(FileSystem::FileName(*File_path))
				.drawAt(resizer.Cal_Pos({ ListImportFrame.center() }), Palette::Black);
		}
		if (resizer.toReal(ListImportButton).leftClicked()) {
			const auto temp = File_path;
			File_path = Dialog::OpenFile({ FileFilter::CSV() });
			//const CSV csv{ U"C:/Users/jlgif/Downloads/robot_move_ver0.0.csv"};
			if (File_path) {
				csv.load(*File_path);
				if (not csv) // もし読み込みに失敗したら
					throw Error{ U"Failed to load" };
			}
			else {
				File_path = temp;
			}
		}
	}

	void List_draw() {

		/*枠の描画*/
		Arrow_up.resized(resizer.Cal_Size(bar_size)).draw(resizer.Cal_Pos({ Sidebutton[0].x, Sidebutton[0].y }), Palette::Black);
		Arrow_down.resized(resizer.Cal_Size(bar_size)).draw(resizer.Cal_Pos({ Sidebutton[1].x, Sidebutton[1].y }), Palette::Black);

		resizer.toReal(RoundRect{ List_Frame.pos, List_Frame.size.x - bar_size,List_Frame.size.y,3 })
			.drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);

		/*リストの項目と縦線の表示*/
		for (int i = 0; i < Item_value; i++) {
			Drawing_Frame = { pos.x,List_Frame.y,OneListSize };
			Item_string_Font(List_item_string[i])
				.drawAt(resizer.Cal_Pos(Drawing_Frame.center()), Palette::Black);
			if (pos.x != List_Frame.x) {
				resizer.toReal(Line{ pos.x,List_Frame.topY(),pos.x,List_Frame.bottomY() })
					.draw(resizer.Cal_Size(0.5), Palette::Black);
			}
			pos.x += OneListSize.x;
		}
		pos.x = List_Frame.pos.x;
		/**/

		for (int i = 0; i < (List_Volume < csv.rows() ? List_Volume : csv.rows()); i++) {
			resizer.toReal(RectF{ List_Frame.x,pos.y,List_Frame.w - bar_size ,OneListSize.y });
			if (not csv.isEmpty())
				for (int a = 0; a < csv.columns(4); a++) {
					windowTitle = csv[i][a];
					Drawing_Frame = { pos,OneListSize };
					List_Font(windowTitle).drawAt(resizer.Cal_Pos(Drawing_Frame.center()), Palette::Black);
					pos.x += OneListSize.x;
				}
			pos.x = List_Frame.x;
			pos.y += OneListSize.y;
		}
		pos.y = List_Frame.y + OneListSize.y;




	}
};
