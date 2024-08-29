/*
    * Developed by: github.com/antialberteinstein
    * GUI Library for C++
    * Version: 1.0
    * Last update: 28/08/2024
    * Note:
    *  - This library is only for Windows OS.
    *  - This library is only for console application.
*/

#ifndef EINS_DEV_GUI
#define EINS_DEV_GUI

#include <iostream>  // For cout, cin
#include <string>  // For string
#include <sstream>  // For stringstream
#include <fstream>  // File I/O
#include <windows.h>  // For Windows API
#include <conio.h>  // For _getch()
#include <memory>  // For unique_ptr

using namespace std;

/* The clear command on Windows */
#define CLEAR_COMMAND "cls"

/* The maximum array's size for some default array's size in the
    library user doesn't define */
#define MAX 100

/* Allow showing color in the console, the colorful console isn't good for
    printing monochrome documents. */
#define ENABLE_COLOR 1

/* Function pointer for the action of the menu item or setting. */
typedef void (*func)(void);

/* Clear the console screen. */
void clear_screen();

/* Wait for the user to press Enter. */
void enter_to_continue();

/* Change the current state of the GUI, call attach_running() inside the loop
    to change the value of loop condition to stop the program as needed.
 */
void exit_program();

/* Do nothing, support for assigning an action that user don't know what to do next. */
void do_nothing();

/*
    Attach to the running variable in main program - to stop the program.
    The function should be called in a loop and change the value of running to false when needed.
*/
void attach_running(bool &running);

#define ENABLE_COLOR 1

#define MENU_FRAME_COLOR RED
#define MENU_TEXT_COLOR YELLOW
#define MENU_WIDTH 47

const int MAX_SETTINGS_IN_ONE_LINE = 4;

/*
    * Parameters:
    *  - text: the label of the menu item.
    *  - action: the function pointer that will be called when the item is selected.
*/
struct MenuItem {
    string text;
    func action;

    MenuItem();

    MenuItem(const string& text, func action);
};

/*
    * This is a List ADT made for listing and storing the settings.
    * The settings include the key, the key string, the description and the action.
    * The action is a function pointer.
    * The class also has a method to draw the settings and a method to act on the key.
    * The act method will call the action of the setting that has the key equal to the input.
    * The constructor:
    * - The default constructor will set the max_size to 100 and initialize the arrays.
    * - The constructor with max_size will set the max_size to the input and initialize the arrays.
*/
class Settings {
    private:
    int count;
    int max_size;
    shared_ptr<int[]> cmds;  // The key user input.
    shared_ptr<string[]> cmds_str;  // The key string showed on the screen.
    shared_ptr<string[]> descriptions;  // The description of the key.
    shared_ptr<func[]> actions;  // The action of the key.

    public:
    Settings();
    Settings(int max_size);

    /* Add a new setting. */
    void add(int cmd, const string& cmd_str, const string& description, func action);

    /* Show setting. */
    void draw();

    /* Do job of the setting match to the key input. */
    void act(int& key);
};

/*
    * This is a List ADT made for listing and storing the menu items.
    * The constructor:
    *   - The constructor will set the x, y, count, current, items and settings.
*/
class Menu {
    private:
    int x, y;  // Position of the cursor, important for rendering.
    int count;
    int current;  // The current item.
    unique_ptr<MenuItem[]> items;
    Settings settings;  // The settings for the menu.
    int width, height;

    public:
    Menu(Settings& settings, int width=MENU_WIDTH);

    /* Add a new menu item to menu. */
    void add_item(const string& text, func action);

    /* Show the menu. */
    void show();

    /* Draw the menu. */
    void render();

    /* Update the menu. */
    void update();

    /* Move the cursor up. */
    void move_up();

    /* Move the cursor down. */
    void move_down();

    /* Select the current item. */
    void select();

    /* Height of the menu, height = number of items + 2*/
    int get_height();

    /* Width of the menu. */
    int get_width();

