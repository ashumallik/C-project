# C-project#include <stdio.h>
#include <math.h>
# © Aashutosh Mallik
#define TRUE 1

double mag(double ax, double ay, double az);
int close_to(double tolerance, double point, double value);

int main(void){
	
	int t, i = 0, u = 0, starting, finaltime;
	double ax, ay, az;
	double distance;
	double startingPos = 0.0, currentPos;
	double prevVel = 0.0, currentVel;
	double convertedTime;
	double prevTime = 0;
	
	printf("Ok, I'm receiving data.\n");
	printf(" I'm waiting");
	while(close_to(0.1, 0.00, mag(ax, ay, az))) {
		scanf("%d,%lf,%lf,%lf", &t, &ax, &ay, &az);
		i++;
		if ((i % 3) == 0){
			printf(".");
			fflush(stdout);
		}
		
	}
	starting = t;
	printf("\nI'm falling");
	prevTime = starting;
	while(TRUE) {
		scanf("%d,%lf,%lf,%lf", &t, &ax, &ay, &az);
		u++;
		if ((u % 3) == 0){
			printf("!");
			fflush(stdout);
		}
		if (mag(ax, ay, az) > 1){
			break;
		}
		
		currentVel = prevVel + ((9.8 - (mag(ax, ay, az) * 9.8)) * ((t - prevTime)/1000));
		currentPos = startingPos + (currentVel * ((t - prevTime)/1000));
		prevTime = t;
		prevVel = currentVel;
		startingPos = currentPos;
		
	}
	finaltime = t - starting;
	convertedTime = finaltime / 1000.0;
	distance = ((0.5)*(9.8)*(pow(convertedTime,2)));
	printf("I fell %lf meters in %lf seconds.", distance, convertedTime);
	

	printf("\nCompensating for air resistance, the fall was %lf meters.", currentPos);
	
	
	
	
return 0;
}

double mag(double ax, double ay, double az) {
	double magnitude;
	magnitude = sqrt(pow(ax,2) + pow(ay,2) + pow(az,2));
	
	return magnitude;
}

int close_to(double tolerance, double point, double value) {
	if ((value <= (point + tolerance)) && (value >= (point - tolerance))){
		return 1;
	}
	else {
		return 0;
	}
	}
