#pragma once

#include <Siv3D.hpp>



constexpr RectF box{ 60,230,90,25 };
constexpr RoundRect TCP_box{960,30,110,60,10};
constexpr RectF Wifi_box{ 60,120,120,80 };
constexpr RoundRect Feildpick{ 50,20,90,25,2 };
constexpr Circle SpeedMeter{190,900,140};
constexpr Circle MoveTimer{ 520,900,140 };
//constexpr Triangle Speedneedle{190,900,100 };
constexpr Triangle Speedneedle{ {184,900},{190,775},{196,900} };
constexpr Line RobotPos_show1{700,1060,700,780};//枠の左の線
constexpr Line RobotPos_show2{ 700,780,1100,780 };
constexpr RoundRect TrajectoryImportFrame{ 20,87,570,27,2 };
constexpr RectF trajectory_frame{ 20,130,660,610 };
constexpr RectF mechanism_state_frame{ 685,130,400,630 };
