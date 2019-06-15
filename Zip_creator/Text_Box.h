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

    // To be manipulated by the internal functions
    int x1, y1, x2, y2;
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
LIST_BOX bt_create_list_box(int x,  int y, int width, int height, ALLEGRO_COLOR background, ALLEGRO_COLOR seperator_line
                            , ALLEGRO_COLOR scroller_color, ALLEGRO_COLOR tail_color);

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
SCROLLER create_scroller(int x, int y, int width, int height
                         , ALLEGRO_COLOR tail_color, ALLEGRO_COLOR color);

// The function to draw scroller in render mode
void draw_scroller(SCROLLER scroll);

// Listen to the ALLEGRO_EVENT (for scroller)
SCROLLER scroller_listener(ALLEGRO_EVENT event, SCROLLER scroll);


void On_click_scroller(ALLEGRO_EVENT event, SCROLLER **scroll);

void On_drag_scroller(ALLEGRO_EVENT event, SCROLLER **scroll);

void On_release_scroller(ALLEGRO_EVENT event, SCROLLER **scroll);
////////////////////////////////////////////
//

