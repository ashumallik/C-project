# C-project// Lab 10 DS4Talker Skeleton Code
# © Aashutosh Mallik
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 0   // set to 0 to disable debug output

// reads words from the file
// into wl and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) ;

void draw_character(int x, int y, char use);

void printWords(char* wordlist[],int wordCount);

double avg(int buffer[], int num_items);

void updatebuffer(int buffer[], int length, int new_item);

int truex(int x);

void clearln(int ln);

void bookmarkBack(int bookmarks[], int* bookmarkLoc,char sentance[]);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordCount;
	int i,k=0,time = 0;
	
	char sentance[80], currWord[11];
	int bookmarks[50], bookmarkLoc=0;
	
	
	
	int t,b1,b2,b3,b4,r,l,opt,shr,r2,l2,r1,l1,j1,j2,j3,j4,buffery[10]={0,0,0,0,0,0,0,0,0,0},bufferx[10]={0,0,0,0,0,0,0,0,0,0},locx=1,locy=1,prevB1=0,prevB2=1,prevB3=0,prevB4=0, prevR=0, lnNum = 20;
	double gx,gy,gz,javgy,javgx;
	
	wordCount = readWords(wordlist, argv[1]);

	if (DEBUG) {
		printf("Read %d words from %s \n",wordCount, argv[1]);
		for (i = 0; i< wordCount; i++) {
			printf("%s,", wordlist[i]);

			}
		printf("\n");
		}

// most of your code goes here. Don't forget to include the ncurses library 
	
	
	
	initscr();
	refresh();
	
	memset(sentance,0,strlen(sentance));
	
	printWords(wordlist,wordCount);
	refresh();
	draw_character(locx,locy,'*');
	
	
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",&t,&gx,&gy,&gz,&b1,&b2,&b3,&b4,&r,&l,&opt,&shr,&r2,&l2,&r1,&l1,&j1,&j2,&j3,&j4);

	
	
	while(opt == 0){
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",&t,&gx,&gy,&gz,&b1,&b2,&b3,&b4,&r,&l,&opt,&shr,&r2,&l2,&r1,&l1,&j1,&j2,&j3,&j4);
		
		updatebuffer(buffery,10,j4);
		updatebuffer(bufferx,10,j3);
		
		
		
		
		if(t>k+150){
			
			
			javgy = avg(buffery,10);
			javgx = avg(bufferx,10);
		
			if(javgy<-110 && locy > 1){
				draw_character(locx,locy,' ');
				locy--;
				draw_character(locx,locy,'*');
			}
			if(javgy>110 && wordCount > 5*(locy) + truex(locx)){	
				draw_character(locx,locy,' ');
				locy++;
				draw_character(locx,locy,'*');
			}
			if(javgx<-110 && locx > 1){
				
				draw_character(locx,locy,' ');
				locx -= 20;
				draw_character(locx,locy,'*');
			}
			if(javgx>110 && locx < 81 && wordCount > 5*(locy-1) + truex(locx)+1){
				
				draw_character(locx,locy,' ');
				locx += 20;
				draw_character(locx,locy,'*');
			}		
			k = t;
		}
		
			
		
		if( b1 == 1 && wordCount > 5*(locy-1) + truex(locx) && prevB1==0){
			bookmarks[bookmarkLoc] = strlen(sentance);
			bookmarkLoc++;
			
			strcpy(currWord,wordlist[5*(locy-1) + truex(locx)]);
			
			strcat(sentance," ");
			
			strcat(sentance,currWord);
			
			mvprintw(lnNum,1,"%s",sentance);
			refresh();
			
		}
		
		else if( b2 == 1 && wordCount > 5*(locy-1) + truex(locx) && prevB2==0){
			bookmarks[bookmarkLoc] = strlen(sentance);
			bookmarkLoc++;
			
			strcpy(currWord,wordlist[5*(locy-1) + truex(locx)]);
			
			strcat(sentance," ");
			
			currWord[0] = toupper(currWord[0]);
			
			strcat(sentance,currWord);
			
			
			mvprintw(lnNum,1,"%s",sentance);
			refresh();
			
		}
		
		else if( b4 == 1 && wordCount > 5*(locy-1) + truex(locx) && prevB4==0){
			bookmarks[bookmarkLoc] = strlen(sentance);
			bookmarkLoc++;
			
			strcpy(currWord,wordlist[5*(locy-1) + truex(locx)]);
			strcat(sentance,currWord);
			
			
			mvprintw(lnNum,1,"%s",sentance);
			refresh();
			
		}
		
		else if( b3 == 1 && prevB3 == 0){
			
			clearln(lnNum);
			
			bookmarkBack(bookmarks,&bookmarkLoc,sentance);
			
			mvprintw(lnNum,1,"%s",sentance);
			
			refresh();
			
		}
		
		else if( r == 1 && prevR == 0){
			lnNum+=2;
			
			memset(sentance,0,strlen(sentance));
			
			memset(bookmarks,0,50);
			
			bookmarkLoc = 0;
			
			
		}
		
		
		prevB1 = b1;
		prevB2 = b2;
		prevB3 = b3;
		prevB4 = b4;
		prevR = r;
	}
	
    
	endwin();
	
	return 0;
}
	
	
	
	void printWords(char* wordlist[],int wordCount){
		
		int i=0;
		while(TRUE){
			if(i>=wordCount) return;
			mvprintw(i/5+1,3,"%s",wordlist[i]);
			if(i+1>=wordCount) return;
			mvprintw(i/5+1,23,"%s",wordlist[i+1]);
			if(i+2>=wordCount) return;
			mvprintw(i/5+1,43,"%s",wordlist[i+2]);
			if(i+3>=wordCount) return;
			mvprintw(i/5+1,63,"%s",wordlist[i+3]);
			if(i+4>=wordCount) return;
			mvprintw(i/5+1,83,"%s",wordlist[i+4]);
			
			i += 5;
		}
		return;
	}
	
	
	
