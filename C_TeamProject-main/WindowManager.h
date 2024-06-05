#pragma once
#include "GameData.h"
#include <string>
#include <ncurses.h>

class WindowManager : public LoopBehavior
{
private:
    GameData *data; // 데이터

public:
    WindowManager(GameData *_data); // 생성자를 통해 색상값 초기화
    void Update() override;         // 현재 map 상태에 따라 화면을 그리는 함수
};
