#pragma once

#include "raylib.h"

#include <string>
#include <vector>
#include <functional>
#include <map>

#include <iostream>

namespace egui {

    template<typename T>
    struct Pair {
        T x, y;
    };

    namespace text {
        struct Text {
            std::string text;
            Font font;
            float fontSize;
            Color fontColour;
        };

        enum Size {
            small = 15,
            normal = 18,
            h6 = 22,
            h5 = 26,
            h4 = 31,
            h3 = 37,
            h2 = 45,
            h1 = 54
        };
    
        class Typeface {
            private:
            std::map<Size, Font> fonts;

            public:
            Typeface(std::string pathToFont, std::vector<Size> sizes) {
                for(Size size: sizes) {
                    Font font = LoadFontEx(pathToFont.c_str(), static_cast<int>(size), nullptr, 250);

                    fonts.insert({size, font});
                }
            }

            Pair<int> MeasureText(std::string text, Size size) {
                Vector2 f = MeasureTextEx(fonts[size], text.c_str(), size, 0);
            }

            Font operator[] (Size size) {
                return fonts[size];
            }
        };
    }
    

    class UIComponent {
        public:
        Pair<int> position, size, scrolled;

        virtual void draw(Pair<int> scrolled) {};
        virtual void onClick() {};
        virtual void onHover() {};

        UIComponent(Pair<int> position, Pair<int> size, Pair<int> scroll = {0, 0}) {
            this->position = position;
            this->size = size;
            this->scrolled = scroll;
        }

        void render(Pair<int> scrolled) {
            this->scrolled = scrolled;
            draw(scrolled);
        }

        bool click() {
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && hover()) {
                onClick();
                return true;
            }

            return false;
        }

        bool hover() {
            Pair<int> mouse;
            mouse.x = GetMouseX();
            mouse.y = GetMouseY();

            bool insideX = mouse.x >= position.x && mouse.x <= position.x + size.x;
            bool insideY = mouse.y >= position.y && mouse.y <= position.y + size.y;
            if (insideX && insideY) {
                onHover();
                return true;
            }

            return false;
        }

        virtual ~UIComponent() {};
    };

    class App  {
        private:
        std::vector<UIComponent *> components;
        Pair<int> scroll;
        Color background;

        public:
        App(std::string windowName, Pair<int> dimensions, const int targetFPS = 60, const Color background = WHITE) {
            InitWindow(dimensions.x, dimensions.y, windowName.c_str());
            SetTargetFPS(targetFPS);

            this->background = background;

            scroll = {0, 0};
        }
        
        void addComponent(UIComponent* component) {
            components.push_back(component);
        }

        void mainloop(std::function<void()> beforeDraw = nullptr, std::function<void()> afterDraw = nullptr) {
            while(!WindowShouldClose()) {
                if(beforeDraw != nullptr) { beforeDraw(); }
                render();
                if(beforeDraw != nullptr) { afterDraw(); }
            }

            exit();
        }

        void render() {
            BeginDrawing();
            ClearBackground(background);
            
            for(int i = components.size()-1; i > -1 ; --i) {
                components[i]->render(scroll);
            }
            EndDrawing();
        }

        void exit() {
            for(auto component: components) {
                delete component;
            }

            CloseWindow();
        }
    };
}