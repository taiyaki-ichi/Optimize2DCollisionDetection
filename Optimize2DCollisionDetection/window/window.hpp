#pragma once
#include<Windows.h>
#include<optional>
#include<glew.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "winmm.lib")

namespace my
{

    HWND create_simple_window(const wchar_t* window_name, float width, float height)
    {
        //ハンドルの獲得
        HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return nullptr;

        // ウィンドウクラス設定
        WNDCLASSEX wcex = {
            sizeof(WNDCLASSEX),
            //ダブルクリック感知、クローズボタンなし
            CS_DBLCLKS| CS_NOCLOSE,
            DefWindowProc,
            0,
            0,
            hInstance,
            LoadIcon(NULL, IDI_APPLICATION),
            LoadCursor(NULL, IDC_ARROW),
            NULL,
            NULL,
            window_name,
            NULL
        };

        if (!RegisterClassEx(&wcex))
            return nullptr;

        //ウィンドウの生成
        hwnd = CreateWindowEx(
            0,
            window_name,
            window_name,
            //超シンプル
            WS_VISIBLE,
            CW_USEDEFAULT,
            0,
            static_cast<int>(width),
            static_cast<int>(height),
            NULL,
            NULL,
            hInstance,
            NULL);

        if (!hwnd)
            return nullptr;

        //ウィンドウの整形
        RECT rc1;
        RECT rc2;
        GetWindowRect(hwnd, &rc1);
        GetClientRect(hwnd, &rc2);
        width += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
        height += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
        SetWindowPos(hwnd, NULL, 0, 0, static_cast<int>(width), static_cast<int>(height), (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        return hwnd;
    }

    bool process_window_message()
    {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //ダブルクリックで消せるように
            if (msg.message== WM_LBUTTONDBLCLK) 
                return false;
            else {
                DispatchMessage(&msg);
                return true;
            }
        }
        else
            return true;
    }

    std::pair<HDC, HGLRC> init_opengl(HWND hwnd)
    {
        // ピクセルフォーマット初期化
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),  //サイズ
            1,  //1固定
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //描写可能、OpenGL使用可能、ダブルバッファリング
            PFD_TYPE_RGBA, //赤、緑、青、アルファ値の順で色指定
            32, //各カラーバッファのカラービットプレーンの数
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, //深度（z軸）バッファの深度
            8, //ステンシルバッファ
            0, //補助バッファの数
            PFD_MAIN_PLANE, //今は使われてない
            0,  //オーバーレイとアンダーレイの面の数
            0, 0, 0
        };

        //デバイスコンテキストの取得
        HDC dc = GetDC(hwnd);
        int format = ChoosePixelFormat(dc, &pfd);
        // 該当するピクセルフォーマットが無い場合
        if (format == 0)
            return { nullptr,nullptr };

        // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
        if (!SetPixelFormat(dc, format, &pfd))
            return { nullptr,nullptr };

        // OpenGL contextを作成
        HGLRC glRC = wglCreateContext(dc);

        // 作成されたコンテキストが現在使用中のコンテキストかどうか
        if (!wglMakeCurrent(dc, glRC))
            return { nullptr,nullptr };

        return { dc,glRC };
    }

    void shutdown(HWND hwnd, HDC hdc, HGLRC hglrc)
    {
        //カレントコンテキストを削除
        wglDeleteContext(hglrc);

        //デバイスコンテキストを開放
        ReleaseDC(hwnd, hdc);
    }
}