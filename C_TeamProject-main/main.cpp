#include "GameManager.h"
#include "StartScreen.h"
#include "GameOverScreen.h"
using namespace std;

int main()
{
    initscr();     // Curses 모드 시작
    start_color(); // 컬러 사용 선언
    cbreak();      // Line buffering 비활성화
    noecho();      // 입력한 문자 화면에 표시하지 않음
    curs_set(0);   // 커서 숨김

    while (true)
    {
        char choice = showStartScreen();
        if (choice == 'e') {
            endwin(); // Curses 모드 종료
            return 0; // 프로그램 종료
        }

        clear(); // 화면 초기화
        refresh(); // 화면 갱신

        GameManager *gameManager = GameManager::GetInstance();
        // GameManager의 Instance 불러오기

        while (!gameManager->isGameOver()) // 게임오버 될 때까지 반복
        {
            gameManager->Update(); // Update 호출 
            usleep(100000);        // 0.1초 대기
        }

        char gameOverOption = showGameOverScreen();
        if (gameOverOption == 'e') // 'E'를 누르면 종료
        {
            endwin();
            return 0;
        }
        else if (gameOverOption == 'r') // 'R'을 누르면 게임 재시작
        {
            gameManager->resetMapIndex();
            GameManager::GetInstance()->Start(); // 게임 재시작
        }
    }

    endwin(); // Curses 모드 종료
    return 0;
}