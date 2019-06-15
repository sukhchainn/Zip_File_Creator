#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "Text_Box.h"

void menu_icon(int, int, int, int, ALLEGRO_COLOR, int);

#define MAXWIDTH 900
#define MAXHEIGHT 600

int main()
{
    al_init();
    al_init_primitives_addon();
    //al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR);

    ALLEGRO_DISPLAY *display = al_create_display(MAXWIDTH, MAXHEIGHT);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = al_create_timer(2.0/60.0);
    ALLEGRO_COLOR m_color = al_map_rgb(255, 214, 51);
    ALLEGRO_FONT *font = al_load_ttf_font("res/L.ttf", 14, 1);
    LIST_BOX list_box = bt_create_list_box(75, 75, 800, 500, al_map_rgb(12, 83, 95), al_map_rgb(155, 155, 155), al_map_rgb(255, 255, 70), al_map_rgb(255, 255, 255));
    //ALLEGRO_BITMAP *background = al_load_bitmap("res/background.jpg");


    int x=0, sc_y=0, sc_pointed_y, sc_pointed_y_trigger=0, main_loop = true, menu = 0, scr_prev_pos=0, scroller=1;
    int width=50, height=50, place_x=25, place_y=25, animate = 0;
    //enum {};

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while(main_loop)
    {

        //if(al_is_event_queue_empty(queue))
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            main_loop = false;

        else if(event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 77, 77)); //rgb(153,50,204)

        //al_draw_scaled_bitmap(background, 0, 0, 4896, 3264, 0, 0, 800, 600, 0);
        al_draw_rounded_rectangle(400-100, 300-20, 400+100, 300+20, 20, 20, al_map_rgb(70, 60, 100), 2);
        al_draw_filled_rectangle(0, 0, 50, 50, m_color);
        al_draw_filled_rectangle(0, 50, 50, MAXHEIGHT, al_map_rgb(255, 214, 51)); //rgb(218, 112, 214) rgb(255, 214, 51) al_map_rgb(230, 46, 0)
        al_draw_line(50, 0, 50, MAXHEIGHT, al_map_rgb(0, 0, 0), 1);
        menu_icon(50, 50, 25, 25, al_map_rgb(0, 0, 0), animate);
        bt_draw_list_box(list_box); //list_box(sc_y);

            if(menu)
            {
                al_draw_filled_rectangle(50, 0, MAXWIDTH, 50, al_map_rgb(22, 88, 110));
            }

        al_flip_display();
        al_rest(0.02);
        }

        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
                if(event.mouse.x < 50 && event.mouse.y < 50)
                    m_color = al_map_rgb(140, 152, 63);
                else
                    m_color = al_map_rgb(255, 214, 51);
        }

        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            //scr_prev_pos = event.mouse.y;


            if(event.mouse.x >= (place_x-(width/2))
            && event.mouse.x <= (place_x+(width/2))
            && event.mouse.y >= (place_y-(height/2))
            && event.mouse.y <= (place_y+(height/2)))
            {
                if(event.mouse.button == 1)
                {
                    (5 == animate) ? (animate = 0) : (animate = 5);
                    menu = !menu;
                }
            }

        }

        if(event.mouse.x >= 753 && event.mouse.x <= 761 && event.mouse.y >= 100+sc_y && event.mouse.y <= 200+sc_y)
            {

                if(event.mouse.button == 1)
                {
                    scroller = 1;

                    if(sc_pointed_y_trigger == 1)
                    {
                        sc_pointed_y = event.mouse.y;
                        sc_pointed_y_trigger = 0;
                    }
                }

                if(scroller)
                {
                    //if((event.mouse.y - 150) < 550 && (event.mouse.y - 150) > 100)
                        sc_y = event.mouse.y - 150;
                }
            }

        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            scroller = 0;
            sc_pointed_y_trigger = 1;
            //scr_prev_pos = event.mouse.y;
        }

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE :
                    exit(1);
                    break;
            }
        }

    list_box = bt_list_box_listener(event, list_box);
    }


    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}

void menu_icon(int width, int height, int place_x, int place_y, ALLEGRO_COLOR colorU, int animate)
{
    al_draw_line(place_x-(width/2)+width/4 + animate, place_y-(height/2)+height/3, place_x-(width/2)+width-(width/4) + animate, place_y-(height/2)+height/3, colorU, 5);
    al_draw_line(place_x-(width/2)+width/4 - animate, place_y-(height/2)+(height/2), place_x-(width/2)+width-(width/4) - animate, place_y-(height/2)+(height/2), colorU, 5);
    al_draw_line(place_x-(width/2)+width/4 + animate, place_y-(height/2)+height-(height/3), place_x-(width/2)+width-(width/4) + animate, place_y-(height/2)+height-(height/3), colorU, 5);
}



