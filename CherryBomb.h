#pragma once
#include "Plant.h"

class CherryBomb : public Plant {
public:
    CherryBomb(int lane, EventManager& bus);

    void destroy() override;

};
