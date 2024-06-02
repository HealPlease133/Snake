#include "GateSpawner.h"
#include "WindowManager.h"

GateSpawner::GateSpawner(GameData *_data)
{
    data = _data;
} 

void GateSpawner::SpawnGate(ObjectType itemType)
{
    gateTime = 0;
    
    int p1r,p1c,p2r,p2c;
    while(1)
    {
        p1r = rand() % HEIGHT;
        p1c = rand() % WIDTH;
        if (data->map[p1r][p1c]==WALL) break;
    }
    while(1)
    {
        p2r = rand() % HEIGHT;
        p2c = rand() % WIDTH;
        if (data->map[p2r][p2c]==WALL) break;
    }
    if (first == 0)
    {
        data->map[gate1Pos.y][gate1Pos.x]= WALL;
        data->map[gate2Pos.y][gate2Pos.x]= WALL;
    }
    first = 0;
    data->map[p1r][p1c] = itemType;
    data->map[p2r][p2c] = itemType;
    gate1Pos = {p1r,p1c};
    gate2Pos = {p2r,p2c};

}

void GateSpawner::Update()
{
    if (first) SpawnGate(GATE);
    gateTime++;
    if (duration <= gateTime)
        SpawnGate(GATE);
    // 지속시간을 다 한 경우 새로 생성한다

} // Update함수의 구현부