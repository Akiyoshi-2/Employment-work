#pragma once
#include "../BulletBase.h"

class PlayerBullet : public BulletBase
{
public:
    PlayerBullet();
    virtual ~PlayerBullet();

    void Init() override;
    void Load() override;
    void Start() override;
    void Step() override;
    void Update() override;
    void Draw() override;
    void Fin() override;


private:
};