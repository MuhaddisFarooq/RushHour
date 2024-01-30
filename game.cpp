//============================================================================
// Name        : .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <ctime>
#include<stdlib.h>
#include<stdio.h>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
 int seconds = 0;
int MainDisplayArray[20][20];
int nScore = 0, time_passed;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


int xCar, yCar;
int xTarget, yTarget;
bool isFree = true;

// if carColor is true Red taxi, if false yellow taxi
bool carColor;

void carChoice(){
	cout<<"Enter 1 to play with RED taxi 2 for YELLOW taxi /n NOTE: enter in small characters"<<endl;	    //User selects between yellow taxi or red taxi
	int col;
	cin>>col;
	if(col == 1){
		cout<<"R"<<endl;
		carColor = true;
	}
	
	else if(col == 2){
		cout<<"Y"<<endl;
		carColor = false;
	}
	
	
}
void nameChoice(){					//user enters his/her name than
	cout<<"Enter Your Name" <<endl;
	char n;
	cin>>n;
	time_passed = 180;
	
	
}

void drawCar(int i, int j) {			

	xCar = (i * 45) + 70;
	yCar = 590 - (j * 25);
	if(carColor){
	DrawRectangle(xCar, yCar, 20, 8, colors[RED]);
	}
	
	else{
		DrawRectangle(xCar, yCar, 20, 8, colors[YELLOW]);
	}
	DrawCircle(xCar-1, yCar-3, 5, colors[BLACK]);
	
	DrawCircle(xCar+19, yCar-3, 5, colors[BLACK]);
	glutPostRedisplay();
}
int counter = 0;
void move() {                       //Moving cars and preventing them from existing grid
	counter += 1;
	if (counter == 5) {
	counter = 0;
	int pos = rand() % 4;
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (MainDisplayArray[i][j] == 6) {
				//LEFT KEY
				if (pos == 1 and MainDisplayArray[i + 1][j] != 1 and MainDisplayArray[i + 1][j] != 2 and MainDisplayArray[i + 1][j] != 3 and MainDisplayArray[i + 1][j] != 4 and 				MainDisplayArray[i + 1][j] != 5 and MainDisplayArray[i + 1][j] != 6 and (i*45)<0){
					MainDisplayArray[i + 1][j] = 6;
					MainDisplayArray[i][j] = 0;
				} 
				//RIGHT KEY
				else if (pos == 0 and MainDisplayArray[i - 1][j] != 1 and MainDisplayArray[i - 1][j] != 2 and MainDisplayArray[i - 1][j] != 3 and MainDisplayArray[i - 1][j] != 4 and 				MainDisplayArray[i - 1][j] != 5 and MainDisplayArray[i - 1][j] != 6 and (i*45)<0) {
					MainDisplayArray[i - 1][j] = 6;
					MainDisplayArray[i][j] = 0;
				}
				//DOWN KEY
				else if (pos == 2 and MainDisplayArray[i][j+1] != 1 and MainDisplayArray[i][j+1] != 2 and MainDisplayArray[i][j+1] != 3 and MainDisplayArray[i][j+1] != 4 and 				MainDisplayArray[i][j+1] != 5 and MainDisplayArray[i][j+1] != 6 and (j*25)<960) {
					MainDisplayArray[i][j+1] = 6;
					MainDisplayArray[i][j] = 0;
				} 
				//UP KEY
				else if (pos == 3 and MainDisplayArray[i][j-1] != 1 and MainDisplayArray[i][j-1] != 2 and MainDisplayArray[i][j-1] != 3 and MainDisplayArray[i][j-1] != 4 and 				MainDisplayArray[i][j-1] != 5 and MainDisplayArray[i][j-1] != 6 and (j*25)<960) {
					MainDisplayArray[i][j-1] = 6;
					MainDisplayArray[i][j] = 0;
				} 
			}
		}
	} 
	}
}
void drawOtherCar(int i, int j) {			
	int xOtherCar = (i * 45) + 70;
	int yOtherCar = 590 - (j * 25);
	DrawRectangle(xOtherCar, yOtherCar, 20, 8, colors[MAGENTA]);		//Upper body
	DrawCircle(xOtherCar-1, yOtherCar-3, 5, colors[BLACK]);		//Lower body
	DrawCircle(xOtherCar+19, yOtherCar-3, 5, colors[BLACK]);		//Lower body
	glutPostRedisplay();
}

void drawPassenger(int i, int j)
{
	int xPassenger = (i * 45) + 70;
	int yPassenger = 590 - (j * 25);
	DrawCircle(xPassenger + 15, yPassenger + 5, 4, colors[BLACK]);	//Upper body
	DrawLine(xPassenger + 15, yPassenger + 5, xPassenger + 15, yPassenger - 5, 2, colors[BLACK]);	//Lower Body
	DrawLine(xPassenger + 15, yPassenger -5, xPassenger + 10, yPassenger - 8, 2, colors[BLACK]);	//Lower Body
	DrawLine(xPassenger + 15, yPassenger - 5, xPassenger + 20, yPassenger - 8, 2, colors[BLACK]);	//Lower Body
	glutPostRedisplay();
}

