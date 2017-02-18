#!/bin/sh
#tests commands with ;, &&, or
ls -a; echo hello && mkdir test && rm -r test; ls
lol || git status; xD && exit; ls pizza
ls&&mkdir test; ls -a &&rm -r test ||lol; ls
lol ||&& git status; xD
