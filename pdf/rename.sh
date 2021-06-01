#!/bin/zsh

for f in how_solve?*.jpeg
do
    echo mv \"$f\" ${f/ /_}
    # mv \"$f\" ${f/ /_}
done