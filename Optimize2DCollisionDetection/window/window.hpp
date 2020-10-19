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
        //�n���h���̊l��
        HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return nullptr;

        // �E�B���h�E�N���X�ݒ�
        WNDCLASSEX wcex = {
            sizeof(WNDCLASSEX),
            //�_�u���N���b�N���m�A�N���[�Y�{�^���Ȃ�
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

        //�E�B���h�E�̐���
        hwnd = CreateWindowEx(
            0,
            window_name,
            window_name,
            //���V���v��
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

        //�E�B���h�E�̐��`
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
            //�_�u���N���b�N�ŏ�����悤��
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
        // �s�N�Z���t�H�[�}�b�g������
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),  //�T�C�Y
            1,  //1�Œ�
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //�`�ʉ\�AOpenGL�g�p�\�A�_�u���o�b�t�@�����O
            PFD_TYPE_RGBA, //�ԁA�΁A�A�A���t�@�l�̏��ŐF�w��
            32, //�e�J���[�o�b�t�@�̃J���[�r�b�g�v���[���̐�
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, //�[�x�iz���j�o�b�t�@�̐[�x
            8, //�X�e���V���o�b�t�@
            0, //�⏕�o�b�t�@�̐�
            PFD_MAIN_PLANE, //���͎g���ĂȂ�
            0,  //�I�[�o�[���C�ƃA���_�[���C�̖ʂ̐�
            0, 0, 0
        };

        //�f�o�C�X�R���e�L�X�g�̎擾
        HDC dc = GetDC(hwnd);
        int format = ChoosePixelFormat(dc, &pfd);
        // �Y������s�N�Z���t�H�[�}�b�g�������ꍇ
        if (format == 0)
            return { nullptr,nullptr };

        // OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
        if (!SetPixelFormat(dc, format, &pfd))
            return { nullptr,nullptr };

        // OpenGL context���쐬
        HGLRC glRC = wglCreateContext(dc);

        // �쐬���ꂽ�R���e�L�X�g�����ݎg�p���̃R���e�L�X�g���ǂ���
        if (!wglMakeCurrent(dc, glRC))
            return { nullptr,nullptr };

        return { dc,glRC };
    }

    void shutdown(HWND hwnd, HDC hdc, HGLRC hglrc)
    {
        //�J�����g�R���e�L�X�g���폜
        wglDeleteContext(hglrc);

        //�f�o�C�X�R���e�L�X�g���J��
        ReleaseDC(hwnd, hdc);
    }
}