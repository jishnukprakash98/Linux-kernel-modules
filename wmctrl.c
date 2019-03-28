#include<stdlib.h>
#include<stdio.h>
void main(){
int time;
printf("Please specify the allowed background time?\t");
scanf("%d",&time);
system("wmctrl -l");
printf("%d seconds expired! can i close the window?",time);




}


