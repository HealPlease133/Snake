#include "GameData.h"
#include <stdlib.h>

class ItemSpawner : public LoopBehavior
{
private:
    GameData *data;                      // 데이터
    const int duration = 15;             // 아이템의 최대 지속시간
    pos poisonPos;                       // 독 아이템의 위치
    int poisonTime = 0;                  // 현재 독 아이템이 나와있었던 시간
    pos growthPos;                       // 성장 아이템의 위치
    int growthTime = 0;                  // 현재 성장 아이템이 나와있었던 시간
    void SpawnItem(ObjectType itemType); // 파라미터로 받은 유형의 아이템을 랜덤 위치에 생성하는 함수

public:
    ItemSpawner(GameData *_data); // 생성자
    void Update() override;       // 아이템을 먹었거나 아이템의 지속시간이 다 되었다면 새 아이템을 생성하는 함수
};