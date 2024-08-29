# GUI Library for C++

## Overview

This is a simple GUI library for C++ designed for console applications on Windows OS. It provides basic functionalities to create menus, handle user input, and display text with colors in the console.

## Features

- Clear the console screen
- Wait for user input
- Change the state of the GUI
- Display menus and settings
- Handle user input for menu navigation
- Display text with colors
- Full-screen mode support

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/antialberteinstein/gui-library.git
    ```
2. Include the `gui.h` and `gui.cpp` files in your project.

## Usage

### Initialization

Before using the GUI library, initialize it by calling:
```cpp
init_gui();
```

### Creating a Menu

1. Define the actions for your menu items:
    ```cpp
    void action1() {
        cout << "Action 1 selected" << endl;
    }

    void action2() {
        cout << "Action 2 selected" << endl;
    }
    ```

2. Create a `Settings` object and a `Menu` object:
    ```cpp
    Settings settings;
    Menu menu(settings);
    ```

3. Add items to the menu:
    ```cpp
    menu.add_item("Option 1", action1);
    menu.add_item("Option 2", action2);
    ```

4. Show the menu and handle user input:
    ```cpp
    bool running = true;
    while (running) {
        menu.show();
        menu.update();
        attach_running(running);
    }
    ```

### Displaying Text with Colors

Use the `set_color` and `reset_color` functions to display text with colors:
```cpp
set_color(RED);
cout << "This is red text" << endl;
reset_color();
```

### Full-Screen Mode

Enter full-screen mode by calling:
```cpp
enter_full_screen();
```

## Example

Here is a complete example of a simple program using the GUI library:

```cpp
#include "gui.h"

void action1() {
    cout << "Action 1 selected" << endl;
}

void action2() {
    cout << "Action 2 selected" << endl;
}

int main() {
    init_gui();

    Settings settings;
    Menu menu(settings);

    menu.add_item("Option 1", action1);
    menu.add_item("Option 2", action2);

    bool running = true;
    while (running) {
        menu.show();
        menu.update();
        attach_running(running);
    }

    return 0;
}
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Author

Developed by [antialberteinstein](https://github.com/antialberteinstein)