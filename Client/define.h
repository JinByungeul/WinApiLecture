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

#define PI 3.1415926535f

// Scene의 그룹
enum class GROUP_TYPE
{
    DEFAUL,         // 0
    PLAYER,         // 1
    MONSTER,        // 2
    PROJ_PLAYER,    // 3
    PROJ_MONSTER,   // 4

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