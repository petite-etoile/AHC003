#!/bin/zsh

for f in how_to_solve?*.jpeg
do
    echo mv \"$f\" ${f/ /_}
    # mv \"$f\" ${f/ /_}
done