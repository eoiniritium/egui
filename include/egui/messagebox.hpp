#pragma once
#include "raylib.h"
#include "egui.hpp"
#include <string>

namespace egui {
    class Messagebox {
        public:
        Messagebox(std::string title, std::string message, Pair<int> screen, int width, int height, Color foreground, Color background, Color border_colour = BLACK, int border_thickness = 0, int padding_top = 1, int padding_left = 1) {
            pt = padding_top;
            pl = padding_left;

            sw = screen.x;
            sh = screen.y;

            w = width;
            h = height;

            fg = foreground;
            bg = background;
            out = border_colour;
            out_thicc = border_thickness;

         // Rectangle lines
            lines.x = sw/2 - w/2;
            lines.y = sh/2 - h/2;
            lines.width = w;
            lines.height = h;

         // Rectangle bttn_lines
            bttn_lines.x = lines.x + w - btn_w - btn_padding;
            bttn_lines.y = lines.y + h - btn_h - btn_padding;
            bttn_lines.width = btn_w;
            bttn_lines.height = btn_h;
        }

        void toggle_visibility()
        {
            flag = !flag;
        }

        int hover()
        {
            int x, y;
            x = GetMouseX();
            y = GetMouseY();

            if(x >= bttn_lines.x && x <= bttn_lines.x + bttn_lines.width && y >= bttn_lines.y && y <= bttn_lines.y + bttn_lines.height)
            {
                return 1;
            }
            return 0;
        }

        void set_text(std::string title, std::string message) {
            this->title = title;
            this->message = message;
        }

        void draw()
        {
            if(flag) {
                DrawRectangle(sw/2 - w/2, sh/2 - h/2, w, h, bg);

                DrawRectangleLinesEx(lines, out_thicc, out);
                DrawText(title.c_str(), lines.x + pl, lines.y + pt, title_fs, fg);
                DrawText(message.c_str(), lines.x + pl, lines.y + title_fs + pt*3, message_fs, fg);

                // Ok button
                DrawRectangle(bttn_lines.x, bttn_lines.y, bttn_lines.width, bttn_lines.height, fg);
                DrawRectangleLinesEx(bttn_lines, out_thicc, out);
                DrawText(btn_text.c_str(), bttn_lines.x + bttn_lines.width/2 - MeasureText(btn_text.c_str(), message_fs)/2, bttn_lines.y + bttn_lines.height/2 - message_fs/2, message_fs, bg);

                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hover())
                    toggle_visibility();
            }
        }

        const int title_fs = 36;
        const int message_fs = 21;

        const int btn_w = 100;
        const int btn_h = 40;
        const int btn_padding = 5;
        const std::string btn_text = "OK";

        std::string title, message;
        int pt, pl, sw, sh, w, h, out_thicc;
        int flag = 0;

        Color fg, bg, out;

        Rectangle lines;
        Rectangle bttn_lines;
    };
}