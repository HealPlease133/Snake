#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "GameData.h"
#include "ItemSpawner.h"
#include "Snake.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GateSpawner.h"

class GameManager
{
private:
    GameData data;                             // 현재 게임의 진행사항
    static GameManager *instance;              // 이 클래스의 인스턴스
    std::vector<LoopBehavior *> loopBehaviors; // 틱마다 실행할 행동들의 목록
    GameManager(const GameManager &other);     // 복사 생성자
    GameManager() { Start(); }                 // 기본 생성자

public:
    bool isGameOver()
    {
        return data.gameOver;
    } // 게임오버 여부를 반환

    static GameManager *GetInstance()
    {
        if (instance == NULL)
        {
            instance = new GameManager();
        }
        return instance;
    } // 인스턴스가 없을 경우 생성, 있을 경우 해당 인스턴스 반환 (싱글 톤 패턴)

    void Start()
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                int edgeCount = 0;
                if (i == 0 || i == HEIGHT - 1)
                    edgeCount++;
                if (j == 0 || j == WIDTH - 1)
                    edgeCount++;
                // edgeCount = 해당 위치가 모퉁이인 경우 2, 모서리인 경우 1, 그외의 경우 0

                if (edgeCount == 1)
                    data.map[i][j] = WALL; // 모서리 부분에 벽 생성
                else if (edgeCount == 2)
                    data.map[i][j] = IMMUNE_WALL; // 모퉁이 부분에 고정 벽 생성
                else
                    data.map[i][j] = EMPTY; // 그 외는 빈 공간으로 생성
            }
        }

        for (auto &behavior : loopBehaviors)
        {
            delete (behavior); // 할당되었던 행동들 해제
        }
        data.nowTime = 0;      // 시간 초기화
        data.gameOver = false; // 게임오버여부 초기화
        data.nowState = STOP;  // 뱀 상태 초기화
        loopBehaviors.clear();
        // 틱마다 발생할 행위들의 목록------------------------------------------------------
        loopBehaviors.push_back(new InputManager(&data));  // 플레이어의 입력값을 받는다
        loopBehaviors.push_back(new GateSpawner(&data));         // 포탈 생성을 관리한다
        loopBehaviors.push_back(new Snake(&data));         // 뱀이 한 칸 이동한다
        loopBehaviors.push_back(new ItemSpawner(&data));   // 아이템 생성을 관리한다
        loopBehaviors.push_back(new WindowManager(&data)); // 최종적인 결과를 실제 화면에 그린다
        // -------------------------------------------------------------------------------
    } // 게임 진행상황 초기화

    void Update()
    {
        data.nowTime++;
        for (auto &behavior : loopBehaviors)
        {
            behavior->Update(); // 목록에 저장된 모든 행동 실행
        }
    } // 틱마다 호출되어 모든 행동들을 실행
};

GameManager *GameManager::instance = NULL;