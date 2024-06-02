#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(GameData *_data)
{
    data = _data;
} // 생성자의 구현부

void ItemSpawner::SpawnItem(ObjectType itemType)
{
    int ry, rx;
    while (1)
    {
        ry = rand() % HEIGHT;
        rx = rand() % WIDTH;
        if (data->map[ry][rx] == EMPTY)
            break;
    } // 맵에서 비어있는 공간 무작위로 고르기
    data->map[ry][rx] = itemType; // 아이템 생성

    if (itemType == POISON_ITEM)
    {
        if (data->map[poisonPos.y][poisonPos.x] == POISON_ITEM)
            data->map[poisonPos.y][poisonPos.x] = EMPTY;
        poisonPos = {ry, rx};
        poisonTime = 0;
    }
    else if (itemType == GROWTH_ITEM)
    {
        if (data->map[growthPos.y][growthPos.x] == GROWTH_ITEM)
            data->map[growthPos.y][growthPos.x] = EMPTY;
        growthPos = {ry, rx};
        growthTime = 0;
    } // 기존에 있던 아이템에 대한 정보 초기화

} // SpawnItem 함수의 구현부

void ItemSpawner::Update()
{
    poisonTime++;
    growthTime++;
    if (data->map[poisonPos.y][poisonPos.x] != POISON_ITEM || duration <= poisonTime)
        SpawnItem(POISON_ITEM);
    if (data->map[growthPos.y][growthPos.x] != GROWTH_ITEM || duration <= growthTime)
        SpawnItem(GROWTH_ITEM);
    // 이미 먹었거나, 지속시간을 다 한 경우 새로 생성한다

} // Update함수의 구현부