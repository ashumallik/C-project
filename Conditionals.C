# C-project/* SE 185 Lab 5 Wrapper Program */
/* SE 185 Lab 5 Wrapper Program */
# © Aashutosh Mallik
#include <stdio.h>
#include <math.h> 
#define TRUE 1

/* Put your lab 4 functions prototypes here, as well as the prototype for lab 5 */
int close_to(int tolerance, int point, int value);
double mag( double x, double y,double z);

int main (void){
	double t, b1, b2, b3, b4, b5, s;
	double ax, ay, az,gx ,gy ,gz; 
	int stable=0;

while (TRUE) {

	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", &t, &ax, &ay, &az, &b1, &b2, &b3, &b4, &b5, &s );	
	if (close_to(0.10, 1.00, mag(ax,ay,az))){
		
		if (close_to(.20, -1.00,gx)){
			if (stable !=1){
			stable=1;
			printf("Right\n");
			}
		}
		if(close_to(.20,1.00,gx)){
			if (stable !=2){
			stable=2;
			printf("Left\n");
			}
		if(close_to(.20,1.00,gy)){
			if (stable !=3){
			stable=3;
			printf("Top\n");
			}
		}
		if(close_to(.20,1.00,gy)){
			if (stable !=4){
			stable=4;
			printf("Bottom\n");
			}
		}
		if(close_to(.20,1.00,gz)){
			if (stable !=5){
			stable=5;
			printf("Back\n");
			}
		}
			if(close_to(.20,1.00,gz)){
			if (stable !=6){
			stable=6;
			printf("Front\n");
			}
		}
			
		}
		if (b1==1)
		{
			
			break;
		}
		
	}
	
	return 0;
}
double mag(double x,double y, double z)
	{
		double m;
		m= sqrt((x*x)+(y*y)+(z*z));
	return m;
	}
	
double close_to(double tolerance, double point , double value) 
	{
	if (value<= (point-tolerance) && value >= (point+tolerance))
	{
		{
			return 1;
		}
	}	else
	{
		return 0;
	}	
			}
