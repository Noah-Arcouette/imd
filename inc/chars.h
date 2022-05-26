#ifndef __CHARS_H__
#define __CHARS_H__
# define TRIANGE_RIGHT        "\uE0B0"
# define TRIANGE_RIGHT_HOLLOW "\uE0B1"
# define TRIANGE_LEFT         "\uE0B2"
# define TRIANGE_LEFT_HOLLOW  "\uE0B3"
# define CURVE_RIGHT          "\uE0B4"
# define CURVE_RIGHT_HOLLOW   "\uE0B5"
# define CURVE_LEFT           "\uE0B6"
# define CURVE_LEFT_HOLLOW    "\uE0B7"
# define ARROW_LEFT           "\uE200"
# define ARROW_RIGHT          "\uE285"
# define HOME_ICON            "\uE1B0"
# define FILE_ICON            "\uE185"
# define END                  "\x1b[?25h\x1b[?47l\x1b[?1049l\x1b[=7h"
# define REFRESH              "\x1b[2J\x1b[H"
# define SETUP                "\x1b[?25l\x1b[?47h\x1b[?1049h\x1b[=7l"
# define MOVE_HOME            "\x1b[H"
# define MOVE(x, y)           ("\x1b[" #y ";" #x "H")
# define MOVE_P(x, y)         printf("\x1b[%d;%dH", y, x);
# define HBAR                 "─"
# define VBAR                 "│"
# define TL_CORNER            "┌"
# define TR_CORNER            "┐"
# define BL_CORNER            "└"
# define BR_CORNER            "┘"
# define TL_CURVE             "╭"
# define TR_CURVE             "╮"
# define BL_CURVE             "╯"
# define BR_CURVE             "╰"  
#endif