void drawObstacle(int i, int j)
{
	int xObstacle = (i * 45) + 70;
	int yObstacle = 590 - (j * 25);
	DrawRectangle(xObstacle - 10, yObstacle - 15, 45, 25, colors[BLACK]);
	glutPostRedisplay();
}

void drawTarget(int i, int j)
{
	int xObstacle = (i * 45) + 70;
	int yObstacle = 590 - (j * 25);
	DrawRectangle(xObstacle - 10, yObstacle - 15, 45, 25, colors[GREEN]);
	glutPostRedisplay();
}

void drawTree(int i, int j)
{
	int xTree = (i * 45) + 70;
	int yTree = 590 - (j * 25);
	DrawTriangle(xTree, yTree - 5, xTree + 30, yTree-5, xTree + 15, yTree + 15, colors[GREEN]);			//Upper Body
	DrawLine(xTree + 15, yTree, xTree + 15, yTree -15, 4, colors[BROWN]);					//Lower Body
	glutPostRedisplay();
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		
		
		
	if (nScore < 100)
	{
		glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
				1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawLine(60 , 600 ,  960 , 600 , 2 , colors[BLACK] );
		DrawLine(60 , 100 ,  960 , 100 , 2 , colors[BLACK] );
		DrawLine(60 , 600 ,  60 , 100 , 2 , colors[BLACK] );	
		DrawLine(960 , 600 ,  960 , 100 , 2 , colors[BLACK] );	

		for (int i=105; i<960; i+=45)
		{									//Grid
			DrawLine(i , 600 ,  i , 100 , 2 , colors[BLACK] );
		}

		for (int i=125; i<600; i+=25)
		{
			DrawLine(60 , i ,  960 , i , 2 , colors[BLACK] );
		}
		
		//Display Score 
		DrawString( 50, 800, "Score=" + to_string(nScore), colors[RED]);
		//Display Time
		DrawString( 450, 800, "Time=" + to_string(time_passed), colors[RED]);
		
		for (int i=0; i<20; i++)
		{
			for (int j=0; j<20; j++)
			{
				if (MainDisplayArray[i][j] == 1)		//Car
				{
					drawCar(i, j);
				}

				if (MainDisplayArray[i][j] == 2)		//Passenger
				{
					drawPassenger(i, j);
				}

				if (MainDisplayArray[i][j] == 3)		//Obstacle
				{
					drawObstacle(i, j);
				}
				if (MainDisplayArray[i][j] == 4)		//Target
				{
					drawTarget(i, j);
				}
				if (MainDisplayArray[i][j] == 5)		//Tree
				{
					drawTree(i, j);
				}
				if (MainDisplayArray[i][j] == 6)		//Other Car
				{
					drawOtherCar(i, j);
				}
			}
		}
	}

	else 
	{
		glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
				1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString( 500, 400, "YOU WIN!!", colors[RED]);
	}
	glutSwapBuffers(); // do not modify this line..

}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	int i = (xCar - 70) / 45;
	int j = -(yCar - 590) / 25;
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/ && (xCar>90) && 
			MainDisplayArray[i-1][j] != 3 &&		
			MainDisplayArray[i-1][j] != 2 &&
			MainDisplayArray[i-1][j] != 5 &&
			MainDisplayArray[i-1][j] != 6) {
		// what to do when left key is pressed...
		MainDisplayArray[i][j] = 0;
		xCar -= 45;
		int new_i = (xCar - 70) / 45;
		int new_j = -(yCar - 590) / 25;
		if (MainDisplayArray[new_i][new_j] == 4)
		{
			nScore += 10;
			isFree = true;
		}
		MainDisplayArray[new_i][new_j] = 1;
	 }
	
	  if (key == GLUT_KEY_LEFT & MainDisplayArray[i-1][j] == 2) {	//Person -5
		

		nScore -= 5;
	}
	  if (key == GLUT_KEY_LEFT & MainDisplayArray[i-1][j] == 3) {	//Obstacle -2,-4
	  	if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;
		  }
	}
	
	 if (key == GLUT_KEY_LEFT & MainDisplayArray[i-1][j] == 5) {		//Tree -2,-4
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	if (key == GLUT_KEY_LEFT & MainDisplayArray[i][j - 1] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_LEFT & MainDisplayArray[i-1][j] == 6) {		//Other Car -3,-2
		if(carColor){
			  nScore -= 3;

		  }
		  else{
			  nScore -= 2;

		  }
	}
	




	else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/ && (xCar<920) && 
			MainDisplayArray[i+1][j] != 3 &&
			MainDisplayArray[i+1][j] != 2 &&
			MainDisplayArray[i+1][j] != 5 &&
			MainDisplayArray[i+1][j] != 6) {
		MainDisplayArray[i][j] = 0;
		xCar += 45;
		int new_i = (xCar - 70) / 45;
		int new_j = -(yCar - 590) / 25;
		if (MainDisplayArray[new_i][new_j] == 4)
		{
			nScore += 10;
			isFree = true;
		}
		MainDisplayArray[new_i][new_j] = 1;
	} 
	
	
	 if (key == GLUT_KEY_RIGHT & MainDisplayArray[i+1][j] == 2) { //person
		nScore -= 5;
	}
	if (key == GLUT_KEY_RIGHT & MainDisplayArray[i+1][j] == 3) {	//Obstacle -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	
	 if (key == GLUT_KEY_RIGHT & MainDisplayArray[i+1][j] == 5) {		//Tree -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	if (key == GLUT_KEY_RIGHT & MainDisplayArray[i][j-1] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_RIGHT & MainDisplayArray[i+1][j] == 6) {		//Other Car -3
		if(carColor){
			  nScore -= 3;

		  }
		  else{
			  nScore -= 2;

		  }
	}
	
	else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ && yCar < 580 && 
			MainDisplayArray[i][j-1] != 3 &&
			MainDisplayArray[i][j-1] != 2 &&
			MainDisplayArray[i][j-1] != 5 &&
			MainDisplayArray[i][j-1] != 6) {
		MainDisplayArray[i][j] = 0;
		yCar += 25;
		int new_i = (xCar - 70) / 45;
		int new_j = -(yCar - 590) / 25;
		if (MainDisplayArray[new_i][new_j] == 4)
		{
			nScore += 10;
			isFree = true;
		}
		MainDisplayArray[new_i][new_j] = 1;
	}
	if (key == GLUT_KEY_UP & MainDisplayArray[i][j - 1] == 2) {
		nScore -= 5;
	}
	if (key == GLUT_KEY_UP & MainDisplayArray[i][j-1] == 3) {	//Obstacle -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	
	 if (key == GLUT_KEY_UP & MainDisplayArray[i][j-1] == 5) {		//Tree -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	if (key == GLUT_KEY_UP & MainDisplayArray[i + 1][j] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_UP & MainDisplayArray[i - 1][j] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_UP & MainDisplayArray[i][j-1] == 6) {		//Other Car -3
		if(carColor){
			  nScore -= 3;

		  }
		  else{
			  nScore -= 2;

		  }
	}

	

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ && yCar > 120 && 
			MainDisplayArray[i][j+1] != 3 &&
			MainDisplayArray[i][j+1] != 2 &&
			MainDisplayArray[i][j+1] != 5 &&
			MainDisplayArray[i][j+1] != 6) {
				MainDisplayArray[i][j] = 0;
		yCar -= 25;
		int new_i = (xCar - 70) / 45;
		int new_j = -(yCar - 590) / 25;
		if (MainDisplayArray[new_i][new_j] == 4)
		{
			nScore += 10;
			isFree = true;
		}
		MainDisplayArray[new_i][new_j] = 1;
	}
	
	if (key == GLUT_KEY_DOWN & MainDisplayArray[i][j + 1] == 2) {
		nScore -= 5;	
	}
	if (key == GLUT_KEY_DOWN & MainDisplayArray[i][j+1] == 3) {	//Obstacle -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	
	 if (key == GLUT_KEY_DOWN & MainDisplayArray[i][j+1] == 5) {		//Tree -2
		if(carColor){
			  nScore -= 2;

		  }
		  else{
			  nScore -= 4;

		  }
	}
	if (key == GLUT_KEY_DOWN & MainDisplayArray[i + 1][j] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_DOWN & MainDisplayArray[i - 1][j] == 6) {		//Carovertaking +1
		if(carColor){
			  nScore += 1;

		  }
		  else{
			  nScore += 1;

		  }
	}
	if (key == GLUT_KEY_DOWN & MainDisplayArray[i][j+1] == 6) {		//Other Car -3
		if(carColor){
			  nScore -= 3;

		  }
		  else{
			  nScore -= 2;

		  }
	}
	

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	else if (key == ' ' && isFree)
	{
		int i = (xCar - 70) / 45;
		int j = -(yCar - 590) / 25;
		
		if (MainDisplayArray[i][j+1] == 2)			//Randomization of passenger and target
		{
			MainDisplayArray[i][j+1] = 0;
			xTarget = rand() % 20;
			yTarget = rand() % 20;
			while (MainDisplayArray[xTarget][yTarget] != 0 && xTarget != i && yTarget != j + 1)
			{
				xTarget = rand() % 20;
				yTarget = rand() % 20;
			}

			MainDisplayArray[xTarget][yTarget] = 4;
			int x = rand() % 20;
			int y = rand() % 20;
			while (MainDisplayArray[x][y] != 0)
			{
				x = rand() % 20;
				y = rand() % 20;
			}
			MainDisplayArray[x][y] = 2;

			isFree = false;
		}
		else if (MainDisplayArray[i][j-1] == 2)
		{
			MainDisplayArray[i][j-1] = 0;
			xTarget = rand() % 20;
			yTarget = rand() % 20;
			while (MainDisplayArray[xTarget][yTarget] != 0 && xTarget != i && yTarget != j - 1)
			{
				xTarget = rand() % 20;
				yTarget = rand() % 20;
			}

			MainDisplayArray[xTarget][yTarget] = 4;
			int x = rand() % 20;
			int y = rand() % 20;
			while (MainDisplayArray[x][y] != 0)
			{
				x = rand() % 20;
				y = rand() % 20;
			}
			MainDisplayArray[x][y] = 2;
			isFree = false;
		}
		else if (MainDisplayArray[i+1][j] == 2)
		{
			MainDisplayArray[i+1][j] = 0;
			xTarget = rand() % 20;
			yTarget = rand() % 20;
			while (MainDisplayArray[xTarget][yTarget] != 0 && xTarget != i+1 && yTarget != j)
			{
				xTarget = rand() % 20;
				yTarget = rand() % 20;
			}

			MainDisplayArray[xTarget][yTarget] = 4;
			int x = rand() % 20;
			int y = rand() % 20;
			while (MainDisplayArray[x][y] != 0)
			{
				x = rand() % 20;
				y = rand() % 20;
			}
			MainDisplayArray[x][y] = 2;
			isFree = false;
		}
		else if (MainDisplayArray[i-1][j] == 2)
		{
			MainDisplayArray[i-1][j] = 0;
			xTarget = rand() % 20;
			yTarget = rand() % 20;
			while (MainDisplayArray[xTarget][yTarget] != 0 && xTarget != i-1 && yTarget != j)
			{
				xTarget = rand() % 20;
				yTarget = rand() % 20;
			}

			MainDisplayArray[xTarget][yTarget] = 4;
			int x = rand() % 20;
			int y = rand() % 20;
			while (MainDisplayArray[x][y] != 0)
			{
				x = rand() % 20;
				y = rand() % 20;
			}
			MainDisplayArray[x][y] = 2;
			isFree = false;
		}
	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {
	seconds += 100;
	if (seconds % 1000 == 0) {
		time_passed -= 1;
	}
	move();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100.0, Timer, 0);
}	

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	//Car choice
	//Name choice
	carChoice();
	nameChoice();
	
	
	
	

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Muhaddis Farooq"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	
	

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	for (int i=0; i<20; i++)
	{
		for (int j=0; j<20; j++)
		{
			MainDisplayArray[i][j] = 0;
		}
	}
	int nCarRow = 0;
	int nCarColumn = 0;
	MainDisplayArray[nCarRow][nCarColumn] = 1;
	xCar = (nCarColumn * 45) + 70;
	yCar = (nCarColumn * 25) + 590;
	srand((unsigned) time(0));
	int nPassengers = (rand() % 3) + 3;		//For Passengers Also randomization of their locations
	for (int i=0; i<nPassengers; i++)
	{
		int x = rand() % 20;
		int y = rand() % 20;
		while (MainDisplayArray[x][y] != 0)
		{
			x = rand() % 20;
			y = rand() % 20;
		}
		MainDisplayArray[x][y] = 2;
	}
	int nObstacles = 50;				//For Obstacles also randomization of their locations
	for (int i=0; i<nObstacles; i++)
	{
		int x, y;
		x = rand() % 20;
		y = rand() % 20;
		while (MainDisplayArray[x][y] != 0)
		{
			x = rand() % 20;
			y = rand() % 20;
		}
		MainDisplayArray[x][y] = 3;
	}

	int nTrees = 10;				//For Trees also randomization of their locations
	for (int i=0; i<nTrees; i++)
	{
		int x, y;
		x = rand() % 20;
		y = rand() % 20;
		while (MainDisplayArray[x][y] != 0)
		{
			x = rand() % 20;
			y = rand() % 20;
		}
		MainDisplayArray[x][y] = 5;
	}
	int nCars = 5;					//For other cars also randomization of their locations
	for (int i=0; i<nCars; i++)
	{
		int x, y;
		x = rand() % 25;
		y = rand() % 25;
		while (MainDisplayArray[x][y] != 0)
		{
			x = rand() % 25;
			y = rand() % 25;
		}
		MainDisplayArray[x][y] = 6;
	}


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
