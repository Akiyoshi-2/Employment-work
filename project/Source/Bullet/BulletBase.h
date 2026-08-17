#pragma once

#include "DxLib.h"

class BulletBase
{
public:
    BulletBase();
    virtual ~BulletBase();

    virtual void Init();
    virtual void Load();
    virtual void Start();
    virtual void Step();
    virtual void Update();
    virtual void Draw();
    virtual void Fin();

    void SetPos(float x, float y, float z);
    void SetMove(float x, float y, float z);

    bool IsDead() const;
    void SetDead();

    VECTOR GetPos() const
    {
        return m_Pos;
    }

protected:
    int m_Handle;

    VECTOR m_Pos;
    VECTOR m_Move;

    bool m_IsDead;
};