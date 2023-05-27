#pragma once

#include "CScene.h"

class CUI;

class CSceneTool :
    public CScene
{
private:
    CUI* m_pUI;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

    void setTileIdx();

    void saveTileData();
    void saveTile(const wstring& _strFilePath);

    void loadTileData();

public:
    CSceneTool();
    ~CSceneTool();
};