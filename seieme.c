#include<stdio.h>
#include<termios.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<math.h>

#include"keys.h"
#include"directions.h"
#include"menu.h"
#include"new.h"
#include"seieme.h"

/*@requires x>=0, y>=0, board n'est pas vide
   assigns  rien
   ensures  retourne la haut de emplacement spécifié..
*/
int haut(chessboard *board,int x, int y){
	int h;
	/*chercher le première ' '.*/
	for(h=0;h<(board->haut);h++) {
            if(board->chess[x][y][h]==' ')
                break;              
	}
	return h;
}


/*@requires x>=0, y>=0, board n'est pas vide
   assigns  rien
   ensures  si il y a seieme,retourne la nomber deeffondrement, sinon, retourne 0. 
*/
int seieme(chessboard *board,int x, int y){
	int h=haut(board,x,y);
	if(h>0){
	   double x,pro,random;
	   x=0.0-((double)h/(double)(2*board->size));
	   pro=1-(double)pow(2,x);
	   pro=pro*1000.0;	
	   srand((unsigned) time(NULL)); 
	   random=rand()%1000;
	   if(pro>=random)
	      return (rand()%h)+1;
	   else
	      return 0;
	}
	else
	   return 0;
}


/*@requires board n'est pas vide
   assigns  *board
   ensures  retirer quelque nombre de jeton, le nombre de jeton à retirer est un nombre aléatoire compris entre 1 et haut. Et affich quelque * sur emplacements de seiemem.
*/
void change_seieme(chessboard *board){
	int x,y,k,s;
	int l;
	int *st=calloc(2,sizeof(int));
	for(x=1;x<board->size;x=x+3){
	    for(y=1;y<board->size;y=y+3){
		
		st[0]=x;
		st[1]=y;
		l=seieme(board,x,y);
		if(l>0){
	   	board->chess[x-1][y][0]='*';
	   	board->chess[x+1][y][0]='*';
	   	board->chess[x][y-1][0]='*';
	   	board->chess[x][y+1][0]='*';
	   	board->chess[x-1][y-1][0]='*';
	   	board->chess[x-1][y+1][0]='*';
	   	board->chess[x+1][y-1][0]='*';
	   	board->chess[x+1][y+1][0]='*';
	   	
		for(k=0;k<l;k++)
		s=retirer(board,st);
			
	   	}
	     }
	}
	s++;
}
