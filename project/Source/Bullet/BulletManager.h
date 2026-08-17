#pragma once

#include <list>

class BulletBase;

class BulletManager
{
public:
    static void CreateInstance() { if (!m_Instance) m_Instance = new BulletManager; }
    static BulletManager* GetInstance() { return m_Instance; }
    static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

    void AddBullet(BulletBase* bullet);

private:
    BulletManager();
    ~BulletManager();

    static BulletManager* m_Instance;

    std::list<BulletBase*> m_BulletList;
};