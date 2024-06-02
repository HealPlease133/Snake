#pragma once
#include <deque>
#include "GameData.h"

class Snake : public LoopBehavior
{
private:
    GameData *data;           // 데이터
    std::deque<pos> snakePos; // 뱀에 해당하는 좌표들을 덱 자료구조에 저장
    const int dy[5] = {0, -1, 0, 1, 0};
    const int dx[5] = {0, 0, -1, 0, 1}; // 상태별로 이동 방향을 나타내는 상대 좌표(정지,위,왼쪽,아래,오른쪽 순서)

public:
    Snake(GameData *data);  // 생성자를 통해 맵 중앙에 길이 3의 뱀 생성
    void Update() override; // 지렁이가 방향에 따라 한 칸 이동
};