#!/bin/bash

SONG=$(cat /tmp/lxsid_cursidsong)
echo "Last song: $SONG"
if [ "$#" -eq 2 ]; then
	echo "$SONG $1 $2" >> ~/C64Music/lxsid/sidratings.log
	echo "logged with ratings $1 $2"
else
	echo "syntax $0 quality sadness"
fi
