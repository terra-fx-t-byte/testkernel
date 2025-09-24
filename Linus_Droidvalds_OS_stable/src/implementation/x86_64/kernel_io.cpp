#include "kernel_io.h"
#include "assemblyoutb.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++){
        buffer[col + NUM_COLS * row] = empty;
    }
}

bool keyboard_has_data() {
    return (inb(KEYBOARD_STATUS_PORT) & 1) != 0;
}

uint8_t keyboard_read_scancode() {
    while (!keyboard_has_data());
    return inb(KEYBOARD_DATA_PORT);
}

typedef struct {
    uint8_t scancode;
    char normal;
    char shifted;
} key_mapping;

key_mapping keymap[] = {
    {0x02, '1', '!'}, {0x03, '2', '@'}, {0x04, '3', '#'}, {0x05, '4', '$'},
    {0x06, '5', '%'}, {0x07, '6', '^'}, {0x08, '7', '&'}, {0x09, '8', '*'},
    {0x0A, '9', '('}, {0x0B, '0', ')'}, {0x0C, '-', '_'}, {0x0D, '=', '+'},
    {0x10, 'q', 'Q'}, {0x11, 'w', 'W'}, {0x12, 'e', 'E'}, {0x13, 'r', 'R'},
    {0x14, 't', 'T'}, {0x15, 'y', 'Y'}, {0x16, 'u', 'U'}, {0x17, 'i', 'I'},
    {0x18, 'o', 'O'}, {0x19, 'p', 'P'}, {0x1A, '[', '{'}, {0x1B, ']', '}'},
    {0x1E, 'a', 'A'}, {0x1F, 's', 'S'}, {0x20, 'd', 'D'}, {0x21, 'f', 'F'},
    {0x22, 'g', 'G'}, {0x23, 'h', 'H'}, {0x24, 'j', 'J'}, {0x25, 'k', 'K'},
    {0x26, 'l', 'L'}, {0x27, ';', ':'}, {0x28, '\'', '"'}, {0x29, '`', '~'},
    {0x2B, '\\', '|'}, {0x2C, 'z', 'Z'}, {0x2D, 'x', 'X'}, {0x2E, 'c', 'C'},
    {0x2F, 'v', 'V'}, {0x30, 'b', 'B'}, {0x31, 'n', 'N'}, {0x32, 'm', 'M'},
    {0x33, ',', '<'}, {0x34, '.', '>'}, {0x35, '/', '?'},
    {0x39, ' ', ' '}, // Space
    {0x1C, '\n', '\n'}, // Enter
    {0x0E, '\b', '\b'}, // Backspace
    {0, 0, 0} // Terminator
};

bool shift_pressed = false;
bool caps_lock = false;

char scancode_to_char(uint8_t scancode) {
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = true;
        return '\0';
    } else if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = false;
        return '\0';
    } else if (scancode == 0x3A) {
        caps_lock = !caps_lock;
        return '\0';
    }

    if (scancode & 0x80) return '\0';

    for (int i = 0; keymap[i].scancode != 0; i++) {
        if (keymap[i].scancode == scancode) {
            bool uppercase = shift_pressed ^ caps_lock;
            return uppercase ? keymap[i].shifted : keymap[i].normal;
        }
    }
    return '?';
}

char getchar_nb() {
    if (!keyboard_has_data()) return '\0';

    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    return scancode_to_char(scancode);
}

char getchar() {
    char c;
    while ((c = getchar_nb()) == '\0');
    return c;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * NUM_COLS + x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++){
        clear_row(i);
    }
}

void print_newline() {
    col = 0;
    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }
    clear_row(NUM_ROWS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color
    };

    col++;
    update_cursor(col, row);
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void clean_last_char() {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };
    buffer[(col + NUM_COLS * row) - 1] = empty;
    col --;
    update_cursor(col, row);
}

char* get_input(int bufferlength = 256){
    static char initbuffer[256] = {0};
    int initpos = 0;
    while(true){
        char inp = getchar();
        if(inp == '\b') {
            if(initpos > 0) {
                clean_last_char();
                initpos--;
                initbuffer[initpos] = '\0';
            }
        }
        else if(inp == '\n') {
            initbuffer[initpos] = '\0';
            return initbuffer;
        }
        else{
            if (initpos <= bufferlength - 1) {
                print_char(inp);
                initbuffer[initpos] = inp;
                initpos++;
            }
        }
    }
    initbuffer[bufferlength - 1] = '\0';
    return initbuffer;
}


void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}
