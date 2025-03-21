#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include "raylib.h"
#define TEXT_BUFFER 100000 // 100,000  bytes long
#define BCKSPC 259

namespace egui
{
    class UIComponent {
        public:
        virtual void draw(bool );
    };


    struct screen {
        int sw, sh;
    };

    void initwindow(const int x, const int y, std::string windowName, const int targetfps)
    {
        InitWindow(x, y, &windowName[0]);
        SetTargetFPS(targetfps);
    }

    char *to_char_array(std::string string)
    {
        return &string[0];
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


    class Oblong // rectangle
    {   public:
        Oblong(int pos_x, int pos_y, int width_x, int width_y, Color colour)
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

        int x, y, wx, wy;
        Color col;

        private:
        int scrolled;
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

            if((mx >= x) && (mx <= x + size + pl*2) && (my >= y + scrolled) && (my <= y + pt*2 + fs + scrolled))
            {
                return 1;
            }
            return 0;
        }

        void (*fptr)();
        int scrolled;
    };

    

    
    class barGraph
    {   public:
        barGraph(int* data, int posx, int posy, int width, int height, int num_bars, int scale_min, int scale_max, Color foreground, Color background, Color outline, int outline_thickness = 0, int bar_padding = 5)
        {
            scrolled = 0;

            fg = foreground;
            bg = background;
            outl = outline;

            x = posx;
            y = posy;
            h = height;
            w = width;
            nb = num_bars;
            smin = scale_min;
            smax = scale_max;
            out_w = outline_thickness;

            bar_p = bar_padding;
            bar_w = (w - (bar_p * nb + 1) - out_w * 2)/nb; // calculate bar width

            d = data;

            int amrediad = smax - smin;
            int available = h - (out_w * 2) - bar_p;
            norm = available / amrediad;
        }

        void draw()
        {
            out.x = x;
            out.y = y + scrolled;
            out.width = w;
            out.height = h;

            DrawRectangle(x, out.y, w, h, bg);
            DrawRectangleLinesEx(out, out_w, outl);

            int baseline = out.y + h - bar_p; // Starting location of all bars on y axis
            int c_pixel = x + bar_p + out_w; // Get position of bar

            for(int i = 0; i < nb; ++i)
            {
                DrawRectangle(c_pixel, baseline - (d[i] * norm), bar_w, d[i] * norm, fg);
                c_pixel += bar_w + bar_p;
            }
        }

        void update_data(int *data, int min, int max)
        {
            int amrediad = max - min;
            int available = h - (out_w * 2) - bar_p;
            norm = available / amrediad;

            d = data;
        }

        void scroll(int amount)
        {
            scrolled = -amount;
        }

        int x, y, h, w, nb, smin, smax, scrolled, out_w, norm;
        Color fg, bg, outl;
        Rectangle out;

        int bar_w, bar_p;
        int* d;
    };
}