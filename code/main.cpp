#include <iostream>
#include <cstring>
#include "raylib.h"
#include "egui.hpp"
#include <time.h>
#include <stdlib.h>

#define SCREENX 1280
#define SCREENY 720



// Banner
    egui::eRectangle banner(0, 0, SCREENX, 50, BLUE);

    // Label
    egui::Label t("Egui showcase", 5, 8, 24, WHITE, RED, 5, 5);

    std::string scroll_attr;
    egui::Label scroll_info("", 1100, 8, 24, WHITE, RED, 5, 5);
    egui::Label showmsgbox_btn_lbl("A button to show a Message Box", 15, 80, 24, BLACK, WHITE, 5, 5);

    // Scroll bar
    egui::v_Scrollbar scroll(SCREENX, 5, 50, SCREENY, 50, 40, LIGHTGRAY, DARKGRAY);

    // Alert
    egui::Messagebox msgbox("Message Box", "This is a Message Box.\nYou can display important information here!", SCREENX, SCREENY, 600, 225, WHITE, BLUE, LIGHTGRAY, 2, 20, 40);
    egui::Messagebox entry_messagebox("Entry", "", SCREENX, SCREENY, 600, 225, WHITE, BLUE, LIGHTGRAY, 2, 20, 40);

    // Entry
    egui::Entry entry("Type here", 18, 900, 70, 321, 32, 20, 10, BLACK, WHITE, BLUE, 2);

    // Graph
    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    egui::barGraph g(data, 8, 200, 1260, 500, 10, 0, 9, BLACK, LIGHTGRAY, BLUE, 5);


    // Buttons
    void showmsgbox()
    {
        msgbox.toggle_visibility();
    }
    void showmsgbox_entry()
    {
        entry_messagebox.set_text("Entry", "Text: " + entry.get_text());
        entry_messagebox.toggle_visibility();
    }

    egui::Button button("Show Message Box", 36, 10, 120, 40, 10, WHITE, BLUE, GRAY, showmsgbox);
    egui::Button btn_Entry("Get Text", 36, 900, 120, 100, 10, WHITE, BLUE, GRAY, showmsgbox_entry);


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
        entry.scroll(scrolled);
        btn_Entry.scroll(scrolled);
        g.scroll(scrolled);

        BeginDrawing();
            ClearBackground(WHITE);
            

            btn_Entry.draw();
            btn_Entry.is_click_single();
            button.draw();
            button.is_click_single();
            showmsgbox_btn_lbl.draw();
            entry.draw();
            g.draw();





            // Top bar
            banner.draw();
            t.draw();
            scroll_info.draw();
            scroll.draw();

            // MessageBox
            msgbox.draw();
            entry_messagebox.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}