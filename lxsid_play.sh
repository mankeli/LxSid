#!/bin/bash
trap 'kill -HUP $PIDI' EXIT
#SONG=$(find ~/C64Music/ -name *sid | sort -R | head -n1)
SONG=$(shuf -n 1 ~/C64Music/lxsid/sidlist.txt)
echo $SONG > /tmp/lxsid_cursidsong
sidplayfp $SONG &
PIDI=$!
wait $PIDI

