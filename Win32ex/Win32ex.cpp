// Win32ex.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32ex.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32EX, szWindowClass, MAX_LOADSTRING);


    //윈도우 정보 등록
    MyRegisterClass(hInstance);


    // 애플리케이션 초기화를 수행합니다: 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    //단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32EX));


    MSG msg;
    

    // 기본 메시지 루프입니다:
    // 이 프로그램에서 발생한 메세지 큐들을 꺼내보는 것
    while (GetMessage(&msg, nullptr, 0, 0)) // msg.message == WM_QUIT 일때 false 반환 -> while 문 종료 -> 프로그램 종료
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    return (int) msg.wParam;
}



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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32EX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32EX);
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

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


// ///////////////////////////////////////////////////
#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjectPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;


// 좌 상단
POINT g_ptLT;
// 우 하단
POINT g_ptRB;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // wParam : key 값 lParam : 마우스 값 
// LPARAM 이 4byte 인데 이걸로도 마우스 좌표 나타내기에 충분함. 각각 2^16 까지 표현가능하니 
{
    // switch - case 문 안에 변수를 선언할때는 반드시 괄호를 써줘야
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

    case WM_PAINT: // 무효화 영역이 발생한 경우
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // device context 만들어서 ID 를 반환
            // 어떤놈에 그릴것인지, 사용할 툴은 멀 사용할지 결정하는놈 hWind가 그릴 대상, ps가 툴을 모아놓은 구조체 
            // 
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // DC 의 목적지는 hWnd
            // DC 의 펜은 기본펜(Black) 테두리
            // DC 의 브러쉬는 기본 브러쉬(White) 채움색

            // 픽셀 1 개의 크기는 3byte (RGB)

            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); 
            //HBRUSH hBlueBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // CreateBrush 도 있는데 이거 같은 경우엔 win32 자체적으로 있는 브러쉬를 가져다 쓸때 사용함. 물론 다쓰고나서 지울필요 없다.
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));


            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); // hdc 의 기본펜을 빨강색으로 변경 반환값은 void* 형식으로 기존 검은색펜 반환.
            // HGDIOBJ == void* 왜 반환값이 void* 이냐? HPEN 뿐만아니라 HBRUSH 등등도 반환 해야하므로 즉 반환값이 범용적이기 때문.
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);


           // Rectangle(hdc, 10, 10, 110, 110);
            Rectangle(hdc, g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y);


            SelectObject(hdc, hDefaultPen); // 기존 검은색으로 다시변경
            SelectObject(hdc, hDefaultBrush);


            DeleteObject(hRedPen); // 빨강색펜은 다썻으니 지워버림 즉 OS에게  kernel object 삭제 '요청'
            DeleteObject(hBlueBrush);


            EndPaint(hWnd, &ps);
            
        }
        break;


        //키 눌렀을때 실행되게 즉 구동부
    case WM_KEYDOWN:
    {

        switch (wParam)
        {

        case VK_UP:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd,nullptr,true); // 무효화 됬다고 윈도우에 강제적으로 알려줌 2번째 인자가 nullptr이면 전체영역 3번째 인자가 true 면 기존의 영역을 전부 지움
            // WM_PAINT 를 다시 실행하게끔함
            break;

        case VK_DOWN:
           // g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
           // g_ptObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
          //  g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

            

        case 'W': // 소문자는 안된다
        {
            int a = 0;
        }
        default:
            break;

        }
    }
    break;

    case WM_LBUTTONDOWN://마우스 왼쪽버튼 클릭할때
    {
       g_ptLT.x = LOWORD(lParam);
       g_ptLT.y = HIWORD(lParam);
    }
    break;

    case WM_MOUSEMOVE: //마우스 움직일때
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_LBUTTONUP:
    {

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
