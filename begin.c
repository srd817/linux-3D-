#include<stdio.h>
#include<termios.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>  
#include<time.h>

#include"keys.h"
#include"directions.h"
#include"menu.h"
#include"new.h"
#include"seieme.h"
#include"judge.h"
#include"begin.h"


/*@requires board n'est pas vide, i>0
   assigns  board
   ensures  L'ensemble du processus du jeu
*/
void begin(chessboard * board,int i){
	print_init(board);
	int dir,h,sign;
	int *stu = malloc(sizeof(int)*2);
	stu[0]=1;
	stu[1]=1;
	int turn=0;
	
	print_board(board,stu);
	print_turn(turn);
	while(1){
	    dir=direction();
	/*judge la bouton */
	    if(dir==PLACE){
	/* poser */
		if(place(board,stu,turn)){
		   if(i>1){
		      change_seieme(board);
		   }
		   print_board(board,stu);
		   print_turn(turn);
		   h=haut(board,stu[0],stu[1])-1;
	/*Mode 0*/
		   if(i==0){
		      	sign=judge_vvdd(board,stu[0],stu[1],h);
			
			if(sign==1)
			   printf("\n X win.\n");
			if(sign==2)
			   printf("\n O win.\n");
			if(sign>0){
			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);
				printf("c'est fini.Appuyez sur Q\n");
			   }
		           return ;
			}
		   }
	/*Mode 1*/
		   if(i==1){
		    	sign=judge_3d(board,stu[0],stu[1],h);
			if(sign==1)
			   printf("\n X win.\n");
			if(sign==2)
			   printf("\n O win.\n");
			if(sign>0){
			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);
				printf("c'est fini.Appuyez sur Q");
			   }
		           return ;
			}
		   }
	/*Mode 2*/
		   if(i==2){
			sign=judge_seieme_vvdd(board);
			if(sign==1)
			   printf("\n X et O win.\n");
			if(sign==2)
			   printf("\n X win.\n");
			if(sign==3)
			   printf("\n O win.\n");
			if(sign>0){
			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);
				printf("c'est fini.Appuyez sur Q");
			   }
		           return ;
			}
		   }
	/*Mode 3*/
		   if(i==3){ 
			sign=judge_seieme_3d(board);
		      	if(sign==1)
			   printf("\n X win.\n");
			if(sign==2)
			   printf("\n O win.\n");
			if(sign>0){
			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);
				printf("c'est fini.Appuyez sur Q");
			   }
		           return ;
			}
		   }
		   turn++;
		}
		else {
		   print_board(board,stu);
		   print_turn(turn);
		   printf("c'est full. ");
		}
	    }
	/*retiere, seulement mode 0 et mode 2 peut utiliser retirer pour victorieux*/
	    else if(dir==RETIRER){
		if(retirer(board,stu))
		    printf("Il n'y a pas de chess.");
		else {
		    if(i>1)
		      change_seieme(board);
		    print_board(board,stu);
		    print_turn(turn);
		    turn++;
		    h=haut(board,stu[0],stu[1])-1;
	/* judge Mode 0*/
		    if(i==0){
		      	sign=judge_vvdd(board,stu[0],stu[1],h);
			if(sign==1)
			   printf("\n X win.\n");
			if(sign==2)
			   printf("\n O win.\n");
			if(sign>0){

			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);	
				printf("c'est fini. Appuyez sur Q");
			   }
		           return ;
			}
		    }
	/* judge Mode 2*/
		    if(i==2){
			sign=judge_seieme_vvdd(board);
			if(sign==1)
			   printf("\n X et O win.\n");
			if(sign==2)
			   printf("\n X win.\n");
			if(sign==3)
			   printf("\n O win.\n");
			if(sign>0){
			   while(dir!=EXIT){
				dir=direction();
				stu=chess_keys(board,dir,stu);	
	                        print_board(board,stu);
		                print_turn(turn);
				printf("c'est fini.Appuyez sur Q");
			   }
		           return ;
			}
		   }
		}
	    }
	/* exit */
	    else if(dir==EXIT){
		system("clear");
		return ;
	    }
	    else{
	    	stu=chess_keys(board,dir,stu);	
	        print_board(board,stu);
		print_turn(turn);
	    }	
	}
	
	
}




