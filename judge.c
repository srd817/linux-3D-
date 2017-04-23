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
#include"seieme.h"
#include"judge.h"

/*@requires board n'est pas vide, x, y et h Supérieur à 0
   assigns  rien
   ensures  retourne le marque de gagnant sur le jeu en variante vue de dessus. si il n'y a pas de gagnant, retourne 0.
*/
int judge_vvdd(chessboard *board,int x,int y,int h){
	int i,j,k;		
	int nb;
	char c=board->chess[x][y][h];
	/*sur une colonne*/
	for(i=1;i<board->size;i=i+3)	{			
		if(i==1)		
		   nb=0;
		k=haut(board,i,y)-1;
	        if(k<0) break;
		else if((board->chess[i][y][k])==c)
		   nb++;
		else
		   break;
		if((3*nb)==(board->size)){
		   if(c=='X')
		      return 1;
		   else if(c=='O')
		      return 2; 
		}
	}
	/*sur une ligne*/
	for(j=1;j<board->size;j=j+3){
		if(j==1)		
		   nb=0;
		k=haut(board,x,j)-1;
	        if(k<0) break;
		if(board->chess[x][j][k]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	}
	/*sur diag quand x==y*/
	if(x==y){
	   for(i=1;i<board->size;i=i+3){
		if(i==1)
		   nb=0;
		k=haut(board,i,i)-1;
	        if(k<0) break;
		else if(board->chess[i][i][k]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else if(c=='O')
		      return 2; 
		}
	   }
	}
	/*sur autre diag*/
	if((x+y)==((board->size)-1)){
	   for(i=1;i<board->size;i=i+3){
		if(i==1)
		   nb=0;
		k=haut(board,i,((board->size)-i-1))-1;
	        if(k<0) break;
		if(board->chess[i][(board->size)-1-i][k]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	   }
	}
	return 0;
	      
}


/*@requires board n'est pas vide, x, y et h Supérieur à 0
   assigns  rien
   ensures   retourne le marque de gagnant sur le jeu en variante 3D. ,si il n'y a pas de gagnant, retourne 0.
*/
int judge_3d(chessboard *board,int x,int y,int h){
	int i,j,k;	
	int nb=0;
	char c=board->chess[x][y][h];
	
	/*sur une colonne , quand  y et h sont des constante */
	for(i=1;i<board->size;i=i+3)	{		
		if(board->chess[i][y][h]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	}
	
	/*sur une ligne , quand x et h sont des constante*/
	nb=0;
	for(j=1;j<board->size;j=j+3){

		if(board->chess[x][j][h]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	}
	
	/*sur haut, quand x et y sont des constante*/
	
	for(i=0;i<board->haut;i++){	
	nb=0;
	for(k=0;k<(board->size)/3;k++)	{	
		if(board->chess[x][y][k+i]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	}
	}
	
	/*  diag 1, quand  h est une constante*/
	if(x==y){
	   nb=0;
	   for(i=1;i<board->size;i=i+3){	
		if(board->chess[i][i][h]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	   }
	}
	
	/*  diag 2,quand  h est une constante*/
	if((x+y)==((board->size)-1)){
	   nb=0;
	   for(i=1;i<board->size;i=i+3){
		j=(board->size)-1-i;
		if(board->chess[i][j][h]==c)
		   nb++;
		else
		   break;
		if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
		}
	    }
	}
	
	 /*  diag 3,quand  x est une constante*/
	   nb=0;
	   k=h;
	   for(j=y;j<board->size;j=j+3){
			
		if(board->chess[x][j][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(j=y-3;j>0;j=j-3){
			
		if(board->chess[x][j][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
		}

	/*  diag 4,quand  x est une constante*/
	   nb=0;
	   k=h;
	   for(j=y;j<board->size;j=j+3){
			
		if(k>=0 && board->chess[x][j][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(j=y-3;j>0;j=j-3){
			
		if(k>=0 && board->chess[x][j][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
		}


	/*  diag 5,quand  y est une constante*/
	   nb=0;
	   k=h;
	   for(i=x;i<board->size;i=i+3){
			
		if(k>=0 && board->chess[i][y][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(i=x-3;i>0;i=i-3){
			
		if(k>=0 && board->chess[i][y][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
		}

	/*  diag 6,quand  y est une constante*/
	   nb=0;
	   k=h;
	   for(i=x;i>0;i=i-3){
			
		if(board->chess[i][y][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(i=x+3;i<board->size;i=i+3){
			
		if(k>=0 && board->chess[i][y][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
	   }
		

	   if(x==y){
	/*  diag 7*,quand  dans niveau x==y */
		nb=0;
	        k=h;
	     for(i=x;i<board->size;i=i+3){
			
		if(k>=0 && board->chess[i][i][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	     }
	   	k=h-1;
	     for(i=x-3;i>0;i=i-3){
			
		if(k>=0 && board->chess[i][i][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	      }
	      if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
	      }


	/*  diag 8,quand  dans niveau x==y*/
	   nb=0;
	   k=h;
	   for(i=x;i>0;i=i-3){
			
		if(k>=0 && board->chess[i][i][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(i=x+3;i<board->size;i=i+3){
			
		if(k>=0 && board->chess[i][i][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
	   }
	}	   

	   if((x+y)==((board->size)-1)){
	/*  diag 9,quand  dans niveau (x+y)==((board->size)-1) */
		nb=0;
	        k=h;
	     for(i=x;i<board->size;i=i+3){
		j=(board->size)-1-i;	
		if(k>=0 && j>=0 && board->chess[i][j][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	     }
	   	k=h-1;
	     for(i=x-3;i>0;i=i-3){
		j=(board->size)-1-i;	
		if(k>=0 && j>=0 && board->chess[i][j][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	      }
	      if(3*nb==board->size){
		   if(c=='X')
		      return 1;
		   else
		      return 2; 
	      }

	   /*  diag 10,quand  dans niveau (x+y)==((board->size)-1) */
	   nb=0;
	   k=h;
	   for(i=x;i>0;i=i-3){
		j=(board->size)-1-i;	
		if(k>=0 && j>=0 && board->chess[i][y][k]==c){
		   nb++;
		   k++;
		}
		else
		   break;
	   }
	   k=h-1;
	   for(i=x+3;i<board->size;i=i+3){
			
		if(k>=0 && j>=0 && board->chess[i][y][k]==c){
		   nb++;
		   k--;
		}
		else
		   break;
	   }
	   if(3*nb==board->size){
		if(c=='X')
		      return 1;
		else
		      return 2; 
	   }
	}
	return 0;
}


/*@requires board n'est pas vide, x, y et h Supérieur à 0
   assigns  rien
   ensures  retourne le marque de gagnant sur le jeu en variante vue de dessus avec option séisme. si il n'y a pas de gagnant, retourne 0.
*/
int judge_seieme_vvdd(chessboard *board){
	int i,j,k,sign,x,o;
	x=0;
	o=0;
	/* Vérifiez tous les sommets*/
	for(i=1;i<board->size;i=i+3)
	    for(j=1;j<board->size;j=j+3){
		k=haut(board,i,j)-1;
		if(k>0){
		   sign=judge_vvdd(board,i,j,k);
		   if(sign==1)
		      x=1;
		   if(sign==2)
		      o=1;
		}
	    }
	if(x==1 && o==1)
	   return 1;
	else if(x==1)
	   return 2;
	else if(o==1)
	   return 3;
	else 
	   return 0;
}


/*@requires board n'est pas vide, x, y et h Supérieur à 0
   assigns  rien
   ensures  retourne le marque de gagnant sur le jeu en variante 3D avec option séisme. si il n'y a pas de gagnant, retourne 0.
*/
int judge_seieme_3d(chessboard *board){
	int i,j,k,h,sign;
	/* Vérifiez tous les points*/
	for(i=1;i<board->size;i=i+3)
	    for(j=1;j<board->size;j=j+3){
		h=haut(board,i,j)-1;
		for(k=0;k<=h;k++)
		if (h>0){
		    sign=judge_3d(board,i,j,k);
		    if(sign==1)
		       return 1;
		    if(sign==2)
		       return 2;
		}
	   }
	return 0;
}
