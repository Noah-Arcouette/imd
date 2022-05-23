#!/bin/python3
from sys import argv
from os.path import exists
import json as JSON

def readConf (f):
    data = f.read();
    data = JSON.loads(data);

    print(data);

    return;

def main ():
    conf = "default"

    # TODO: Check Args

    if exists(f"./confs/{conf}.json"):
        with open(f"./confs/{conf}.json", "r") as f:
            readConf(f);
    else:
        print(f"\x1b[31;1mError\x1b[0m: Config `\x1b[1;35m{conf}\x1b[0m' cannot be opened.");

        exit(1);

    exit(0);

if __name__ == "__main__":
    main();
