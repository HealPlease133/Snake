#include "GameData.h"
#include <stdlib.h>


class GateSpawner : public LoopBehavior
{
private:
    GameData *data;                      // 데이터
    const int duration = 30;             // 아이템의 최대 지속시간
    bool first = 1;
    pos gate1Pos;                       // 게이트1의 위치
    pos gate2Pos;                       // 게이트2의 위치
    int gateTime = 0;                  // 현재 게이트가 나와있었던 시간
    void SpawnGate(ObjectType itemType); // 파라미터로 받은 유형의 아이템을 랜덤 위치에 생성하는 함수

public:
    GateSpawner(GameData *_data); // 생성자
    void Update() override;       // 아이템을 먹었거나 아이템의 지속시간이 다 되었다면 새 아이템을 생성하는 함수
};


