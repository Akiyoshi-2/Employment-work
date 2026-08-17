#pragma once
#include "DxLib.h"
#include "../Collision/CollisionAABB.h"

class Floor
{
public:
    Floor();
    ~Floor();

    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

    CollisionAABB* GetCollision()
    {
        return &m_Collision;
    }

    VECTOR GetPos() const
    {
        return m_Pos;
    }

private:
    int m_Handle;

    VECTOR m_Pos;

    CollisionAABB m_Collision;
};