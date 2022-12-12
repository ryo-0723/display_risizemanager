#pragma once
#include"ScreenStyle.h"
/*
開発開始　12月６日
開発者　藤本涼
OpenSiv3D用の画面の縮小拡大を自動的に行うもの
*/



class Screen_Resizer {
private:
	Vec2 Virtual_Size;
	Vec2 Offset_Pos = {};
	Vec2 Scalling = {};
	double Scall = 0;
	uint8 Style = 1;
public:
	Screen_Resizer(const Vec2& Virtual_Size) :Virtual_Size(Virtual_Size) {}
	/*仮想スクリーンの大きさを指定する*/

	void Resize_Update() {
		Scalling = Scene::Size() / Virtual_Size;
		//仮想ウィンドウと実ウィンドウの大きさの比率を求める
		Scall = Scalling.x < Scalling.y ? Scalling.x : Scalling.y;
		//x,yのうち、より縮小しなければ画面に入らないほうの縮小率を求める
		if (Style == 0) {
			Offset_Pos.x = 0;
			Offset_Pos.y = (Scene::Size().y - Virtual_Size.y * Scall) * 0.5;
		}
		else if (Style == 1) {
			Offset_Pos = (Scene::Size() - Virtual_Size * Scall) * 0.5;
		}
		else {
			Offset_Pos.x = (Scene::Size().x - Virtual_Size.x * Scall);
			Offset_Pos.y = (Scene::Size().y - Virtual_Size.y * Scall) * 0.5;
		}
		//pos*scallは実ウィンドウ内での仮想ウィンドウの大きさ
	}
	Vec2 GetWindow_Size() {
		return Scene::Size() * Scall;
	}
	void SetStyle(ScreenStyle Style) {
		this->Style = (uint8)Style;
	}
	/// @brief 実ウィンドウでの座標になるよう計算
	/// @param Pos 仮想ウィンドウでの座標
	Vec2  Cal_Pos(const Vec2& Pos) const {//左下からの座標にします！！←後回しかな
		return Pos * Scall + Offset_Pos;
	}
	/// @brief 実ウィンドウでの大きさになるように計算
	/// @param Size 仮想ウィンドウでの大きさ
	Vec2 Cal_Size(const Vec2& Size) const {
		return  Size * Scall;
	}
	/// @brief 実ウィンドウでの大きさになるように計算
	/// @param Size 仮想ウィンドウでの大きさ
	double Cal_Size(const double& Size)const {
		return Size * Scall;
	}

	Line toReal(const Line& Raw) const {
		return Line{ Cal_Pos(Raw.begin),Cal_Size(Raw.end) };
	}
	RectF toReal(const RectF& Raw) const {
		return RectF{ Cal_Pos(Raw.pos),Cal_Size(Raw.size) };
	}
	Circle toReal(const Circle& Raw) const {
		return Circle{ Cal_Pos(Raw.center),Cal_Size(Raw.r) };
	}
	Triangle toRael(const Triangle& Raw)const {
		return Triangle{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2) };
	}
	Bezier2 toReal(const Bezier2& Raw)const {
		return Bezier2{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2) };
	}
	Bezier3 toReal(const Bezier3& Raw)const {
		return Bezier3{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2),Cal_Pos(Raw.p3) };
	}
};
