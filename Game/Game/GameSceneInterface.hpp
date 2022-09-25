#ifndef GameScene_Interface_hpp
#define GameScene_Interface_hpp

#include "interfaces.h"

class GameSceneI
{
protected:
    bool m_isActive;

public:
    GameSceneI() { };
    virtual ~GameSceneI() { };

public:
    void SetActive(bool val) { m_isActive = val; };

public:
    virtual engine::SceneI *GetSceneObj() = 0;
    virtual void DidActivate() = 0;
    virtual void DidDeactivate() = 0;
};

#endif /* GameScene_hpp */
