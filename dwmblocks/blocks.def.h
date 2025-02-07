// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    // {"", "sb-music", 1, 16},
    {"", "sb-netspeed", 5, 17},
    {"", "sb-cpu", 5, 18},
    {"", "sb-memory", 5, 19},
    {"", "sb-volume", 3, 20},
    // {"", "sb-battery", 3, 21},
    {"", "sb-bluetooth", 5, 23},
    {"", "sb-internet", 5, 24},
    {"", "sb-date", 1, 25},
    {"", "sb-user", 0, 26},
};

// sets delimeter between status commands. NULL character ('\0') means no
// delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
