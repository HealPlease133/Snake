#include "GameManager.h"
using namespace std;

int main()
{
    initscr();     // Curses 모드 시작
    start_color(); // 컬러 사용 선언

    GameManager *gameManager = GameManager::GetInstance();
    // GameManager의 Instance 불러오기

    while (!gameManager->isGameOver()) // 게임오버 될 때 까지 반복
    {
        gameManager->Update(); // Update호출 
        usleep(100000);        // 0.1초 대기
    }
    endwin();// Curses 모드 종료
    return 0;
}