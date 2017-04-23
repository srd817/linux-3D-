#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "keys.h"
#include "directions.h"
/*@requires  rien
   assigns  rien
   ensures  retourne  entrée du clavier de la valeur 
*/
int getch(void)
{
	 /* restore terminal settings*/ 
     static struct termios tm, tm_old; 
     int fd = 0, ch; 
     if (tcgetattr(fd, &tm_old) < 0) {
          return -1;
     }
     tm=tm_old;
     tm.c_lflag &= ~(ICANON|ECHO|ECHOE|ECHOK|ECHONL|ICRNL);   
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     } 
     ch = getchar();
	/*apply settings*/
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {           
          return -1;
     }    
     return ch;
}
/*@requires  rien
   assigns  rien
   ensures  retourne la nomber de direction(dans keys.c deja defini).
*/

int direction(){
     int array[]={UP,LEFT,DOWN,RIGHT,ENTER,PLACE,EXIT,RETIRER};
     int i,ch;
     while(1){
	  ch=getch();
          for(i=0; i<8; i++){
	        if(ch == array[i])
		   return ch;
          }
     }     
}




