
#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스
HWND      g_hWnd;                               // 현재 윈도우
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 함수의 전방 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 변수 종류
// 지역
// 정적 (데이터 영역)
// 1. 함수 안에
// 2. 파일 안에
// 3. 클래스 안에 (초기화는 반드시 클래스 밖에서)
// 외부 

// SAL(소스코드주석언어): _In_, _In_opt_ ...
int APIENTRY wWinMain(_In_ HINSTANCE hInstance  /* 실행된 프로세스의 시작 주소 */
                    , _In_opt_ HINSTANCE hPrevInstance
                    , _In_ LPWSTR lpCmdLine
                    , _In_ int nCmdShow)
{
    // My-4 메모리 누수 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(220);   // 문제 생긴 곳에 중단점 => 디버깅 후 주석처리 요함!!!

    UNREFERENCED_PARAMETER(hPrevInstance);  // 쓰이지 않음
    UNREFERENCED_PARAMETER(lpCmdLine);      // 쓰이지 않음

    // TODO: 여기에 코드를 입력합니다.
    



    // 전역 문자열 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    
    // 1. 윈도우 정보 등록
    MyRegisterClass(hInstance); 

    // 2. 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 768 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    // 3. 기본 메시지 루프
    // GetMessage
    // 메시지 큐에서 메시지가 확인될 때까지 대기
    // msg.message == WM_QUIT 인 경우, false 를 반환 => 프로그램 종료

    // PeekMessage
    // 메시지 유무와 관계없이 반환
    // 메시지큐에서 메시지를 확인한 경우 true, 메시지가 없는 경우 false 를 반환
    
    MSG msg;

    while (true)
    {
        // 1. 윈도우 메시지가 있는 경우
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)         // 프로그램 종료
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 테이블 확인
            {
                TranslateMessage(&msg);         // 메시지 해석
                DispatchMessage(&msg);          // 메시지 처리: 메인 윈도우의 프로시저(WndProc) 호출
            }
        }
        // 2. 윈도우 메시지가 발생하지 않는 대부분의 시간
        else
        {
            // 우리의 코드 수행 부분
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴
            CCore::GetInst()->process();

        }
    }

    return (int) msg.wParam;

}// wWinMain



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

#include <vector>

using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

// 좌 상단
POINT g_ptLT;

// 우 하단
POINT g_ptRB;

bool blbtnDown = false;

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리
//  WM_PAINT    - 주 창을 그리기
//  WM_DESTROY  - 종료 메시지를 게시하고 반환
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT: // 무효화 영역(invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;

            // 1. 그리기 시작
            HDC hdc = BeginPaint(hWnd, &ps);    // Device Context (그리기)

            //Rectangle(hdc, 1180, 668, 1280, 768);
            
            // 2. 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:

        break;

    case WM_LBUTTONDOWN:

        break;

    case WM_MOUSEMOVE:

        break;

    case WM_LBUTTONUP:

        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
