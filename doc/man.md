# imd <file> [options]

## <file>

File to open.

IMD also supports pipping.

## Options

### -r, --raw

Print data without less like feature.

### -d, --no-decoration

No decoration I.E line numbers and file display

### -s, --no-syntax

No syntax highlighting.

### -h, --help

Display this file.

### -v, --version

Display version.


# Controls For Pager

## w-s

Up-Down

## j-k

Up-Down

## ArrowUp-ArrowDown

Up-Down

## PageUp-PageDown

PagedUp-PagedUp

## Mouse Wheel

Just scroll.

## q

Quit.

## G

Goto end of file.

## g

Goto start of file.

## :<line>

Goto `line`.

## Ctrl-c

Force quit.

***Warning: Does not free data, will cause memory leaks***
***Only use when `q' doesn't work***
