#include "GateSpawner.h"
#include "WindowManager.h"
#include <cstdlib>
#include <ctime>
#include <vector>

GateSpawner::GateSpawner(GameData *_data) : data(_data), first(true), gateTime(0), duration(100)
{
    std::srand(std::time(0)); // 랜덤 시드 초기화
}

void GateSpawner::SpawnGate(ObjectType itemType)
{
    gateTime = 0;

    // 벽 위치를 저장할 벡터 선언
    std::vector<std::pair<int, int>> wallPositions;
    for (int r = 0; r < HEIGHT; ++r)
    {
        for (int c = 0; c < WIDTH; ++c)
        {
            if (data->map[r][c] == WALL)
            {
                wallPositions.emplace_back(r, c);
            }
        }
    }

    if (wallPositions.size() < 2)
    {
        // 벽 위치가 충분하지 않은 경우 적절히 처리
        return;
    }

    int index1 = std::rand() % wallPositions.size();
    int index2;
    do
    {
        index2 = std::rand() % wallPositions.size();
    } while (index1 == index2);

    int p1r = wallPositions[index1].first;
    int p1c = wallPositions[index1].second;
    int p2r = wallPositions[index2].first;
    int p2c = wallPositions[index2].second;

    if (!first)
    {
        data->map[gate1Pos.y][gate1Pos.x] = WALL;
        data->map[gate2Pos.y][gate2Pos.x] = WALL;
    }

    first = false;
    data->map[p1r][p1c] = itemType;
    data->map[p2r][p2c] = itemType;
    gate1Pos = {p1r, p1c};
    gate2Pos = {p2r, p2c};
}

void GateSpawner::Update()
{
    if (first)
    {
        SpawnGate(GATE);
    }

    if (data->gateUse)
    {
        gateTime = gateTime;
    }
    else
    {
        gateTime++; // 게이트 사용 중이 아닐 때만 지속시간 증가
    }

    if (duration <= gateTime)
    {
        SpawnGate(GATE);
    }
    // 지속시간이 다 된 경우 새로 생성
}
 // Update함수의 구현부