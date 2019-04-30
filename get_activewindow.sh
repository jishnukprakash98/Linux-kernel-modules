echo "enter the limit"
read limit
for x in $(seq 1 $limit); do sleep 5; wmctrl -lp | grep $(xprop -root | \
    grep _NET_ACTIVE_WINDOW | head -1 | awk '{print $5}' | sed 's/,//' | \
    sed 's/^0x/0x0/'); done >file2
wmctrl -lp >file1

awk -F' ' 'NR==FNR{c[$3]++;next};c[$3] <= 0' file2 file1 >file3

while read line ; do
    set $line
    name=$(echo $line|cut -d" " -f5-)
    zenity --question --text="Do you wish to close this window?: $name"
    option=$?
    echo "$option"
    if [ "$option" = "0" ]; then
               wmctrl -i -c $1
    fi
done <file3