double avg(int buffer[], int num_items){
	int i;
	double sum=0;
	for(i=0;i<num_items;i++){
		sum += buffer[i];
	}
	
	return sum/num_items;
}

void updatebuffer(int buffer[], int length, int new_item){
	int i;
	for(i = 0; i<length-1; i++){
		buffer[i] = buffer[i+1];
	}
	buffer[length-1] = new_item;
	return;
}
	
int truex(int x){
	return (x-1)/20;
}	
	
void clearln(int ln){
	int i;
	for(i = 0; i<80;i++){
		draw_character(i,ln,' ');
	}
	
}

void bookmarkBack(int bookmarks[], int* bookmarkLoc,char sentance[]){
	
	char temp[80];
	strcpy(temp,sentance);
	memset(sentance,0,strlen(sentance));
	
	strncpy(sentance,temp,bookmarks[*bookmarkLoc-1]);
	
	bookmarks[*bookmarkLoc] = 0;
	
	
	if(bookmarkLoc > 0){
		*bookmarkLoc -= 1;
	}

}






	
	
	
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}	

// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) {
        int len = strlen(s) ;
        int x;
        if (len ==0) return;
        x = len-1;
        while (isspace(s[x]) && (x>=0)) {
                s[x] = '\0';
                x--;
                }
        }


// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename) {
	int numread =0;
	char line[WORDLEN];
	char *p;
	FILE* fp = fopen(filename,"r");
	while (!feof(fp)) {
		p  =fgets(line, WORDLEN, fp);
		if (!feof(fp) && p !=NULL) {
			trimws(line);
			wl[numread] = (char *)  malloc(strlen(line)+1);
			strcpy(wl[numread], line);
			numread++;
			}
		} 
	fclose(fp);
	return numread;	
	}
