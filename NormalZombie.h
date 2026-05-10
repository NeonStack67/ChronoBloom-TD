#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
public:
    NormalZombie(int lane, EventManager& bus);

    // 暂不需要重写 update，因为基类 Zombie 已经提供了“每一帧向左移动”的默认逻辑
    // 除非未来你想给它加断手断脚的特殊逻辑，再重写也不迟
};