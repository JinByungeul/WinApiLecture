// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 함수의 전방 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL(소스코드주석언어): _In_, _In_opt_ ...
int APIENTRY wWinMain(_In_ HINSTANCE hInstance  /* 실행된 프로세스의 시작 주소 */
                    , _In_opt_ HINSTANCE hPrevInstance
                    , _In_ LPWSTR lpCmdLine
                    , _In_ int nCmdShow)
{
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

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    // 3. 기본 메시지 루프
    // GetMessage
    // 메시지 큐에서 메시지가 확인될 때까지 대기
    // msg.message == WM_QUIT 인 경우, false 를 반환 => 프로그램 종료
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) // 프로그램의 '메시지 큐'에서 꺼내서
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 테이블 확인
        {
            TranslateMessage(&msg);         // 메시지 해석
            DispatchMessage(&msg);          // 메시지 처리: 메인 윈도우의 프로시저(WndProc) 호출
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100, 100 };

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

            // Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);
            // DC의 목적지는 hWnd
            // DC의 펜은 기본펜(Black)
            // DC의 브러쉬는 기본 브러쉬(White) 

            // 직접 펜과 브러쉬를 만들어서 DC에 적용
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // 기존 펜과 브러쉬 ID 값을 받아 둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            // 변경된 펜과 브러쉬로 사각형 그림
            Rectangle(hdc
                , g_ptObjPos.x - g_ptObjScale.x / 2
                , g_ptObjPos.y - g_ptObjScale.y / 2 
                , g_ptObjPos.x + g_ptObjScale.x / 2
                , g_ptObjPos.y + g_ptObjScale.y / 2);

            // DC의 펜과 브러쉬를 원래대로 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 펜과 브러쉬 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);
            
            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_DOWN:
            g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        
        case VK_LEFT:
            g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            g_ptObjPos.x += 10;
            break;
            InvalidateRect(hWnd, nullptr, true);
        }
    }
        break;

    case WM_LBUTTONDOWN:
    {
        g_x = LOWORD(lParam);
        g_y = HIWORD(lParam);
    }
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
