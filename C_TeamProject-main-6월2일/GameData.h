#pragma once
const int WIDTH = 21;
const int HEIGHT = 21;
// 가로, 세로 크기

enum State
{
    STOP, // 정지 상태
    UP,   // 위
    LEFT, // 왼쪽
    DOWN, // 아래
    RIGHT // 오른쪽
}; // 뱀의 현재 상태를 나타내는 열거형

enum ObjectType
{
    EMPTY = 1,   // 빈 공간
    WALL,        // 벽
    IMMUNE_WALL, // 고정 벽
    SNAKE_HEAD,  // 뱀의 머리
    SNAKE_BODY,  // 뱀의 꼬리
    GROWTH_ITEM, // 성장 아이템
    POISON_ITEM,  // 독 아이템
    GATE        // 포탈
}; // 맵의 특정 위치의 상태를 나타내는 열거형

struct GameData
{
public:
    ObjectType map[HEIGHT][WIDTH]; // 구조물이 담긴 2차원 배열
    State nowState;                // 현재 스네이크의 상태
    bool gameOver = false;         // 게임 오버 여부
    int nowTime = 0;               // Update가 호출된 횟수
    int growth_item_count = 0;
    int poison_item_count = 0;
    int gate_count = 0;
    int max_snake_len = 0;
    int current_snake_len = 0;
}; // 게임의 현재 진행사항을 나타내는 구조체

typedef struct _pos
{
    int y = 0;
    int x = 0;
} pos; // x,y좌표 표현을 위한 구조체

class LoopBehavior
{
public:
    virtual void Update() = 0;
}; // Loop 인터페이스 (해당 클래스를 상속받은 클래스는 Update를 호출 가능해야 함)