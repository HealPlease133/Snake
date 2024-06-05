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
}

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

    case GATE: // 게이트에 진입한 경우
        data->gate_count++;
        data->gateUse = true; // 뱀의 머리가 게이트 이용시 gateUse = true
        entranceGateX = snakePos.front().x; //입구 게이트의 X좌표 저장
        entranceGateY = snakePos.front().y; //입구 게이트의 Y좌표 저장
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (!(i == snakePos.front().y && j == snakePos.front().x) && data->map[i][j] == GATE)
                {
                    // 진입할 게이트의 위치 확인 및 진출 방향 설정
                    if (i == 0) // 상단 벽에 있는 경우
                        data->nowState = DOWN;
                    else if (i == HEIGHT - 1) // 하단 벽에 있는 경우
                        data->nowState = UP;
                    else if (j == 0) // 좌측 벽에 있는 경우
                        data->nowState = RIGHT;
                    else if (j == WIDTH - 1) // 우측 벽에 있는 경우
                        data->nowState = LEFT;

                    //진출할 게이트로 뱀의 머리를 이동
                    snakePos.front().y = i;
                    snakePos.front().x = j;
                    exitGateX = j;  //출구 게이트의 X좌표 저장
                    exitGateY = i;  //출구 게이트의 Y좌표 저장
                    //게이트로 이동했으므로 반복문 종료
                    i = HEIGHT;
                    break;
                }
            }
        }
        data->map[snakePos.back().y][snakePos.back().x] = EMPTY;
        snakePos.pop_back();
        break;

    default: // 그 외 구조물(벽, 뱀의 다른 부위, 고정 벽)과 충돌한 경우 : 게임 오버
        data->gameOver = true;
        return;
    }

    data->map[snakePos.front().y][snakePos.front().x] = SNAKE_HEAD;
    if (snakePos.back().x == exitGateX && snakePos.back().y == exitGateY)
    {
        data->gateUse = false; //뱀의 마지막 꼬리의 좌표가 게이트의 좌표랑 같을 시 gateUse = false
        data->map[entranceGateY][entranceGateX] = WALL; 
        data->map[exitGateY][exitGateX] = WALL; //게이트 사용 후 게이트를 벽으로 변경
    }
    if (not data->gateUse && data->map[exitGateY][exitGateX] != WALL)
        data->map[exitGateY][exitGateX] = WALL;

    data->current_snake_len = snakePos.size();
    if (data->max_snake_len < data->current_snake_len)
        data->max_snake_len = data->current_snake_len;
    return;
}
