echo "enter the limit"
read limit
echo "Entered limit is : $limit"
for x in $(seq 1 $limit); do sleep 5; wmctrl -lp | grep $(xprop -root | \
    grep _NET_ACTIVE_WINDOW | head -1 | awk '{print $5}' | sed 's/,//' | \
    sed 's/^0x/0x0/'); done >file2
wmctrl -lp >file1
echo "you should close this window~ Yes/No?"
read option
if [ "$option" = "y" ]; then
               echo "expression evaluated as true"
fi
awk -F' ' 'NR==FNR{c[$3]++;next};c[$3] <= 0' file2 file1
echo "enter the pid of window to be closed"
read pid
wmctrl -i -c $pid
