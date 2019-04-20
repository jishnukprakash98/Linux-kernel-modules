#!/bin/sh

for x in {1..10} ; do
	sleep 5; wmctrl -lp | grep $(xprop -root | \
	grep _NET_ACTIVE_WINDOW | head -1 | awk '{print $5}' | sed 's/,//' | \
	sed 's/^0x/0x0/');
done
