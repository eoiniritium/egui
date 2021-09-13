#include <iostream>
#include <cstring>
#include "raylib.h"
#include "egui.hpp"

#define SCREENX 1280
#define SCREENY 720



// Banner
    egui::eRectangle banner(0, 0, SCREENX, 50, BLUE);

    // Label
    egui::Label t("Egui", 5, 8, 24, WHITE, RED, 5, 5);

    std::string scroll_attr;
    egui::Label scroll_info("", 1100, 8, 24, WHITE, RED, 5, 5);
    egui::Label showmsgbox_btn_lbl("A button to show a Message Box", 15, 80, 24, BLACK, WHITE, 5, 5);

    // Scroll bar
    egui::v_Scrollbar scroll(SCREENX, 2, 50, SCREENY, 10, 20, LIGHTGRAY, DARKGRAY);

    // Alert
    egui::Messagebox msgbox("Message Box", "This is a Message Box.\nYou can display important information here!", SCREENX, SCREENY, 600, 225, WHITE, BLUE, LIGHTGRAY, 2, 20, 40);

    // Buttons
    void showmsgbox()
    {
        msgbox.toggle_visibility();
    }
    egui::Button button("Show Message Box", 36, 10, 120, 40, 10, WHITE, BLUE, GRAY, showmsgbox);


int main()
{
    egui::initwindow(1280, 720, "Egui", 144);

    int scrolled;

    while(!WindowShouldClose())
    {
        scroll.scroll();
        scrolled = scroll.getscroll();
        scroll_attr = "Scroll: " + std::to_string(scroll.getscroll());
        strcpy(scroll_info.text, egui::to_char_array(scroll_attr));

        //Scroll
        button.scroll(scrolled);
        showmsgbox_btn_lbl.scroll(scrolled);

        BeginDrawing();
            ClearBackground(WHITE);
            

           
            button.draw();
            button.is_click_single();
            showmsgbox_btn_lbl.draw();






            banner.draw();
            t.draw();
            scroll_info.draw();
            scroll.draw();
            msgbox.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}