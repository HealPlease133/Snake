#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>
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
    std::vector<std::string> mapFiles;         // 맵 파일들의 목록
    int currentMapIndex{};                     // 현재 맵의 인덱스
    GameManager(const GameManager &other);     // 복사 생성자
    GameManager() : currentMapIndex(0)         // 기본 생성자
    {
        // mapFiles.push_back("Map.txt");
        mapFiles.push_back("map0.txt");
        mapFiles.push_back("map1.txt");
        mapFiles.push_back("map2.txt");
        mapFiles.push_back("map3.txt");
        Start();
    }

public:
    bool isGameOver()
    {
        return data.gameOver;
    } // 게임오버 여부를 반환

    void resetMap(){
        currentMapIndex = 0;
    }
    
    void resetItem(){
        data.gate_target = 1;
        data.growth_item_target = 3;
        data.poison_item_target = 3;
        data.gate_count = 0;
        data.growth_item_count = 0;
        data.poison_item_count = 0;
    }

    static GameManager *GetInstance()
    {
        if (instance == NULL)
        {
            instance = new GameManager();
        }
        return instance;
    } // 인스턴스가 없을 경우 생성, 있을 경우 해당 인스턴스 반환 (싱글 톤 패턴)

    void LoadMap(const std::string &filename)
    {
        
        std::ifstream mapFile(filename);
        if (mapFile.is_open())
        {
            for (int i = 0; i < HEIGHT; i++)
            {
                std::string line;
                std::getline(mapFile, line);
                for (int j = 0; j < WIDTH; j++)
                {
                    if (j < line.length())
                    {
                        switch (line[j])
                        {
                        case 'W':
                            data.map[i][j] = WALL;
                            break;
                        case 'I':
                            data.map[i][j] = IMMUNE_WALL;
                            break;
                        case 'E':
                            data.map[i][j] = EMPTY;
                            break;
                        default:
                            data.map[i][j] = EMPTY; // 인식되지 않는 문자는 기본으로 EMPTY
                            break;
                        }
                    }
                    else
                    {
                        data.map[i][j] = EMPTY; // 줄이 너무 짧은 경우 기본으로 EMPTY
                    }
                }
            }
            mapFile.close();
        }
        else
        {
            // ncurses를 사용하여 오류 메시지 출력
            clear();
            mvprintw(0, 0, "맵 파일을 열 수 없습니다: %s", filename.c_str());
            refresh();
            getch();
        }
    }

    void Start()
    {
        LoadMap(mapFiles[currentMapIndex]);
        
        for (auto &behavior : loopBehaviors)
        {
            delete (behavior); // 할당되었던 행동들 해제
        }
        data.nowTime = 0;      // 시간 초기화
        data.gameOver = false; // 게임오버여부 초기화
        data.nowState = STOP;  // 뱀 상태 초기화
        data.gate_count = 0;
        data.growth_item_count = 0;
        data.poison_item_count = 0;
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

        // 특정 조건을 달성했을 때 맵을 변경하는 로직
        if (data.growth_item_count >= data.growth_item_target
            && data.poison_item_count >= data.poison_item_target
            && data.gate_count >= data.gate_target
            && currentMapIndex < mapFiles.size() - 1) // 
         {
            data.gateUse = false;
            data.growth_item_target += 3;
            data.poison_item_target += 3;
            data.gate_target += 2;
            currentMapIndex++;
            Start(); // 맵 로드
        }
    } // 틱마다 호출되어 모든 행동들을 실행
};

GameManager *GameManager::instance = NULL;