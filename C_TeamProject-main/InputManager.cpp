#include "InputManager.h"

InputManager::InputManager(GameData *_data)
{
    data = _data;
} // 생성자의 구현부

void InputManager::Update()
{
    timeout(100);      // 입력에 타임아웃 적용
    noecho();          // 입력값이 보이지 않도록 설정
    char ch = getch(); // 문자 입력받기

    if ('a' <= ch && ch <= 'z')
        ch = ch - 'a' + 'A'; // 입력받은 문자 대문자로 변환

    if (ch == upKey)
        data->nowState = UP;
    else if (ch == leftKey)
        data->nowState = LEFT;
    else if (ch == downKey)
        data->nowState = DOWN;
    else if (ch == rightKey)
        data->nowState = RIGHT;
    // 입력에 따라 뱀이 바라보는 방향 변경
} // Update 함수의 구현부