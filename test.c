#include<stdlib.h>
#include <time.h> 
int main(){
int secs=60;
int unit_time=10;
int steps=secs/unit_time;
printf("Watching CPU usage... ");
for((i=0;i<steps;i++))
{
system( "ps -eocomm,pcpu | tail -n +2 >> /tmp/cpu_usage.$$");
sleep(unit_time);
printf("CPU Eaters");
system(cat /tmp/cpu_usage.$$ | \);




return 0;
}
