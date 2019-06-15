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
    al_draw_line(763, 100, 763, 550, al_map_rgb(255, 255, 255), 1); //757, 100, 757, 550
    al_draw_filled_rounded_rectangle(760, 100+y, 765, 200+y, 2, 2, al_map_rgb(255, 255, 70));

}

//LIST_BOX functions
/////////////////////////////////////////////////////////////////////////////////////////////

// Initializes the LIST_BOX struct
LIST_BOX bt_create_list_box(int x,  int y, int width, int height, ALLEGRO_COLOR background, ALLEGRO_COLOR seperator_line
                            , ALLEGRO_COLOR scroller_color, ALLEGRO_COLOR tail_color)
{
    LIST_BOX list_box;

    list_box.x = x;
    list_box.y = y;
    list_box.width = width;
    list_box.height = height;
    list_box.background = background;
    list_box.seperator_line = seperator_line;

    list_box.scroller = create_scroller(list_box.width+50, list_box.y, 50, list_box.height, tail_color, scroller_color);

    return list_box;
}

// To be called while rendering
void bt_draw_list_box(LIST_BOX box)
{
    // Taking measures for the List Box's x2 y2
    int bg_width_pos = box.x + box.width;
    int bg_height_pos = box.y + box.height;

    // Drawing background
    al_draw_filled_rectangle(box.x, box.y, bg_width_pos, bg_height_pos, box.background);

    // I Don't remember why did I do that
    int loop = box.height - 25;
    // To draw separator lines
    for(int i=0; i < loop; i+=25)
    {
        al_draw_line(box.x+25, box.y+25+i, bg_width_pos-50, box.y+25+i, box.seperator_line, 1); //rgb(182, 182, 182)

    }

    // Drawing actual scroller
    draw_scroller(box.scroller);
}

// Makes changes in the LIST_BOX, to be called in the logical computational part
LIST_BOX bt_list_box_listener(ALLEGRO_EVENT event, LIST_BOX box)
{
    box.scroller = scroller_listener(event, box.scroller);
    return box;
}

//LIST_BOX functions
/////////////////////////////////////////////////////////////////////////////////////////////
SCROLLER create_scroller(int x, int y, int width, int height
                         , ALLEGRO_COLOR tail_color, ALLEGRO_COLOR color)
{
    SCROLLER scroll;

    scroll.x = x;
    scroll.y = y;
    scroll.width = width;
    scroll.height = height;
    scroll.color = color;
    scroll.tail_color = tail_color;
    scroll.flag = 0;
    scroll.from_y = 0;
    scroll.ordinate = 0;

    // Scroller button information
    scroll.x1 = scroll.x + 10;
    scroll.y1 = scroll.y + 25;
    scroll.x2 = scroll.x + 15;
    scroll.y2 = scroll.y + 100;

    return scroll;
}


// The function to draw scroller in render mode
void draw_scroller(SCROLLER scroll)
{

    al_draw_line(scroll.x + 13, scroll.y + 25, scroll.x + 13, scroll.height + scroll.y - 25
                 , scroll.tail_color, 1);
    al_draw_filled_rounded_rectangle(scroll.x1, scroll.y1+scroll.ordinate, scroll.x2, scroll.y2+scroll.ordinate
                                     , 2, 2, scroll.color);

}

// Listen to the ALLEGRO_EVENT (for scroller)
SCROLLER scroller_listener(ALLEGRO_EVENT event, SCROLLER scroll)
{

    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.x > scroll.x1 && event.mouse.x < scroll.x2 &&
           event.mouse.y > scroll.y1 && event.mouse.y < scroll.y2 && scroll.flag == 0)
           {
            scroll.flag = 1;
            scroll.from_y = event.mouse.y;
           }
    }

    if(scroll.flag == 1)
        scroll.ordinate = event.mouse.y - scroll.from_y;

    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        scroll.flag = 0;


    return scroll;
}
