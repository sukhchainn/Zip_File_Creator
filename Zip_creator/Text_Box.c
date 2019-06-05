#include "Text_Box.h"

// To be replaced by properly designed functions
void list_box(int y)
{
    al_draw_filled_rectangle(75, 75, 775, 575, al_map_rgb(12, 83, 95));// rgb(51, 102, 153)

    for(int i=0; i < 475; i+=25)
    {
        al_draw_line(100, 100+i, 725, 100+i, al_map_rgb(155, 155, 155), 1); //rgb(182, 182, 182)
     //   al_draw_line(100+i, 100, 100+i, 550, al_map_rgb(255, 255, 255), 1);
    }

    //al_draw_filled_rectangle(750, 75, 775, 575, al_map_rgb(51, 102, 153));
    al_draw_line(757, 100, 757, 550, al_map_rgb(255, 255, 255), 1);
    al_draw_filled_rounded_rectangle(754, 100+y, 760, 200+y, 2, 2, al_map_rgb(255, 255, 70));

}

//LIST_BOX functions
/////////////////////////////////////////////////////////////////////////////////////////////

// Initializes the LIST_BOX struct
LIST_BOX bt_create_list_box(int x,  int y, int width, int height, ALLEGRO_COLOR background, ALLEGRO_COLOR seperator_line)
{
    LIST_BOX list_box;

    list_box.x = x;
    list_box.y = y;
    list_box.width = width;
    list_box.height = height;
    list_box.background = background;
    list_box.seperator_line = seperator_line;

    return list_box;
}

// To be called while rendering
void bt_draw_list_box(LIST_BOX box)
{
    int bg_width_pos = box.x + box.width;
    int bg_height_pos = box.y + box.height;

    al_draw_filled_rectangle(box.x, box.y, bg_width_pos, bg_height_pos, box.background);

    int loop = box.width - 25;
    for(int i=0; i < loop; i+=25)
    {
        al_draw_line(box.x+25, box.y+25+i, bg_width_pos-50, box.y+25+i, box.seperator_line, 1); //rgb(182, 182, 182)

    }


}

// Makes changes in the LIST_BOX, to be called in the logical computational part
LIST_BOX bt_list_box_listener(ALLEGRO_EVENT event, LIST_BOX box)
{

}

//LIST_BOX functions
/////////////////////////////////////////////////////////////////////////////////////////////
LIST_BOX create_scroller(int x, int y, int width, int height, ALLEGRO_COLOR color, ALLEGRO_COLOR tail_color, ALLEGRO_COLOR hover_color, ALLEGRO_COLOR drag_color)
{
    SCROLLER scroll;

    scroll.x = x;
    scroll.y = y;
    scroll.width = width;
    scroll.height = height;
    scroll.color = color;
    scroll.tail_color = tail_color;

    scroll.hover_color = hover_color;
    scroll.drag_color = darg_color;

    return scroll;
}


// The function to draw scroller in render mode
void draw_scroller(LIST_BOX box)
{
    al_draw_line(757, 100, 757, 550, al_map_rgb(255, 255, 255), 1);
    al_draw_filled_rounded_rectangle(754, 100+y, 760, 200+y, 2, 2, al_map_rgb(255, 255, 70));

}

// Listen to the ALLEGRO_EVENT (for scroller)
LIST_BOX scroller_listener(ALLEGRO_EVENT event, LIST_BOX box);

void On_click_scroller(SCROLLER scroll);

void On_drag_scroller(SCROLLER scroll);

void On_release_scroller(SCROLLER scroll);
