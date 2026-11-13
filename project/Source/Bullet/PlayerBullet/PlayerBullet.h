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

    void SetDamage(int damage) { m_Damage = damage; }
    int GetDamage() const { return m_Damage; }

private:
    int m_Damage = 1;
};