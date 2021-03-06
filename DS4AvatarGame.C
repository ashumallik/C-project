# C-project// AVATAR GAME
# © Aashutosh Mallik
// Headers
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Mathematical constants	
#define PI 3.14159

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 80
#define DELAY 300
#define DELAY2 200

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

// Number of samples taken to form an average for the gyroscope data
// Feel free to tweak this.  You may actually want to use the moving averages
// code you created last week 
#define NUM_SAMPLES 10  


// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];


// POST: Generates a random maze structure into MAZE[][]
//You will want to use the rand() function and maybe use the output %100.  
//You will have to use the argument to the command line to determine how 
//difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.  
float calc_roll(float x_mag);

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
void main(int argc, char* argv[])
{
	// setup screen    
	initscr();
	refresh();
	
	int diffi = 0;
	int PosX = 0;
	int PosY = 0;
	int prevTime = 0;
	int otTime = 0;
	int t;
	double g_x, g_y, g_z, roll;
	

	// Generate and draw the maze, with initial avatar
	sscanf(argv[1], "%d", &diffi );
	generate_maze(diffi);
	draw_maze();
	
	PosX = NUMCOLS / 2;
	PosY = 0;
	draw_character(PosX, PosY, AVATAR);
	
	
	
 
	// Read gyroscope data to get ready for using moving averages.    

	// Event loop
	do
	{	
	
	scanf("%d, %lf, %lf, %lf", &t, &g_x, &g_y, &g_z);
	
	if((t - prevTime) > DELAY2){
		prevTime = t;
		draw_character(PosX, PosY,EMPTY_SPACE);
		
		if(((g_x) > 0.5) && (g_x <= 1.1) && (PosX != 0)){
			if(MAZE[PosY][PosX-1] == EMPTY_SPACE){
			PosX--;
			}
		}
		else if((g_x > -1.1) && (g_x <= -0.5) && (PosX != NUMCOLS)){
			if(MAZE[PosY][PosX+1] == EMPTY_SPACE){
			PosX++;
			}
		}
		draw_character(PosX, PosY, AVATAR);
		}
		
	if((t - otTime) > DELAY){
		otTime = t;
		draw_character(PosX, PosY,EMPTY_SPACE);
		if(MAZE[PosY+1][PosX] == EMPTY_SPACE){
			PosY++;
		}
		draw_character(PosX, PosY, AVATAR);
	}
	//checks to see if avatar is in a bucket of 1 wall width
	if (MAZE [PosX][PosY+1] == WALL && MAZE [PosX+1][PosY] ==  WALL && MAZE [PosX-1][PosY] == WALL){
		endwin();
	
	}

} while(PosY <= NUMROWS && NUMCOLS != 1); // Change this to end game at right time 

	// Print the win message
	endwin();
	 
	if (NUMCOLS == 1){
		
		printf("YOU WIN!\n");
	}
	
	
	
}



// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void generate_maze(int difficulty){
	int i = 0;
	int j = 0;
	int number = 0;
	srand(time(0));
	for(i = 0; i < NUMROWS; i++){
		for (j = 0; j < NUMCOLS; j++){
			number = rand() % 100;
			if (number < difficulty){
				MAZE[i][j] = WALL;				
			}
			else{
				MAZE[i][j] = EMPTY_SPACE;
			}
		}
	}
}
void draw_maze(void){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < NUMROWS; i++){
		for(j = 0; j < NUMCOLS; j++){
			draw_character(j, i, MAZE[i][j]);
		}
	}
}

float calc_roll(float x_mag){
	double returnVal1;
	if(x_mag > 1){
		x_mag = 1.0;
	}
	else if (x_mag < -1.0){
		x_mag = -1.0;
	}
	returnVal1 = x_mag;
	return returnVal1;
}
