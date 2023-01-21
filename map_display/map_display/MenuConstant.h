#pragma once

#include <Siv3D.hpp>



constexpr RectF box{ 60,240,90,25 };
constexpr RoundRect TCP_box{960,40,110,45,10};
constexpr RectF Wifi_box{ 60,120,120,80 };
constexpr RoundRect Feildpick{ 50,20,110,30,2 };
constexpr Circle SpeedMeter{190,920,140};
constexpr Circle MoveTimer{ 520,920,140 };
//constexpr Triangle Speedneedle{190,900,100 };
constexpr Triangle Speedneedle{ {184,900},{190,775},{196,900} };
constexpr RectF RobotPos_showFrame{ 775,590,300,200 };
constexpr RoundRect TrajectoryImportFrame{ 20,70,570,27,2 };
constexpr RectF trajectory_frame{ 20,100,740,660 };
constexpr RectF mechanism_state_frame{ 775,100,300,480 };
