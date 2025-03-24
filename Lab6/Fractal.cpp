#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>

using namespace std;

// Структура для хранения точек
struct Point {
    double x, y;
};

// Функция для рисования кривой Гильберта
void hilbertCurve(vector<Point>& points, double x, double y, double xi, double xj, double yi, double yj, double n) {
    if (n <= 0) {
        double x1 = x + (xi + yi) / 2;
        double y1 = y + (xj + yj) / 2;
        points.push_back({ x1, y1 });
    }
    else {
        hilbertCurve(points, x, y, yi / 2, yj / 2, xi / 2, xj / 2, n - 1);
        hilbertCurve(points, x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
        hilbertCurve(points, x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
        hilbertCurve(points, x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2, n - 1);
    }
}

// Функция для отрисовки кривой
void drawHilbertCurve(HDC hdc, const vector<Point>& points) {
    if (points.empty()) return;

    MoveToEx(hdc, points[0].x, points[0].y, NULL);
    for (size_t i = 0; i < points.size(); ++i) {
        LineTo(hdc, points[i].x, points[i].y);
    }
}

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static vector<Point> points;
    static bool isDrawn = false;

    switch (msg) {
    case WM_CREATE: {
        // Генерация точек кривой Гильберта
        int depth = 3; // Глубина рекурсии
        hilbertCurve(points, 80, 80, 600, 0, 0, 600, depth);
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Отрисовка кривой
        if (!isDrawn) {
            drawHilbertCurve(hdc, points);
            isDrawn = true;
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Точка входа
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"HilbertCurveWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Hilbert Curve",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}