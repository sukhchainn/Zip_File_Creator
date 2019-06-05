#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


// Structure for scroller (subset of List Box)
typedef struct SCROLLER
{
    int x, y;
    int width, height;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR tail_color;
    ALLEGRO_COLOR hover_color;
    ALLEGRO_COLOR drag_color;
    char flag;
    long from_y;
    int ordinate;

} SCROLLER;

typedef struct LIST_BOX
{
    int x, y;
    int width, height;
    ALLEGRO_COLOR background;
    ALLEGRO_COLOR seperator_line;
    SCROLLER scroller;
} LIST_BOX;



///////////////////////////////////////////
//                                       //
//               LIST_BOX                //
//                                       //
///////////////////////////////////////////

// The function to draw the whole List Box
void list_box(int y);

// The function to Initialize LIST_BOX struct
LIST_BOX bt_create_list_box(int x,  int y, int width, int height, ALLEGRO_COLOR background, ALLEGRO_COLOR seperator_line);

// The function to draw List Box in render mode
void bt_draw_list_box(LIST_BOX box);

// Listen to the ALLEGRO_EVENT (for List Box)
LIST_BOX bt_list_box_listener(ALLEGRO_EVENT event, LIST_BOX box);

////////////////////////////////////////////



///////////////////////////////////////////
//                                       //
//               SCROLLER                //
//                                       //
///////////////////////////////////////////

// The function to Initialize SCROLLER struct
LIST_BOX create_scroller(int x, int y, int width, int height, ALLEGRO_COLOR color, ALLEGRO_COLOR tail_color, ALLEGRO_COLOR hover_color, ALLEGRO_COLOR drag_color);

// The function to draw scroller in render mode
void draw_scroller(LIST_BOX box);

// Listen to the ALLEGRO_EVENT (for scroller)
LIST_BOX scroller_listener(ALLEGRO_EVENT event, LIST_BOX box);

void On_click_scroller(SCROLLER scroll);

void On_drag_scroller(SCROLLER scroll);

void On_release_scroller(SCROLLER scroll);
////////////////////////////////////////////


