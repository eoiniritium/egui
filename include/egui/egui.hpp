#pragma once

#include "raylib.h"

#include <string>
#include <vector>
#include <functional>
#include <map>

#include <iostream>

namespace egui {

    typedef std::function<void()> onEventCallback;

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
            float spacing = 1.0f;
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
                    Font font = LoadFontEx(pathToFont.c_str(), static_cast<int>(size), 0, 0);
                    fonts.insert({size, font});
                }
            }

            Pair<int> MeasureText(std::string text, Size size) {
                Vector2 f = MeasureTextEx(fonts[size], text.c_str(), size, 0);
                Pair<int> ret;
                ret.x = static_cast<int>(f.x);
                ret.y = static_cast<int>(f.y);
                return ret;
            }

            Font operator[] (Size size) {
                return fonts[size];
            }
        };

        void drawText(Text text, Pair<int> position) {
            Vector2 pos;
            pos.x = static_cast<float>(position.x);
            pos.y = static_cast<float>(position.y);
            DrawTextEx(text.font, text.text.c_str(), pos, text.fontSize, text.spacing, text.fontColour);
        }
    }

    class UIComponent {
        public:
        Pair<int> position, size, scrolled;

        onEventCallback onClickFunction;
        onEventCallback onHoverFunction;
        onEventCallback onPressFunction;

        virtual void draw(Pair<int> scrolled) {};
        virtual void onClick(onEventCallback onClickFunction) { if(onClickFunction) onClickFunction(); };
        virtual void onHover(onEventCallback onClickFunction) { if(onHoverFunction) onHoverFunction(); };
        virtual void onPress(onEventCallback onPressFunction) { if(onPressFunction) onPressFunction(); };
        virtual ~UIComponent() {};

        UIComponent(
            Pair<int> position,
            Pair<int> size,
            onEventCallback onClick = nullptr,
            onEventCallback onHover = nullptr,
            onEventCallback onPress = nullptr,
            Pair<int> scroll = {0, 0}
        ) {
            this->position = position;
            this->size = size;
            this->scrolled = scroll;

            this->onClickFunction = onClick;
            this->onHoverFunction = onHover;
            this->onPressFunction = onPress;
        }

        void render(Pair<int> scrolled) {
            this->scrolled = scrolled;
            draw(scrolled);
        }

        bool click() {
            if(hover() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                onClick(onClickFunction);
                return true;
            }

            return false;
        }

        bool pressed() {
            if(hover() && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                onPress(onPressFunction);
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
                onHover(onHoverFunction);
                return true;
            }

            return false;
        }
    };

    class App  {
        private:
        std::vector<UIComponent *> components;
        Scrollbar *verticalScrollBar, *horizontalScrollBar;
        Pair<int> scroll;
        Color background;

        public:
        struct Options {
            std::string windowName;
            Pair<int> dimensions;
            Color background = WHITE;
            bool verticalScrollbar = false;
            bool horizontalScrollbar = false;
            int targetFPS = 60;
        };

        App(App::Options options) {
            InitWindow(options.dimensions.x, options.dimensions.y, options.windowName.c_str());
            SetTargetFPS(options.targetFPS);

            this->background = options.background;
            verticalScrollBar = nullptr;
            horizontalScrollBar = nullptr;
            if(options.verticalScrollbar) {
                verticalScrollBar = new Scrollbar();
            }

            scroll = {0, 0};
        }

        void addComponent(UIComponent* component) {
            components.push_back(component);
        }

        void mainloop(std::function<void()> beforeDraw = nullptr, std::function<void()> afterDraw = nullptr) {
            while(!WindowShouldClose()) {
                if(beforeDraw != nullptr) { beforeDraw(); }
                render();
                handleClick();
                handlePress();
                if(beforeDraw != nullptr) { afterDraw(); }
            }

            exit();
        }

        void render() {
            BeginDrawing();
            ClearBackground(background);

            for(auto component: components) {
                component->render(scroll);
            }

            EndDrawing();
        }

        void handleClick() {
            for(int i = components.size() - 1; i >= 0; --i) {
                if(components[i]->click()) { break; }
            }
        }

        void handlePress() {
            for(int i = components.size() - 1; i >= 0; --i) {
                if(components[i]->pressed()) { break; }
            }
        }

        void exit() {
            CloseWindow();

            delete verticalScrollBar;
            delete horizontalScrollBar;
            for(auto component: components) {
                delete component;
            }
        }
    };
}