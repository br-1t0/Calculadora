#include "raylib.h"
// #include "mainCalc.h"

#define SCREEN_WIDTH 400 // preciso então de distancia de 100 pra ter 4 botões na tela
#define SCREEN_HEIGHT 600

char operacao = 0;
double resultado;
double num1 = 0, num2 = 0; // num1 = 8.84554654654654, num2 = 3.542145464654654654;
// char entrada[20] = "";
bool digitandoNum1 = true;

double calcular(double a, double b, int o)
{
    switch (o)
    {
    case 1:

        return (double)a + b;

    case 2:
        return (double)a - b;

    case 3:
        return (double)a * b;

    case 4:
        return (double)(b != 0) ? a / b : 0;
        {
        }
    }
}

void adicionarNum(int digito)
{

    if (digitandoNum1)
    {
        num1 = num1 * 10 + digito;
    }
    else
    {
        num2 = num2 * 10 + digito;
    }
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Calculadora");
    // SetTargetFPS(60);
    InitAudioDevice();
    Sound sfx_botao = LoadSound("./sfx/buttonSound.wav");

    // float num1 = 0, num2 = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePos = GetMousePosition();
        // bool botaoAct = false;

        DrawText("Calculadora", 140, 20, 20, BLACK); // DrawText recebe (texto,posHorizontal,posVertical,tamahno,cor)
        DrawText(TextFormat("Num1: %.2f ", num1), 50, 100, 20, DARKGRAY);
        DrawText(TextFormat("Num2: %.2f ", num2), 50, 140, 20, DARKGRAY);
        DrawText(TextFormat("Operação: %u ", operacao), 50, 180, 20, DARKGRAY);
        DrawText(TextFormat("Resultado: %.2f", resultado), 50, 220, 20, RED);

        // botoes de opercoes
        for (int i = 0; i < 4; i++)
        {
            char operacoes_Simbolos[] = {'+', '-', 'x', '/'};
            Rectangle botao = {20 + (i * 100), 300, 60, 40};                                     // recebe posHorizontal,posVerical,largura,altura, for pra poupar código 50(pos inicial) + i(n_botoes)*distancia de cada
            DrawRectangleRec(botao, LIGHTGRAY);                                                  // recebe uma struct (Retangle, cor)
            DrawText(TextFormat("%c", operacoes_Simbolos[i]), botao.x + 20, botao.y, 40, BLACK); // text, horizontal,vertical,tamanho,cor

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botao) || IsKeyPressed(334 - i))
            {
                operacao = 1 + i;
                digitandoNum1 = false;
            }
        }

        // botoes dos numeros
        int num = 1;

        for (int j = 0; j < 3; j++)
        {

            for (int i = 0; i < 4; i++)
            {
                if (num > 9)
                {
                    break;
                }

                Rectangle n_botao = {20 + (i * 100), 400 + (j * 60), 60, 40};
                DrawRectangleRec(n_botao, LIGHTGRAY);
                DrawText(TextFormat("%u", num), n_botao.x + 20, n_botao.y, 40, BLACK);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, n_botao) || IsKeyPressed(48 + num) || IsKeyPressed(320 + num))
                {
                    adicionarNum(num);
                    PlaySound(sfx_botao);
                }

                num++;
            }
        }

        // botao zero
        Rectangle botao_zero = {20 + 100, 400 + (2 * 60), 60, 40}; // lembrando, ele recebe horizontal,vertical,largura e altura. Aqui é 3 por que é a distancia de 3 botoes ja feitos pelo for
        DrawRectangleRec(botao_zero, LIGHTGRAY);
        DrawText("0", botao_zero.x + 20, botao_zero.y, 40, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botao_zero) || IsKeyPressed(48) || IsKeyPressed(320))
        {
            PlaySound(sfx_botao);
            adicionarNum(0);
        }
        // botao .              // implementação é difícil de fazer com a interface gráfica
        /*Rectangle botao_ponto = {20 + 200, 400 + (2 * 60), 60, 40}; // lembrando, ele recebe horizontal,vertical,largura e altura. Aqui é 3 por que é a distancia de 3 botoes ja feitos pelo for
        DrawRectangleRec(botao_ponto, LIGHTGRAY);
        DrawText(".", botao_ponto.x + 28, botao_ponto.y - 10, 40, BLACK);*/

        // botao =
        Rectangle botao_igual = {20 + 300, 400 + (2 * 60), 60, 40};
        DrawRectangleRec(botao_igual, ORANGE);
        DrawText("=", botao_igual.x + 20, botao_igual.y, 40, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botao_igual) || IsKeyPressed(257)) // recebe Vector2 point, Rectangle rec
        {
            PlaySound(sfx_botao);
            resultado = calcular(num1, num2, operacao);
        }

        // botao clear
        Rectangle botao_limpar = {20 + 200, 400 + (2 * 60), 60, 40};
        DrawRectangleRec(botao_limpar, LIGHTGRAY);
        DrawText("C", botao_limpar.x + 20, botao_limpar.y, 40, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botao_limpar) || IsKeyPressed(67))
        {
            PlaySound(sfx_botao);
            num1 = 0;
            num2 = 0;
            operacao = 0;
            resultado = 0;
            digitandoNum1 = true;
        }

        // ifs pressionamos botoes

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
