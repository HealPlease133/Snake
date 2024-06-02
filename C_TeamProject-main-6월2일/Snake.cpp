#include "Snake.h"
Snake::Snake(GameData *_data)
{
    data = _data;
    data->map[HEIGHT / 2][WIDTH / 2] = SNAKE_HEAD;     // 맵의 중앙에 뱀 머리 생성
    data->map[HEIGHT / 2][WIDTH / 2 - 1] = SNAKE_BODY; // 그 옆에 뱀 몸통 생성
    data->map[HEIGHT / 2][WIDTH / 2 - 2] = SNAKE_BODY; // 그 옆에 뱀 몸통 생성
    snakePos.push_front({HEIGHT / 2, WIDTH / 2 - 2});  // 뱀 몸통을 snakePos에 추가
    snakePos.push_front({HEIGHT / 2, WIDTH / 2 - 1});  // 뱀 몸통을 snakePos에 추가
    snakePos.push_front({HEIGHT / 2, WIDTH / 2});      // 뱀 머리를 snakePos에 추가
} // 생성자의 구현부

void Snake::Update()
{
    if (snakePos.size() < 3)
    {
        data->gameOver = true;
        return;
    } // 길이가 3보다 작으면 게임 오버

    if (data->nowState == STOP)
        return; // 정지 상태인 경우 바로 리턴

    int _y = snakePos.front().y + dy[data->nowState];
    int _x = snakePos.front().x + dx[data->nowState]; // 이동할 다음 좌표

    data->map[snakePos.front().y][snakePos.front().x] = SNAKE_BODY;
    snakePos.push_front({_y, _x}); // 머리 이동

    switch (data->map[_y][_x])
    {
    case EMPTY: // 빈공간으로 이동한 경우 : 꼬리부분 1개 삭제
        data->map[snakePos.back().y][snakePos.back().x] = EMPTY;
        snakePos.pop_back();
        break;

    case POISON_ITEM: // 독 아이템을 먹은 경우 : 꼬리부분 2개 삭제
        data->poison_item_count++;
        data->map[snakePos.back().y][snakePos.back().x] = EMPTY;
        snakePos.pop_back();
        data->map[snakePos.back().y][snakePos.back().x] = EMPTY;
        snakePos.pop_back();
        break;

    case GROWTH_ITEM: // 성장 아이템을 먹은 경우 : 꼬리부분 그대로
        data->growth_item_count++;
        break;

    case GATE: //게이트 들어간 경우
        data->gate_count++;
        for (int i = 0; i<HEIGHT; i++)
            for (int j = 0; j<WIDTH; j++)
                if (!(i==snakePos.front().y && j==snakePos.front().x) && data->map[i][j] == GATE)
                {
                    break;
                }
        break;


    default: // 그 외 구조물(벽, 뱀의 다른 부위, 고정 벽)과 충돌한 경우 : 게임 오버
        data->gameOver = true;
        return;
    }
    data->current_snake_len = snakePos.size();
    if (data->max_snake_len < data->current_snake_len) data->max_snake_len = data->current_snake_len;
    data->map[_y][_x] = SNAKE_HEAD;
    return;
} // Update 함수의 구현부