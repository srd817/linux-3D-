#include<stdio.h>
#include<termios.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>  

#include"keys.h"
#include"directions.h"
#include"menu.h"
#include"new.h"


/*@requires n>0,h>0
   assigns  chessboard c
   ensures  Création d'un damier.
*/
chessboard creat(int n,int h){
	int i,j,k;	
	chessboard c;
	c.size=3*n;
	c.haut=h;
	c.chess=(char ***)calloc(3*n,sizeof(char **));
	/* sur la ligne*/
	for (i=0;i<3*n;i++)
	c.chess[i]=(char **)calloc(3*n,sizeof(char *));	
	/*sur la colonne*/
	for (i=0;i<3*n;i++){
	/*sur la haut*/
	    for(j=0;j<3*n;j++){
		c.chess[i][j]=(char *)calloc(h,sizeof(char));
		for(k=0;k<h;k++)
		        c.chess[i][j][k]=' ';
	    }
	}
	return c;	
}

/*@requires board n'est pas NULL
   assigns  rien
   ensures  afficher le initial damier 
*/
void print_init(chessboard *board) {
	system("clear");
	int i,j; 
  	for(i=0;i<board->size;i++) {
    		for(j=0;j<board->size;j++) {
                   printf(" %c ",board->chess[i][j][0]);
                }
            printf("\n");
        }
}

/*@requires stu[0]>=0,stu[1]>=0
   assigns  rien
   ensures  juger si le emplacement spécifié est vide.
*/
int board_void(chessboard *board,int stu[]) {
	int x=stu[0],y=stu[1];
	if (board->chess[x][y][0]==' ') 
	    return 0;
	else 
	    return 1;

}


/*@requires stu[0]>=0,stu[1]>=0, et board n'est pas vide.
   assigns  *board.
   ensures  retirer le jeton au sommet de emplacement spécifié. si il est vide ,retourne 0, si retier, retourne 1. 
*/
int retirer(chessboard *board,int stu[]) {
	int k,x=stu[0],y=stu[1];
	if(board_void(board,stu)){    
	/*chercher le jeton au sommet*/                   
		for(k=1;k<board->haut;k++) {
			if(board->chess[x][y][k] == ' '){
                    		board->chess[x][y][k-1]=' ';
                           	return 0; 
                        }
		}
	board->chess[x][y][k-1]=' ';
	return 0; 			     
	}
     	return 1;
}


/*@requires stu[0]>=0,stu[1]>=0,board n'est pas vide
   assigns  *board
   ensures  poser le jeton au sommet de emplacement spécifié.
*/
int place(chessboard *board,int stu[],int turn) {
	int k;	
	int x=stu[0],y=stu[1];
	/*chercher la sommet*/
	for(k=0;k<(board->haut);k++){
	    if(board->chess[x][y][k]==' ')
	    break;
	}
	if(k<(board->haut)){
	    if((turn%2)==0)
	        board->chess[x][y][k]='X';
	    else
	        board->chess[x][y][k]='O';
	return 1;
	}
	return 0;	
}

/*@requires stu[0]>=0,stu[1]>=0,board n'est pas vide
   assigns  rien
   ensures  afficher le  damier actuel.
*/
void print_board(chessboard *chess,int stu[]) {
	int x=stu[0],y=stu[1];	
	system("clear");
	int i,j,k,h,sign;
	if(chess->chess[x-1][y][0]=='*')
	   sign=1; 
	else
	   sign=0;
/*afficher la position du curseur*/
	chess->chess[x-1][y][0]='+';
	chess->chess[x+1][y][0]='+';
	chess->chess[x][y-1][0]='+';
	chess->chess[x][y+1][0]='+';
	for(k=0;k<(chess->haut);k++) {
            if(chess->chess[x][y][k]==' ')
                break;              
	}
	h=k;
	k=1;
	for(i=0;i<chess->size;i++) {
	       for(j=0;j<chess->size;j++) {        
                     for(k=1;k<(chess->haut);k++) {
                        if(chess->chess[i][j][k]==' '){
                           printf(" %c ",chess->chess[i][j][k-1]);  
                           break;               
	                }
			if(k==(chess->haut-1))
			   printf(" %c ",chess->chess[i][j][k]); 
	             }
               }
	if(((chess->size)-i-2)<h){    
             printf("|   %c \n",chess->chess[x][y][h]);
	     h--;	
	}
	else
	     printf("|\n");
        }

  	printf("___________________________________________________________________\n");
	if(sign==0){		
	chess->chess[x-1][y][0]=' ';
	chess->chess[x+1][y][0]=' ';
	chess->chess[x][y-1][0]=' ';
	chess->chess[x][y+1][0]=' ';
	}
	/* si il y a  seieme, devient '*' */
	else{
	chess->chess[x-1][y][0]='*';
	chess->chess[x+1][y][0]='*';
	chess->chess[x][y-1][0]='*';
	chess->chess[x][y+1][0]='*';
	}
}


/*@requires stu[0]>=0,stu[1]>=0, board n'est pas vide, direction deja defini dans ksys.c 
   assigns  stu[]
   ensures  retourne la nouvel emplacement.
*/
int *chess_keys(chessboard *board,int direction,int stu[]){
  	int x=stu[0],y=stu[1];
  	if(direction==UP){
	   if(x==1)
      	      x=(board->size)-2;
    	   else
              x=x-3; 
	/* afficher le  damier actuel.*/
    	   print_board(board,stu);       
   	}
  	else if(direction==DOWN){
    	   if(x==(board->size)-2)
      	      x=1;
    	   else
      	      x=x+3;      
	/* afficher le  damier actuel.*/
    	   print_board(board,stu);      
  	}
 	else if(direction==LEFT){
	   if(y==1)
	      y=(board->size)-2;
	   else
	      y=y-3;
	/* afficher le  damier actuel.*/
	   print_board(board,stu);   
	}
	else if(direction==RIGHT){
	   if(y==(board->size)-2)
	      y=1;
	   else
	      y=y+3;
	/* afficher le  damier actuel.*/
	   print_board(board,stu);   
	}
  	   printf("\n");
  	   stu[0]=x;
  	   stu[1]=y;
  	   return stu; 
}


/*@requires turn>0
   assigns  rien
   ensures  affich forme de jeton.
*/
void print_turn(int turn){
	if(turn%2 == 0){
	    printf("C'est X\n");
	    printf("  i:up  j:left  k:down  l:right  p:palce  q:exit  r:retirer \n");
	}
	else if(turn%2 == 1){
	    printf("C'est O\n");
	    printf("  i:up  j:left  k:down  l:right  p:palce  q:exit  r:retirer \n");
	}
}




