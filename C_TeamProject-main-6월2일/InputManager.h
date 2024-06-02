#pragma once
#include "GameData.h"
#include <ncurses.h>
#include <unistd.h>

class InputManager : public LoopBehavior
{
private:
    GameData *data; // 데이터
    char upKey = 'W';
    char leftKey = 'A';
    char downKey = 'S';
    char rightKey = 'D'; // 이동 키 할당
public:
    InputManager(GameData *); // 생성자
    void Update() override;   // 방향키를 입력받아 플레이어 상태를 변경하는 함수
};