#include "WindowManager.h"
WindowManager::WindowManager(GameData *_data)
{
    data = _data;
    init_pair(EMPTY, COLOR_WHITE, COLOR_WHITE);
    init_pair(WALL, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(IMMUNE_WALL, COLOR_BLACK, COLOR_BLACK);
    init_pair(SNAKE_HEAD, COLOR_CYAN, COLOR_CYAN);
    init_pair(SNAKE_BODY, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(GROWTH_ITEM, COLOR_GREEN, COLOR_GREEN);
    init_pair(POISON_ITEM, COLOR_RED, COLOR_RED);
    init_pair(GATE,COLOR_BLUE, COLOR_BLUE); 
    // 각 오브젝트 별로 색깔 설정

} // 생성자의 구현부

void WindowManager::Update()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            attron(COLOR_PAIR(data->map[i][j]));  // 해당 위치에 있는 오브젝트에 맞는 색상의 Attribute 사용
            mvprintw(i, j * 2, "  ");             // 화면에 출력
            attroff(COLOR_PAIR(data->map[i][j])); // Attribute 사용 해제
        }
    }
    const std::string temp = "Time : " + std::to_string(data->nowTime);
    const std::string temp2 = "B : " + std::to_string(float(data->current_snake_len)/data->max_snake_len);
    const std::string temp3 = "+ : " + std::to_string(data->growth_item_count);
    const std::string temp4 = "- : " + std::to_string(data->poison_item_count);
    const std::string temp5 = "G : " + std::to_string(data->gate_count);
    const std::string temp6 = "[+] : " + std::to_string(data->growth_item_target);
    const std::string temp7 = "[-] : " + std::to_string(data->poison_item_target);
    const std::string temp8 = "[G] : " + std::to_string(data->gate_target);
    mvprintw(HEIGHT + 1, 1, const_cast<char *>(temp.c_str())); // 현재 시간을 밑쪽에 표시
    mvprintw(HEIGHT + 2, 1, const_cast<char *>(temp2.c_str()));
    mvprintw(HEIGHT + 3, 1, const_cast<char *>(temp3.c_str()));
    mvprintw(HEIGHT + 4, 1, const_cast<char *>(temp4.c_str()));
    mvprintw(HEIGHT + 5, 1, const_cast<char *>(temp5.c_str()));
    mvprintw(HEIGHT + 3, 10, const_cast<char *>(temp6.c_str()));
    mvprintw(HEIGHT + 4, 10, const_cast<char *>(temp7.c_str()));
    mvprintw(HEIGHT + 5, 10, const_cast<char *>(temp8.c_str()));
    refresh(); // 실제 스크린에 출력

} // Update 함수의 구현부