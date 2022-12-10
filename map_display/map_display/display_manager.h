#pragma once
/*
開発開始　12月６日
開発者　藤本涼
opensiv用の画面の縮小拡大を自動的に行うもの
*/



class screen_resizer {
private:
	int x=0,y=0;
	Vec2 pos;
	Vec2 point;
	Vec2 Op;
	Vec2 scalling;
	double scall;
public:
	screen_resizer(double x,double y ) {
		pos.x = x;
		pos.y = y;

	}
	/*仮想スクリーンの大きさを指定する*/


	void resizer() {
		scalling.x = Scene::Size().x / pos.x;
		scalling.y = Scene::Size().y / pos.y;
		scall = scalling.x < scalling.y ? scalling.x : scalling.y;

		Op.x = (Scene::Size().x - 1200.0 * scall) * 0.5;
		Op.y = (Scene::Size().y - pos.y * scall) * 0.5;
	}

	Vec2  pointer(Vec2& p) {//左下からの座標にします！！
		point.x = p.x+Op.x;
		point.y = p.y+Op.y;
		return point;
	}


};
