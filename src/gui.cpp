#include "gui.h"

bool special_00124 = true;  // Decide program state.

int Menu::get_height() {
    return count + 2;
}

int Menu::get_width() {
    return width;
}

void Menu::set_pos(int x, int y) {
    this->x = x;
    this->y = y;
}

MenuItem::MenuItem() : text(""), action(do_nothing) {}

MenuItem::MenuItem(const string& text, func action) : text(text), action(action) {}

Menu::Menu(Settings& settings, int width) : count(0), current(0),
        settings(settings), items(make_unique<MenuItem[]>(MAX)),
        width(width) {}

void draw_title(const string& title, const string& path, int color) {
    ifstream file(path);
    int x, y;
    get_position(x, y);

    if (file.good()) {
        // If file is exist, read the file and show the content.
        set_color(color);
        while (!file.eof()) {
            string line;
            getline(file, line);
            set_position(x, y++);
            cout << line;
        }
        reset_color();
    }
    else {
        // If file is not exist, show the title (string).
        cout << title << endl;
    }
    cout << endl;
}

void Menu::render() {
    // Move the cursor to right position.
    set_position(this->x, this->y);
    int temp;

    int noo = count;  // Number of options.
    const int MENU_HEIGHT = noo + 2;

    // Draw the top border.
    cout << "╔";
    for (int i = 0; i < MENU_WIDTH - 2; i++) {
        cout << "═";
    }
    int end_x = 0;  // Position of the right border.
    get_position(end_x, temp);
    cout << "╗" << endl;

    // Draw the options.
    for (int i = 0; i < noo; i++) {
        set_x(x);
        cout << "║ ";
        if (i == current) {
            set_color(BLACK, WHITE);
            cout << items[i].text;
            reset_color();
        }
        else
            cout << items[i].text;
        set_x(end_x);
        cout << "║" << endl;
    }

    // Draw the bottom border.
    set_x(x);
    cout << "╚";
    for (int i = 0; i < MENU_WIDTH - 2; i++) {
        cout << "═";
    }
    cout << "╝" << endl;
}

void Menu::move_up() {
    current = (current - 1 + count) % count;
    render();
}

void Menu::move_down() {
    current = (current + 1) % count;
    render();
}

void Menu::select() {
    items[current].action();
}

void Menu::update() {
    special_00124 = true;
    int key = get_key();

    // Default option
    if (key == KEY_UP)
        this->move_up();
    else if (key == KEY_DOWN)
        this->move_down();
    else if (key == KEY_ENTER)
        this->select();

    // User option calling by typing key 0 - 9
    if (key >= '1' && key <= '9') {
        this->items[int(key - '0') - 1].action();
    }

    this->settings.act(key);
}

void Menu::show() {
    render();
    this->settings.draw();
}

void Menu::add_item(const string& text, func action) {
    if (count == MAX)
        return;
    items[count++] = MenuItem(text, action);
}

void sleep(int time) {
    Sleep(time);
}

void splash_screen(const string& text, const string& path,
    const string dev_list[], int dev_count, int color) {
    clear_screen();

    draw_title(text, path, color);

    // Show the list of developers.
    for (int i = 0; i < dev_count; i++)
        cout << "+) " << dev_list[i] << endl;                                     

    enter_to_continue();
    clear_screen();
}

void set_position(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void get_position(int &x, int &y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
}

void toggle_cursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = visible;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void set_x(int x) {
    int y, tmp;
    get_position(tmp, y);
    set_position(x, y);
}

void set_y(int y) {
    int x, tmp;
    get_position(x, tmp);
    set_position(x, y);
}

void set_color(int color, int background_color) {
    if (!ENABLE_COLOR)
        // If developer disable the color, end the function.
        return;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color + background_color * 16);
}

void reset_color() {
    if (!ENABLE_COLOR)
        // If developer disable the color, end the function.
        return;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}

int get_key() {
    return _getch();
}

Settings::Settings() : Settings(MAX) {}

Settings::Settings(int max_size) : cmds(new int[max_size]),
        cmds_str(new string[max_size]), descriptions(new string[max_size]),
        actions(new func[max_size]), count(0), max_size(max_size) {
    // Add default settings.
    this->add(KEY_UP, "↑", "Lên", do_nothing);
    this->add(KEY_DOWN, "↓", "Xuống", do_nothing);
    this->add(KEY_ENTER, "↲", "Chọn", do_nothing);
    this->add('q', "q", "Thoát", exit_program);
}

void Settings::add(int cmd, const string& cmd_str, const string& description, func action) {
    if (count == max_size)
        // If the settings is full, end the function.
        return;
    cmds[count] = cmd;
    cmds_str[count] = cmd_str;
    descriptions[count] = description;
    actions[count] = action;
    count++;
}

void Settings::act(int &key) {
    for (int i = 0; i < count; ++i) {
        if (key == cmds[i]) {
            actions[i]();
        }
    }
}

void Settings::draw() {
    for (int i = 0; i < count; i++) {
        set_color(BLACK, WHITE);
        cout << cmds_str[i];
        reset_color();
        cout << " - " << descriptions[i] << " \t";
        // If the number of settings in one line is full, move to the next line.
        if ((i + 1) % MAX_SETTINGS_IN_ONE_LINE == 0) {
            cout << endl;
        }
    }
}

void clear_screen() {
    system(CLEAR_COMMAND);
}

void enter_to_continue() {
    cout << endl << "Nhấn Enter để tiếp tục...";
    _getch();
}

void exit_program() {
    clear_screen();
    cout << "Hẹn gặp lại...";

    special_00124 = false;

    enter_to_continue();
}

void attach_running(bool &running) {
    // Attach to the running variable in main program.
    running = special_00124;
}

void do_nothing() {
    // Do nothing.
}

void init_gui() {
    SetConsoleOutputCP(65001);
    toggle_cursor(false);
    enter_full_screen();
}

void enter_full_screen() {
    HWND Hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    
    // Remove the WS_CAPTION, WS_THICKFRAME, and WS_BORDER styles, but don't add WS_POPUP
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER));
    
    // Set the window position and size while keeping the taskbar visible
    SetWindowPos(Hwnd, HWND_TOP, 0, 0, x, y, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
}

// GraphicsMatrix::GraphicsMatrix(int x, int y, int n, int m, int cell_width, int cell_height) :
//         x(x), y(y), n(n), m(m), i(0), j(0), cell_width(cell_width), cell_height(cell_height),
//         matrix(make_unique<MenuItem[]>(n * m)) {
//             for (int i = 0; i < n * m; ++i)
//                 matrix[i] = EMPTY_ITEM;
//         }

// void GraphicsMatrix::set_pos(int x, int y) {
//     this->x = x;
//     this->y = y;
// }

// void GraphicsMatrix::add_item(const string& text, func action) {
//     MenuItem item(text, action);
//     matrix[i][j] = item;
//     j++;
//     if (j == m) {
//         i++;
//         j = 0;
//     }
// }

// void GraphicsMatrix::render() {
//     set_position(x, y);
//     int index;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             index = i * n + j;
//         }
//         cout << endl;
//     }
// }