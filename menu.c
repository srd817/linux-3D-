#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "keys.h"
#include "directions.h"

/*@requires  nombre est positive.
   assigns  rien.
   ensures  Imprimer le nombre de lignes nécessaires. 
*/
void print_lines(int nombre) {
    int i;
    for (i = 0; i < nombre; i++) {
        printf("\n");
    }
}


/*@requires  rien
   assigns  rien.
   ensures  Imprimer titre de jeux. 
*/
void menu_title() {
    print_lines(3);
    printf("                    █████     █    █     █ ███████ \n");
    printf("                   █     █   █ █   ██   ██ █       \n");
    printf("                   █        █   █  █ █ █ █ █       \n");
    printf("                   █  ████ █     █ █  █  █ ██████   \n"); 
    printf("                   █     █ ███████ █     █ █       \n");
    printf("                   █     █ █     █ █     █ █       \n");
    printf("                    █████  █     █ █     █ ███████ \n");
    print_lines(3);
    printf("     i:up  j:left  k:down  l:right  a:enter  p:palce  q:exit  r:retirer     \n");
    print_lines(3);
}


/*@requires 0<=tiem<5.
   assigns  rien.
   ensures  Imprimer menu de jeux. 
*/
void menu_sign(int item){
    char sign[5]={' ',' ',' ',' ',' '};
    sign[item]='@';
    printf("                          %c NEW VVDD\n",sign[0]);
    printf("                          %c NEW 3D\n",sign[1]);
    printf("                          %c NEW SEISME-VVDD\n",sign[2]);  
    printf("                          %c NEW SEISME-3D\n",sign[3]);    
    printf("                          %c EXIT\n",sign[4]);   
}


/*@requires 0<=tiem<5.
   assigns  rien.
   ensures  Imprimer toutes les interfaces. 
*/
void menu_print(int item){
    system("clear");
    menu_title();
    menu_sign(item);
} 


/*@requires 0<=tiem<5.
   assigns  rien.
   ensures  Sélection du menu. 
*/
int menu_choose(){
    int item=0;
    menu_print(item);    
    int dir=direction();
/* quand entrée n'est pas ENTRE, mouvement circulating */
    while (dir!=ENTER){
	if (dir==UP && item!=0)
	    item--;
	else if (dir==DOWN && item !=4)
	    item++;
	else if (dir==EXIT)
	    return 10;
        menu_print(item);
        dir=direction();
    }
    return item;
}
 






