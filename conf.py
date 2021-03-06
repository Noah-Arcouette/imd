#!/bin/python3
from sys import argv
from os.path import exists
import json as JSON

def genConf (f):
    data = f.read();
    data = JSON.loads(data);

    # outputs
    error      = scope(data['error']);
    defs       = scope(data['default']);
    highlight  = scope(data['highlight']);

    # headers
    h1         = scope(data['h1']);
    h2         = scope(data['h2']);
    h3         = scope(data['h3']);

    # lists
    list       = scope(data['list']);
    tab_list   = scope(data['tab-list']);

    # links
    alt        = scope(data['alt']);
    link       = scope(data['link']);
    brackets   = scope(data['brackets']);

    # underline
    underline  = scope(data['underline']);

    # italics
    italic     = scope(data['italic']);
    bold       = scope(data['bold']);
    bold_ital  = scope(data['bold-italic']);

    # boxs
    box        = scope(data['box']);
    box_text   = scope(data['box-text']);

    # syntax
    syntax     = scope(data['syntax']);
    operator   = scope(data['operator']);
    string     = scope(data['string']);
    number     = scope(data['number']);
    bracket    = scope(data['bracket']);

    out = "#ifndef __CONF_H__\n#define __CONF_H__\n";

    # outputs
    out += error.gen("error_c");
    out += defs.gen("def_c");
    out += highlight.gen("highlight_c");

    # headers
    out += h1.gen("h1_c");
    out += h2.gen("h2_c");
    out += h3.gen("h3_c");

    # lists
    out += list.gen("list_c");
    out += tab_list.gen("tab_list_c");

    # links
    out += alt.gen("alt_c");
    out += link.gen("link_c");
    out += brackets.gen("brackets_c");

    # underline
    out += underline.gen("underline_c");

    # italics
    out += italic.gen("italic_c");
    out += bold.gen("bold_c");
    out += bold_ital.gen("bold_italic_c");

    # syntax
    out += syntax.gen("syntax_c");
    out += operator.gen("operator_c");
    out += string.gen("string_c");
    out += number.gen("number_c");
    out += bracket.gen("bracket_c");

    # boxs
    out += box.gen("box_c");
    out += box_text.gen("box_text_c");

    out += "#endif\n";

    return out;

class Style:
    def __init__ (self):
        self.fg      = "default";
        self.bg      = "default";
        self.bold    = False;
        self.dim     = False;
        self.ital    = False;
        self.line    = False;
        self.blink   = False;
        self.reverse = False;
        self.strike  = False;
        self.hidden  = False;

    def getColor (self):
        out = "\\x1b[0;";

        if self.fg == "default":
            out += "39"
        elif self.fg == "black" or self.fg == "gray":
            out += "30"
        elif self.fg == "bright black" or self.fg == "bright gray":
            out += "90"
        elif self.fg == "red":
            out += "31"
        elif self.fg == "bright red":
            out += "91"
        elif self.fg == "green":
            out += "32"
        elif self.fg == "bright green":
            out += "92"
        elif self.fg == "yellow":
            out += "33"
        elif self.fg == "bright yellow":
            out += "93"
        elif self.fg == "blue":
            out += "34"
        elif self.fg == "bright blue":
            out += "94"
        elif self.fg == "purple":
            out += "35"
        elif self.fg == "bright purple":
            out += "95"
        elif self.fg == "cyan":
            out += "36"
        elif self.fg == "bright cyan":
            out += "96"
        elif self.fg == "white":
            out += "37"
        elif self.fg == "bright white":
            out += "97"
        elif self.fg[0] == '#':
            out += '38;2;';

            # 216 30 91
            # d8  1e 5b

            num = int(self.fg[1::], 16);

            # R
            out += str((num >> 16) & 0xff) + ';';

            # G
            out += str((num >> 8) & 0xff) + ';';

            # B
            out += str(num & 0xff);
        else:
            print(f"\x1b[1;31mError\x1b[0m: Unknown color `\x1b[1;35m{self.fg}\x1b[0m`.");

            exit(1);

        out += ';';

        if self.bg == "default":
            out += "49"
        elif self.bg == "black" or self.bg == "gray":
            out += "40"
        elif self.bg == "bright black" or self.bg == "bright gray":
            out += "100"
        elif self.bg == "red":
            out += "41"
        elif self.bg == "bright red":
            out += "101"
        elif self.bg == "green":
            out += "42"
        elif self.bg == "bright green":
            out += "102"
        elif self.bg == "yellow":
            out += "43"
        elif self.bg == "bright yellow":
            out += "103"
        elif self.bg == "blue":
            out += "44"
        elif self.bg == "bright blue":
            out += "104"
        elif self.bg == "purple":
            out += "45"
        elif self.bg == "bright purple":
            out += "105"
        elif self.bg == "cyan":
            out += "46"
        elif self.bg == "bright cyan":
            out += "106"
        elif self.bg == "white":
            out += "47"
        elif self.bg == "bright white":
            out += "107"
        elif self.bg[0] == '#':
            out += '48;2;';

            # 216 30 91
            # d8  1e 5b

            num = int(self.bg[1::], 16);

            # R
            out += str((num >> 16) & 0xff) + ';';

            # G
            out += str((num >> 8) & 0xff) + ';';

            # B
            out += str(num & 0xff);
        else:
            print(f"\x1b[1;31mError\x1b[0m: Unknown color `\x1b[1;35m{self.bg}\x1b[0m`.");

            exit(1);

        if self.bold:
            out += ';1';

        if self.dim:
            out += ';2';

        if self.ital:
            out += ';3';

        if self.line:
            out += ';4';

        if self.blink:
            out += ';5';

        if self.reverse:
            out += ';7';

        if self.hidden:
            out += ';8';

        if self.strike:
            out += ';9';

        out += 'm';

        return out;

    def gen (self, name):
        out = "";

        name = name.upper();

        color = self.getColor();

        out += f"#\tdefine {name} \"{color}\"\n";

        return out;

def scope (section):
    s = Style();

    if 'fg' in section:
        s.fg = section['fg'];

    if 'bg' in section:
        s.bg = section['bg'];

    if 'styles' in section:
        styles = section['styles'].split(' ');

        if 'bold' in styles:
            s.bold = True;

        if 'dim' in styles:
            s.dim = True;

        if 'ital' in styles or 'italic' in styles:
            s.ital = True;

        if 'line' in styles or 'underline' in styles:
            s.line = True;

        if 'blink' in styles or 'blinking' in styles:
            s.blink = True;

        if 'reverse' in styles:
            s.reverse = True;

        if 'strike' in styles:
            s.strike = True;

        if 'hidden' in styles or 'hide' in styles:
            s.hidden = True;

    return s;

def main ():
    conf = "default"

    # TODO: Check Args

    if exists(f"./confs/{conf}.json"):
        with open(f"./confs/{conf}.json", "r") as f:
            conf = genConf(f);

            with open("./inc/conf.h", "w") as confF:
                confF.write(conf);
    else:
        print(f"\x1b[31;1mError\x1b[0m: Config `\x1b[1;35m{conf}\x1b[0m' cannot be opened.");

        exit(1);

    exit(0);

if __name__ == "__main__":
    main();
