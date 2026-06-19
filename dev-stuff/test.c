#include "raylib.h"
#include "rlgl.h"



int main(void) 
{
    // 1. Инициализация окна
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Raylib 3D - Свободная камера и Модель");

    // 2. Настройка свободной 3D-камеры
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 15.0f }; // Позиция камеры в мире
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Куда камера смотрит изначально
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Ось ВВЕРХ (в Raylib это Y)
    camera.fovy = 60.0f;                               // Угол обзора
    camera.projection = CAMERA_PERSPECTIVE;            // Перспективная проекция

    // 3. Загрузка 3D модели (Положи её в ту же папку, где лежит исполняемый файл)
    // Внимание: Если используешь .stl, Raylib выдаст ошибку в консоли. Используй .obj или .gltf
    Model model = LoadModel("obj.obj"); 
    Vector3 modelPosition = { 0.0f, 0.0f, 0.0f };      // Координаты спавна модели

    // Скрываем курсор мыши и фиксируем его в центре экрана (для свободного обзора)
    DisableCursor();

    SetTargetFPS(60);

    // Главный игровой цикл
    while (!WindowShouldClose()) 
    {

		#define MAX_STREAMS 20 // Количество вертикальных потоков символов
		int streamX[MAX_STREAMS];
		float streamY[MAX_STREAMS];
		float streamSpeed[MAX_STREAMS];
		
		for (int i = 0; i < MAX_STREAMS; i++) {
		    streamX[i] = GetRandomValue(0, GetScreenWidth());
		    streamY[i] = GetRandomValue(0, 700);
		    streamSpeed[i] = 0.3f;
		}
		

        // 4. Обновление камеры (РЕЖИМ FREE — дает управление через WASD + мышь)
        // Доступные режимы: CAMERA_FREE, CAMERA_FIRST_PERSON, CAMERA_THIRD_PERSON
        UpdateCamera(&camera, CAMERA_FREE);

        // Если зажать левый Alt, можно временно вернуть курсор (полезно при отладке)
        if (IsKeyPressed(KEY_LEFT_ALT)) EnableCursor();
        if (IsKeyPressed(KEY_LEFT_CONTROL)) DisableCursor();

        // 5. Отрисовка кадра
        BeginDrawing();
            ClearBackground(BLACK);

    for (int i = 0; i < MAX_STREAMS; i++) {
        streamY[i] += streamSpeed[i];
        if (streamY[i] > GetScreenHeight()) {
            streamY[i] = GetRandomValue(0, 500);
            streamX[i] = GetRandomValue(0, GetScreenWidth());
        }
        
        // Рисуем один случайный символ для каждого потока (имитация хвоста)
        char glyph[2] = { (char)GetRandomValue(33, 126), '\0' };
        DrawText(glyph, streamX[i], (int)streamY[i], 16, LIME);
        DrawText(glyph, streamX[i], (int)streamY[i] - 20, 16, GREEN);
    }

            // Начало 3D режима
            BeginMode3D(camera);

                // Рисуем твою загруженную модель (масштаб 1.0f, цвет белый)
				DrawModelWires(model, modelPosition, 1.0f, RED); 
                // Рисуем сетку для ориентира в пространстве (48x48 клеток, шаг 1.0f)
                DrawGrid(96, 1.0f);
	
            EndMode3D();

            // Интерфейс поверх экрана (2D)
            DrawText("Управление: WASD + Мышь. Нажми ESC для выхода.", 10, 10, 20, LIGHTGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    // 6. Очистка памяти перед закрытием программы
    UnloadModel(model); // Выгружаем модель из видеопамяти
    CloseWindow();      // Закрываем окно

    return 0;
}
