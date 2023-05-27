#pragma once


// Singleton 매크로
#define SINGLE(type) public:\
                         static type* GetInst()\
                         {\
                             static type mgr;\
                             return &mgr;\
                         }\
                     private:\
                         type();\
                         ~type();

// 프레임간 소요시간
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define CLONE(type) type* clone() { return new type(*this); }

// 키 입력 조건 체크
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->getMousePos()

#define PI 3.1415926535f

// 타일 크기
#define TILE_SIZE 64

// Scene의 그룹
enum class GROUP_TYPE
{
    DEFAUL,         // 0
    TILE,
    PLAYER,
    MONSTER,
    PROJ_PLAYER,
    PROJ_MONSTER,

    UI  = 31,
    END = 32,
};

enum class SCENE_TYPE
{
    TOOL,
    START,
    STAGE_01,
    STAGE_02,

    END,
};

enum class BRUSH_TYPE
{
    HOLLOW,

    END,
};

enum class PEN_TYPE
{
    RED,
    GREEN,
    BLUE,

    END,
};

enum class EVENT_TYPE
{
    CREATE_OBJECT,
    DELETE_OBJECT,
    SCENE_CHANGE,

    END,
};