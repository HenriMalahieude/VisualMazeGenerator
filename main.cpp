#include "raylib.h" //Render pipeline

#include "Generators/Maze.hpp" //Maze Generator (Recursive Backtracker)

//Globals
const int windowDim = 900;
const int cellAmount = 21;
const float generateStepTime = 0.025f;
const float solveStepTime    = 0.005f;

//Calculated Globals
const int wallMax = (cellAmount*2+1);
const int wallSize = windowDim / wallMax;
const int whiteBorder = (windowDim - (wallSize * wallMax)) / 1.5; //I don't understand why the centering border/extra space isn't consitent at all cell amounts

//Global Variables
bool loaded = false;

void createSquare(int, int, int, Color);
void loadAt(int, int);
void showMaze(vector<vector<char>>);

int main(){
    InitWindow(windowDim, windowDim, "Maze Generator 9000");
    SetTargetFPS(60);

    float time = 0.0f;

    Maze picture = Maze{cellAmount};
    DepthFirstGenerator dfSolver;

    //Start Up Animation
    for (int i = 0; i < wallMax; i++){
        BeginDrawing();
        ClearBackground(GRAY);
        for (int j = 0; j < wallMax; j++){
            loadAt(j , i);
        }
        EndDrawing();
    }
    

    while (!WindowShouldClose()){

        /*if (maze.FinishedGenerate() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int mX = GetMouseX();
            int mY = GetMouseY();

            if (mX > 0 && mX < 100 && mY > 700 && mY < 800){
                maze.ResetMaze();
            }
        }*/

        BeginDrawing();
            ClearBackground(GRAY);
            
            showMaze(picture);

            if (!dfSolver.FinishedGenerate()){
                int x = dfSolver.currentCell[0];
                int y = dfSolver.currentCell[1];
                createSquare(wallSize, x * wallSize, y * wallSize, RED); //Current "Digger" Location
                if (time >= generateStepTime){
                    dfSolver.StepMaze(picture);

                    time = 0;
                }

                time += GetFrameTime();
            }else{
                DrawRectangle(0, 700, 100, 100, GREEN);
                DrawText("Regen", 20, 740, 25, BLACK);
            }

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void createSquare(int size, int x, int y, Color col){
    int pX = x - (size/2) + whiteBorder; //- windowDim/2;
    int pY = y - (size/2) + whiteBorder; //- windowDim/2;

    DrawRectangle(pX, pY, size, size, col);
}

void loadAt(int h, int v){ 
    for (int i = 0; i < wallMax; i++){
        for (int j = 0; j < v; j++){
            if ((i) % 2 == 0 || (j) % 2 == 0){
                createSquare(wallSize, i*wallSize, j*wallSize, BLACK);
            }
        }
    }

    for (int i = 0; i < h; i++){
        createSquare(wallSize, i*wallSize, v*wallSize, RED);
    }
}

void showMaze(Maze &maze){
    for (int i = 0; i < wallMax; i++){
        for (int j = 0; j < wallMax; j++){
            if (maze.scene[i][j] == '#'){
                createSquare(wallSize, i*wallSize, j*wallSize, BLACK);
            }
        }
    }
}