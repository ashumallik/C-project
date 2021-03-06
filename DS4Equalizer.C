# C-project// SE 185 lab7.c
//# © Aashutosh Mallik
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when left button is pressed
//  False Otherwise
//POST: it modifies its arguments to return values read from the input line.
int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT, int* Button_joyStickvalue); 

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);
int joyStick(int joyStickvalue);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 79 characters wide.
void graph_line(int number);

int main()
{
	double x, y, z;			// magnitude values of x, y, and z
	int b_Up, b_Down, b_Left, b_Right, b_joyStickvalue;	// variables to hold the button statuses
	double roll_rad, pitch_rad;		// value of the roll measured in radians
	int scaled_value; 	// value of the roll adjusted to fit screen display
	int state = 1, t=0;
	//insert any beginning needed code here

	do
	{
		read_acc(&x, &y, &z, &t, &b_Up, &b_Down, &b_Left, &b_Right, &b_joyStickvalue);// Get line of input
		
		roll_rad = roll(x);
		pitch_rad = pitch(y);// calculate roll and pitch.  Use the buttons to set the condition for roll and pitch
		
		if(b_Up == 1){
			if(state = 1){state=2;}
			else{state=1;}
		}
		if (b_Down == 1){
			state = 2;
		}
		if (b_Right == 1)
			state = 3;
		// switch between roll and pitch(up vs. down button)
	if (state == 1){
		scaled_value = scaleRadsForScreen(-roll_rad);
	}
	else if (state == 2){
		scaled_value = scaleRadsForScreen(-pitch_rad);
	}
	else if (state == 3){
		scaled_value = joyStick(b_joyStickvalue);
	}
		// Scale your output value
	graph_line(scaled_value);
		// Output your graph line


		fflush(stdout);
	} while ( b_Left != 1); // Modify to stop when left button is pressed
	return 0;
}
int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT, int* Button_joyStickvalue){
	int hi, ji, jv;
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d", time, a_x, a_y, a_z, Button_UP, Button_RIGHT, Button_DOWN, Button_LEFT, Button_joyStickvalue, &hi, &ji, &jv);
	if(Button_LEFT != 0){
			return 1;
	}
return 0;
	}
double roll(double x_mag){
	double returnVal1;
	if(x_mag >= 1.0){
		returnVal1 =  asin(1.0);
	}
	else if(x_mag <= -1.0){
		returnVal1 =  asin(-1.0);
	}
	else{
		returnVal1 =  asin(x_mag);
	}
	
	return returnVal1;
}
double pitch(double y_mag){
	double returnVal2;
	if(y_mag >= 1.0){
		returnVal2 = asin(1.0);
	}
	else if(y_mag <= -1.0){
		returnVal2 = asin(-1.0);
	}
	else{
		returnVal2 = asin(y_mag);
	}
	
	return returnVal2;
}
int scaleRadsForScreen(double rad){
	double returnVal3;
	returnVal3 = rad * (78.0/PI);
	return returnVal3;
}
void print_chars(int num, char use){
	int i;
	for(i=0; i < num; i++){
		printf("%c", use);//use the character n number of times
		}
	}
void graph_line(int number){
	if(number < 0 ){
		print_chars(39-(number * -1), ' ');
		print_chars(number * -1, 'l');
		
	
	}
	else if(number > 0){
	
		print_chars(39, ' ');
		print_chars(number, 'r');
	}
	else if(number == 0){
		print_chars(39, ' ');
		print_chars(1, '0');
	}
	print_chars(1, '\n');
}	
int joyStick(int joyStickvalue){
	return(joyStickvalue/127.0)*39.0;
	
}