    /* Set position for menu. */
    void set_pos(int x, int y);
};

/*
    * Show the title (text/ASCII Art) for the program.
    * The parameters:
    *  - title: the text will be showed if the file is not exist.
    *  - path: the path to the ASCII Art file.
*/
void draw_title(const string& title, const string& path="", int color=7);

/*
    * Pause the program for a while counted by milliseconds.
*/
void sleep(int);

/*
    * Show the splash screen for the program.
    * The parameters:
    *  - text: the text will be showed if the file is not exist.
    *  - path: the path to the ASCII Art file.
    *  - dev_list: the list of developers.
    *  - dev_count: the number of developers.
*/
void splash_screen(const string &text, const string& path="",
    const string dev_list[] = nullptr, int dev_count = 0, int color=7);

/* Move the cursor to the position (x, y) on the console. */
void set_position(int x, int y);

/* Set the cursor to the position x. */
void set_x(int x);

/* Set the cursor to the position y. */
void set_y(int y);

/* Hiding (False) or Showing (True) the cursor on the console. */
void toggle_cursor(bool);

/* Get the current position of the cursor. */
void get_position(int &x, int &y);

/*
    * Set the color of the text and the background.
    * The parameters:
    *  - color: the color of the text.
    *  - background_color: the color of the background.
    * Note:
    *   - This function will not work if the ENABLE_COLOR is set to 0.
    *   - The constant ENABLE_COLOR is set to 1 by default and in gui.h,
    *       change it to 0 to disable the color.
*/
void set_color(int color, int background_color=0);

/*
    * Reset the color of the text and the background to the default.
    * Note:
    *   - This function will not work if the ENABLE_COLOR is set to 0.
    *   - The constant ENABLE_COLOR is set to 1 by default and in gui.h,
    *       change it to 0 to disable the color.
*/
void reset_color();

#define BLACK 0
#define GRAY 8
#define BLUE 1
#define LIGHT_BLUE 9
#define GREEN 2
#define LIGHT_GREEN 10
#define AQUA 3
#define LIGHT_AQUA 11
#define RED 4
#define LIGHT_RED 12
#define PURPLE 5
#define LIGHT_PURPLE 13
#define YELLOW 6
#define LIGHT_YELLOW 14
#define WHITE 7
#define BRIGHT_WHITE 15

/* Get key from user input. */
int get_key();
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

/* Initialize the GUI library, need to call first to use GUI library. */
void init_gui();

#define CELL_WIDTH 10
#define CELL_HEIGHT 5

/* Enter full screen */
void enter_full_screen();

/*
    * Graphics Matrix:
    * Display the table with the given menu items.
    * The constructor:
    *  - x, y: the position of the matrix.
    *  - n, m: the size of the matrix.
    *  - cell_width, cell_height: the size of the cell, default is 10x5.
*/
// class GraphicsMatrix {
//     private:
//     int x, y;
//     int n, m;
//     int i, j;  // Current position.
//     int cell_width;
//     int cell_height;
//     unique_ptr<MenuItem[]> matrix;  // The flat matrix, but will be showed as a table.

//     public:
//     GraphicsMatrix(int x, int y, int n, int m, int cell_width=CELL_WIDTH, int cell_height=CELL_HEIGHT);

//     /* Set the position of the matrix. */
//     void set_pos(int x, int y);

//     /* Add a new item to the matrix. */
//     void add_item(const string& text, func action);

//     /* Rendering the table. */
//     void render();

//     /* Move the cursor up. */
//     void move_up();

//     /* Move the cursor down. */
//     void move_down();

//     /* Move the cursor left. */
//     void move_left();

//     /* Move the cursor right. */
//     void move_right();

//     /* Select the current item. */
//     void select();

//     /* Update the matrix. */
//     void update();

//     /* Get the height of the matrix. */
//     int get_height();

//     /* Get the width of the matrix. */
//     int get_width();
// }

#endif