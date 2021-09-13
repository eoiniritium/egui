// Wrapper header

#ifndef EGUI
#define EGUI

#include <iostream>
#include <string>
#include <cstring>
#include "raylib.h"
#define TEXT_BUFFER 100000 // 100,000  bytes long

namespace egui
{
    void initwindow(const int x, const int y, std::string windowName, const int targetfps)
    {
        InitWindow(x, y, &windowName[0]);
        SetTargetFPS(targetfps);
    }

    char *to_char_array(std::string string)
    {
        return &string[0];
    }

    void string_cpp_to_c(char* dest, std::string source)
    {
        strcpy_s(dest, TEXT_BUFFER, to_char_array(source));
    }

    class Label
    {   public:
        Label(std::string txt, int x, int y, int fontsize, Color font_colour, Color background_colour, int padding_tb, int padding_lr){
            strcpy(text, to_char_array(txt));
            posx = x;
            posy = y;
            fntsize = fontsize;
            fg = font_colour;
            bg = background_colour;
            p_tb = padding_tb;
            p_lr = padding_lr;

            rectwidth  = (p_lr * 2) + MeasureText(text, fntsize);
            rectheight = (p_tb * 2) + fntsize;

            tmiddle =  rectwidth / 2;
            smiddle = rectheight / 2;

            scrolled = 0;
        }

        void draw()
        {
            DrawRectangle(posx, posy + scrolled, (p_lr * 2) + MeasureText(text, fntsize), (p_tb * 2) + fntsize, bg);
            DrawText(text, posx + p_lr, posy + p_tb + scrolled, fntsize, fg);
        }

        int middle_width_x()
        {
            return tmiddle;
        }

        int middle_height_y()
        {
            return smiddle;
        }

        void scroll(int amount)
        {
            scrolled = -amount;
        }

        int posx, posy;
        char text[TEXT_BUFFER];
        
        private:
        int fntsize;
        Color fg;
        Color bg;
        int p_tb, p_lr;
        int rectwidth, rectheight;
        int tmiddle, smiddle;
        int scrolled;
    };


    class eRectangle
    {   public:
        eRectangle(int pos_x, int pos_y, int width_x, int width_y, Color colour)
        {
            x   = pos_x;
            y   = pos_y;
            col = colour;
            wx  = width_x;
            wy  = width_y;
            scrolled = 0;
        }

        void draw()
        {
            DrawRectangle(x, y + scrolled, x+wx, y+wy, col);
        }

        void scroll(int amount)
        {
            scrolled = -amount;
        }

        private:
        int x, y, wx, wy, scrolled;
        Color col;
    };


    class v_Scrollbar
    {   public:
        v_Scrollbar(int screenwidth, int width, int starty, int endy, int scrollpoints, int scroll_multiplier, Color bar_colour, Color trackbar_colour)
        {
            sw = screenwidth;
            w = width;
            sy = starty;
            ey = endy;
            
            pos = 0;

            bc = bar_colour;
            tc = trackbar_colour;

            sm = scroll_multiplier;
            sp = scrollpoints;

            float height = endy-starty;
            bh = height / (scrollpoints+1);
            spc = 0;
        }

        void draw()
        {
            DrawRectangle(sw-w, sy, w, ey-sy, bc);
            DrawRectangle(sw-w, sy+pos, w, bh, tc);
        }

        void scroll()
        {
            int sc;
            float scroll_wheel = GetMouseWheelMove();

            if(scroll_wheel < 0)
            {
                sc = -1;
            } 
            else if( scroll_wheel > 0)
            {
                sc = 1;
            } 
            else
            {
                sc = 0;
            }

            if(sc == -1) // Scroll down
            {
                if(spc < sp) ++spc; // From 0 = n+1
            }
            else if(sc == 1) // Scroll up
            {
                if(spc > 0) --spc;
            }

            pos = spc * bh;
        }

        int getscroll()
        {
            return sm * spc;
        }

        private:
        int sw, w, sy, ey, sp, pos, sm, spc;
        float bh;
        Color bc, tc;
    };


    class Button
    {   public:
        Button(std::string txt, int fontsize, int posx, int posy, int paddingl, int paddingt, Color foreground, Color background, Color onhover, void(*on_click_function)())
        {
            strcpy(text, to_char_array(txt));
            fs = fontsize;
            x = posx;
            y = posy;
            pl = paddingl;
            pt = paddingt;
            fg = foreground;
            bg = background;
            hvr = onhover;
            fptr = on_click_function;
            scrolled = 0;
        }

        void draw()
        {
            int size = MeasureText(text, fs);
            if(hover())
                DrawRectangle(x, y + scrolled, size + pl * 2, fs + pt * 2, hvr);
            else
                DrawRectangle(x, y + scrolled, size + pl * 2, fs + pt * 2, bg);
            DrawText(text, x+pl, y+pt + scrolled, fs, fg);
        }

        void scroll(int amount)
        {
            scrolled = -amount;
        }

        void is_click_single()
        {
            if(hover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                fptr();
        }

        void is_click_multiple()
        {
            if(hover() && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                fptr();
        }


        char text[TEXT_BUFFER];
        int x, y, fs, pl, pt;
        Color fg, bg, hvr;

        private:
        int hover()
        {
            int size = MeasureText(text, fs);
            int mx = GetMouseX();
            int my = GetMouseY();

            if((mx >= x) && (mx <= x + size + pl*2) && (my >= y) && (my <= y + pt*2 + fs))
            {
                return 1;
            }
            return 0;
        }

        void (*fptr)();
        int scrolled;
    };

    class Messagebox
    {   public:
        Messagebox(std::string title, std::string message, int screenwidth, int screenheight, int width, int height, Color foreground, Color background, Color outline = BLACK, int outline_thickness = 0, int padding_top = 1, int padding_left = 1)
        {
            string_cpp_to_c(t, title);
            string_cpp_to_c(m, message);


            pt = padding_top;
            pl = padding_left;

            sw = screenwidth;
            sh = screenheight;

            w = width;
            h = height;

            fg = foreground;
            bg = background;
            out = outline;
            out_thicc = outline_thickness;

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

        void draw()
        {
            if(flag)    
            {
                DrawRectangle(sw/2 - w/2, sh/2 - h/2, w, h, bg);
                
                DrawRectangleLinesEx(lines, out_thicc, out);
                DrawText(t, lines.x + pl, lines.y + pt, title_fs, fg);
                DrawText(m, lines.x + pl, lines.y + title_fs + pt*3, message_fs, fg);

                // Ok button
                DrawRectangle(bttn_lines.x, bttn_lines.y, bttn_lines.width, bttn_lines.height, fg);
                DrawRectangleLinesEx(bttn_lines, out_thicc, out);
                DrawText(btn_text, bttn_lines.x + bttn_lines.width/2 - MeasureText(btn_text, message_fs)/2, bttn_lines.y + bttn_lines.height/2 - message_fs/2, message_fs, bg);
                
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hover())
                    toggle_visibility(); // flag =! flag;
            }
        }

        const int title_fs = 36;
        const int message_fs = 21;

        const int btn_w = 100;
        const int btn_h = 40;
        const int btn_padding = 5;
        const char btn_text[3] = "OK";

        char t[TEXT_BUFFER];
        char m[TEXT_BUFFER];
        int pt, pl, sw, sh, w, h, out_thicc;
        int flag = 0;

        Color fg, bg, out;

        Rectangle lines;
        Rectangle bttn_lines;
    };










}

#endif