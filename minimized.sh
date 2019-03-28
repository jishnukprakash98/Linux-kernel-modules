#!/bin/bash
# usage: isMinimized <windowId>
# returns status 0 if and only if window with given id is minimized
isMinimized() {
    xprop -id "$1" | grep -Fq 'window state: Iconic'
}
openWindows() {
    count=0
    for id in $(wmctrl -l | cut -f1 -d' '); do
        isMinimized "$id" || ((count++))
    done
    echo $count
}
openWindows
