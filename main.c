#include<stdio.h>
#include<termios.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>  
#include<time.h>
#include<math.h>

#include "keys.h" 
#include "directions.h"
#include "menu.h"
#include "new.h"
#include "seieme.h"
#include "judge.h"
#include "begin.h"

int main(){
	printf("\033[?25l");
	chessboard c;
	int i;
	while(1){
	i=menu_choose();	
	switch(i){
	    case 0 : {
		system("clear");		
		int n,h=0;
		printf("C'est size:\n");
		scanf("%d",&n);
		while(h<n){
		printf("C'est haut:(haut > size)\n");	
		scanf("%d",&h);}
		c=creat(n,h);
		begin(&c,i);
		break;
	    }
	    case 1: {
		system("clear");		
		int n,h=0;
		printf("C'est size:\n");
		scanf("%d",&n);
		while(h<n){
		printf("C'est haut:(haut > size)\n");	
		scanf("%d",&h);}
		c=creat(n,h);
		begin(&c,i);
		break;
	    }
	    case 2: {
		system("clear");		
		int n,h=0;
		printf("C'est size:\n");
		scanf("%d",&n);
		while(h<n){
		printf("C'est haut:(haut > size)\n");	
		scanf("%d",&h);}
		c=creat(n,h);
		begin(&c,i);
		break;
	    }
	    case 3: {
		system("clear");		
		int n,h=0;
		printf("C'est size:\n");
		scanf("%d",&n);
		while(h<n){
		printf("C'est haut:(haut > size)\n");	
		scanf("%d",&h);}
		c=creat(n,h);
		begin(&c,i);
		break;
	    }
	    default:
		system("clear");
                printf("\033[?25h");
		return 0;
	}
   	return 0;
	}
} 
