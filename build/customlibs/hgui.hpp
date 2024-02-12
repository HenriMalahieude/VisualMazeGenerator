#include "raylib.h"
#include <string>
#include <list>

using namespace std;

class GUIManager{
    public:
        list<ScreenObject> buffer;

        GUIManager();
        void Render();
        void AddElement(ScreenObject*);
};

class ScreenObject{
    public:
        int priority = 0;
        Vector2 position;
        Vector2 size;
        Color col;

        ScreenObject() : position(0, 0), size(0, 0), col(BLACK){};
        ScreenObject(Vector2 pos, Vector2 siz, Color c): position(pos.x, pos.y), size(siz.x, siz.y), col(c){};
        
        virtual ScreenObject& operator=(const ScreenObject&) = 0;
        //virtual ScreenObject& operator==();
        virtual void Draw() = 0;
};

class TextObject : public ScreenObject{
    public:
        string text;
        int fontSize;
        Color fontColor;

        TextObject() : ScreenObject(), text(""), fontSize(1){};
        TextObject(Vector2 p, Vector2 s, Color c, string t, int f, Color ff) : ScreenObject(p, s, c), text(t), fontSize(f), fontColor(ff){};

        TextObject& operator=(const TextObject&) override;
        void Draw() override{
            DrawRectangle(position.x, position.y, size.x, size.y, col);
            DrawText(c_str(text), position.x+(size.x/2), position.y+(size.y/2), fontSize, fontColor);
        };

        bool IsHovering() const;
}