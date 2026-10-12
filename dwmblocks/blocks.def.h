// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/ /*Keep in compact view*/
    {"", "sb-netspeed", 5, 17, 0},
    // {"", "sb-cpu", 5, 18, 0},
    // {"", "sb-memory", 5, 19, 0},
    {"", "sb-music", 3, 30, 0},
    {"", "sb-volume", 3, 20, 1},
    {"", "sb-battery", 3, 21, 0},
    // {"", "sb-bluetooth", 5, 23, 0},
    // {"", "sb-internet", 5, 24, 0},
    {"", "sb-date", 1, 25, 1},
    {"", "sb-user", 0, 26, 1},
};

// sets delimeter between status commands. NULL character ('\0') means no
// delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;

// Clicking the toggle glyph flips between full and compact view.
// Signal must not collide with any block signal.
#define TOGGLE_SIGNAL 27
static const char glyphFull[] = " ‹ ";
static const char glyphCompact[] = " › ";
