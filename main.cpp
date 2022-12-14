#include <string>
#include <iostream>

#include "raylib.h" //Render pipeline

#include "Generators/Maze.hpp"
#include "Generators/DepthFirst/DepthFirst.hpp"
#include "Generators/Kruskal/Kruskal.hpp"
#include "Solvers/Greedy/Greedy.hpp"
#include "Solvers/Dijkstras/Dijkstras.hpp"

//Note: This is all so haphazard, but I don't really have the motivation to reorganize all this
enum Generator {DEAF = 0, DEPTH_FIRST, KRUSKAL};
enum Solver {BLIND = 0, GREEDY, DIJK};

//Globals
const int windowDim = 900;
const int cellAmount = 21;
const float generateStepTime = 0.02f;
const float solveStepTime    = 0.00225f;

//Calculated Globals
const int wallMax = (cellAmount*2+1);
const int wallSize = windowDim / wallMax;
const int whiteBorder = (windowDim - (wallSize * wallMax)) / 1.5; //I don't understand why the centering border/extra space isn't consistent at all cell amounts

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
void showPath(vector<pair<int, int>> &, Color);

vector<ButtonInfo> buttons = {
    //Top
    ButtonInfo{0, 0, 100, 100, Color{0, 255, 0, 150}, "Depth\nFirst\nGen"},
    ButtonInfo{100, 0, 100, 100, Color{255, 255, 0, 150}, "Kruskal\nGen"},

    //Bottom
    ButtonInfo{0, windowDim-100, 100, 100, Color{0, 100, 255, 150}, "Greedy\nSolver"},
    ButtonInfo{100, windowDim-100, 100, 100, Color{255, 0, 255, 150}, "Dijkstra's\nSolver"},
};

int main(){
    InitWindow(windowDim, windowDim, "Maze Generator 9000");
    SetTargetFPS(60);

    float time = 0.0f;

    Maze picture = Maze{wallMax};
    
    //Generators
    DepthFirstGenerator dfGen;
    KruskalGenerator kGen;

    //Solvers
    GreedySolver gSolv;
    DijkstraSolver dSolv;

    Solver currentSolv = BLIND;
    Generator currentGen = DEAF;

    picture.Clear();

    //Start Up Animation
    /*for (int i = 0; i < wallMax; i++){
        BeginDrawing();
        ClearBackground(GRAY);
        for (int j = 0; j < wallMax; j++){
            loadAt(j , i);
        }
        EndDrawing();
    }*/

    while (!WindowShouldClose()){

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount() > 0){
            //cout << dfGen.FinishedGenerate() << kGen.Finished() << endl;
            if (dfGen.FinishedGenerate() && kGen.Finished() && currentGen == DEAF && currentSolv == BLIND){
                int mX = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? GetMouseX() : GetTouchX();
                int mY = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? GetMouseY() : GetTouchY();

                //cout << 2;

                if (clickInLocation(mX, mY, buttons[0])){
                    dfGen.Reset(picture);

                    currentGen = DEPTH_FIRST;
                    currentSolv = BLIND;
                }else if (clickInLocation(mX, mY, buttons[1])){
                    kGen.Reset(picture);

                    currentGen = KRUSKAL;
                    currentSolv = BLIND;
                }else if (clickInLocation(mX, mY, buttons[2])){
                    gSolv.Reset(picture);

                    currentGen = DEAF;
                    currentSolv = GREEDY;
                }else if (clickInLocation(mX, mY, buttons[3])){
                    dSolv.Reset(picture, {picture.size - 2, picture.size - 2});

                    currentGen = DEAF;
                    currentSolv = DIJK;
                }
            }
        }

        BeginDrawing();
            ClearBackground(GRAY);
            
            showMaze(picture);
            showPath(picture.path, YELLOW);

            if (currentGen != DEAF){
                if (currentGen == DEPTH_FIRST){
                    if (!dfGen.FinishedGenerate()){
                        int x = dfGen.currentCell[0];
                        int y = dfGen.currentCell[1];
                        createSquare(wallSize, x * wallSize, y * wallSize, RED); //Current "Digger" Location
                        if (time >= generateStepTime){
                            dfGen.StepMaze(picture);

                            time = 0;
                        }
                    }else{
                        currentGen = DEAF;
                    }
                }else if (currentGen == KRUSKAL){
                    if (!kGen.Finished()){
                        if (time >= generateStepTime){
                            kGen.StepMaze(picture);

                            time = 0;
                        }
                    }else{
                        currentGen = DEAF;
                    }
                }

                time += GetFrameTime();
            }else if (currentSolv != BLIND){
                if (currentSolv == GREEDY) {
                    showPath(gSolv.tried, BLUE);
                    if (!gSolv.IsFinished()){
                        if (time >= solveStepTime){
                            gSolv.StepSolve(picture, {picture.size - 1, picture.size - 2}, {0, 1});

                            time = 0;
                        }
                    }else{
                        currentSolv = BLIND;
                    }
                }else if (currentSolv == DIJK){
                    showPath(dSolv.visited, PURPLE);
                    if (!dSolv.IsFinished()){ //while not finished
                        if (time >= solveStepTime){
                            dSolv.StepSolve(picture, {1, 1});

                            time = 0;
                        }
                    }else{
                        currentSolv = BLIND;
                    }
                }

                time += GetFrameTime();
            }else{
                for (unsigned i = 0; i < buttons.size(); i++){
                    ButtonInfo b = buttons.at(i);
                    DrawRectangle(b.x, b.y, b.sizeX, b.sizeY, b.background);
                    DrawText(b.text.c_str(), b.x + 5, b.y + 20, 20, BLACK);
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

void showPath(vector<pair<int, int>> &path, Color col){
    for (unsigned i = 0; i < path.size(); i++){
        createSquare(wallSize, path[i].first*wallSize, path[i].second*wallSize, col);
    }
}