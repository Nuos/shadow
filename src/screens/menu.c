#include "menu.h"

HSV background_color;

void play_game() {
    set_screen(GLOBALS.screen_game);
}

static void create() {
    menu_data.buttons = list_init();
    list_add(menu_data.buttons, (list_data_t)(void*)button_create("Play", 100, 100, play_game));
    list_add(menu_data.buttons, (list_data_t)(void*)button_create_font("Create map", 100, 160, NULL, font_bold_oblique));
    background_color = (HSV) { 0, 100, 100 };
    printf("created menu\n");
}

static void destroy() {
    printf("Cleaning up menu screen...\n");
    list_free_all(menu_data.buttons);
}

static void show() {

}

static void hide() {

}

static void render() {
    
    // background color
    background_color.h++;
    RGB tmp = HsvToRgb(background_color);
    glClearColor((float)tmp.r / 255, (float)tmp.g / 255, (float)tmp.b / 255, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // draw buttons
    list_item_t* button = list_get_first_item(menu_data.buttons);
    while (button != NULL) {
        button_draw(button->data.data);
        button = button->next;
    }
    buffer_end();
    
    draw_text(100, 300, "Testing Text _ <- underscore", (RGBA) {0, 255, 0, 255});
    
    draw_texture(font_bold_oblique->texture, (RGBA) {0, 0, 255, 255}, 100, 400, 256, 256);
    
    draw_texture_region(font_bold_oblique->texture, (RGBA) {255, 0, 255, 255}, 400, 250, 100, 100, 0, 0, 100, 100);
}

static void key_callback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        running = false;
    }
}

static void mouse_callback(int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        list_item_t* button = list_get_first_item(menu_data.buttons);
        while (button != NULL) {
            button_click((button_t*) (button->data.data));
            button = button->next;
        }
    }
}

screen_t* screen_menu() {
    screen_t* screen = malloc(sizeof (screen_t));
    screen->create          = &create;
    screen->destroy         = &destroy;
    screen->show            = &show;
    screen->hide            = &hide;
    screen->render          = &render;
    screen->key_callback    = &key_callback;
    screen->mouse_callback  = &mouse_callback;
    create();
    return screen;
}
