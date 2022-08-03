#include "raylib.h" //Render pipeline
#include <string>
#include <iostream>
#include "Generators/Maze.hpp" //Maze Generator (Recursive Backtracker)

//Note: This is all so haphazard, but I don't really have the motivation to reorganize all this

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

struct ButtonInfo{
    int x, y; //Top Left
    int sizeX, sizeY;
    Color background;
    string text;
};

//Some Main Functions
void createSquare(int, int, int, Color);
void loadAt(int, int);
void showMaze(Maze &maze);
bool clickInLocation(int mX, int mY, ButtonInfo); 

vector<ButtonInfo> buttons = {
    ButtonInfo{0, 0, 100, 100, Color{0, 255, 0, 200}, "Depth First\nGen"},
    ButtonInfo{100, 0, 100, 100, Color{255, 255, 0, 200}, "Kruskal Gen"},
    ButtonInfo{0, windowDim-100, 100, 100, Color{0, 100, 255, 200}, "SOLVER\nTO DO"},
};

int main(){
    InitWindow(windowDim, windowDim, "Maze Generator 9000");
    SetTargetFPS(30);

    float time = 0.0f;

    Maze picture = Maze{wallMax};
    DepthFirstGenerator dfGen;
    KruskalGenerator kGen;

    Generator currentGen = NONE;

    picture.Clear();

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

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            cout << dfGen.FinishedGenerate() << kGen.Finished() << endl;
            if (dfGen.FinishedGenerate() && kGen.Finished() && currentGen == NONE){
                int mX = GetMouseX();
                int mY = GetMouseY();

                //cout << 2;

                if (clickInLocation(mX, mY, buttons[0])){
                    dfGen.Reset(picture);
                    currentGen = DEPTH_FIRST;
                }else if (clickInLocation(mX, mY, buttons[1])){
                    kGen.Reset(picture);
                    currentGen = KRUSKAL;
                }
            }
        }

        BeginDrawing();
            ClearBackground(GRAY);
            
            showMaze(picture);

            if (currentGen != NONE){
                if (currentGen == DEPTH_FIRST){
                    if (!dfGen.FinishedGenerate()){
                        int x = dfGen.currentCell[0];
                        int y = dfGen.currentCell[1];
                        createSquare(wallSize, x * wallSize, y * wallSize, RED); //Current "Digger" Location
                        if (time >= generateStepTime){
                            dfGen.StepMaze(picture);

                            time = 0;
                        }

                        time += GetFrameTime();
                    }else{
                        currentGen = NONE;
                    }
                }else if (currentGen == KRUSKAL){
                    if (!kGen.Finished()){
                        if (time >= generateStepTime){
                            kGen.StepMaze(picture);

                            time = 0;
                        }

                        time += GetFrameTime();
                    }else{
                        currentGen = NONE;
                    }
                }
            }else{
                for (unsigned i = 0; i < buttons.size(); i++){
                    ButtonInfo b = buttons.at(i);
                    DrawRectangle(b.x, b.y, b.sizeX, b.sizeY, b.background);
                    DrawText(b.text.c_str(), b.x + 5, b.y + 40, 20, BLACK);
                }
            }

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

bool clickInLocation(int mX, int mY, ButtonInfo b){
    int bX = b.x; int tX = bX + b.sizeX;
    int bY = b.y; int tY = bY + b.sizeY;

    return mX > bX && mX < tX && mY > bY && mY < tY;
};

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
    for (int i = 0; i < maze.size; i++){
        for (int j = 0; j < maze.size; j++){
            //cout << i << ", " << j << endl;
            if (maze.scene.at(i).at(j)== '#'){
                createSquare(wallSize, i*wallSize, j*wallSize, BLACK);
            }
        }
    }
}