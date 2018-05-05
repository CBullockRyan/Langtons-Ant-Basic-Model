/*********************************************************************
** Program Filename: LangtonAnt
** Author: Cassidy Bullock
** Date: June 5th, 2016
** Description: Simulates Langton's Ant
** Input: filename, starting X, starting Y, starting direction, number of iterations
** Output: prints out the movement of the ant for each step it takes
*********************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

/*This structure contains
*information about the ant
*and the ant's position*/
struct ant{
	string direction;
	bool color;
	int row;
	int column;
};

/*********************************************************************
** Function: countflags
** Description: checks to make sure user has input all the flags
				in the correct areas.
** Parameters: argc, argv
** Pre-Conditions: must have user inputs
** Post-Conditions: will return true if all the flags exist
*********************************************************************/ 
bool countflags(int argc, char *argv[]){
	bool Xexist, Yexist, Nexist, Fexist, Dexist;
	for(int i=1; i<argc; i+=2){
		if(strcmp(argv[i], "-f")==0){
			Fexist=1;
		}
		else if(strcmp(argv[i], "-x")==0){
			Xexist=1;
		}
		else if(strcmp(argv[i], "-y")==0){
			Yexist=1;
		}
		else if(strcmp(argv[i], "-d")==0){
			Dexist=1;
		}
		else if(strcmp(argv[i], "-n")==0){
			Nexist=1;
		}
	}
	return (Xexist&&Yexist&&Nexist&&Fexist&&Dexist);
}

/*********************************************************************
** Function: processInputs
** Description: checks to see if command line arguments have been put in
				correctly. If they haven't it will display correct format.
** Parameters: argc, argv, begin
** Pre-Conditions: program must be running
** Post-Conditions: will return true if command line arguments look correct
*********************************************************************/ 
bool processInputs(int argc, char *argv[]){
	if(argc!=11){
		cout<<"There are not enough arguments for the simulation."<<endl;
		cout<<"Correct input format: "<<endl<<"./LA -f filename -d up -x 2 -y 4 -n 20"<<endl;
		return 0;
	}
	if(!countflags(argc, argv)){
		cout<<"Input arguments not input correctly"<<endl;
		cout<<"Correct input format: "<<endl<<"./LA -f filename -d up -x 2 -y 4 -n 20"<<endl;
		return 0;
	}
	return 1;
}

/*********************************************************************
** Function: searchString
** Description: searches for the target flag and returns the next string
** Parameters: argv, argc, target
** Pre-Conditions: assume smart user who knows what to enter into the 
					command line
** Post-Conditions: outputs the string value next to the flag
*********************************************************************/ 
string searchString(char *argv[], int argc, string target){
	int j;
	for(int i=0; i<argc; i++){
		if(argv[i]== target){
			j=i+1;
			return argv[j];
		}
	}
}

/*********************************************************************
** Function: searchInt
** Description: searches for the target flag and grabs the next string
				turns it into an int and returns that int.
** Parameters: argv, argc, target
** Pre-Conditions: assume smart user who knows what to enter into the 
					command line
** Post-Conditions: outputs the int value next to the flag
*********************************************************************/
int searchInt(char *argv[], int argc, string target){
	string i=searchString(argv, argc, target);
	int j=atoi(i.c_str());
	return j;
}

/*********************************************************************
** Function: grab_options
** Description: gets all the user input options from the command line
** Parameters: steps, start, array, argv, argc
** Pre-Conditions: assume smart user who put in the correct flags and values
** Post-Conditions: funnels all the values for the setup of the simulation
					to the starting ant struct
*********************************************************************/
void grab_options(int &steps, ant &start, char **array, char *argv[], int argc){
	if(processInputs(argc, argv)==1){
		start.direction=searchString(argv, argc, "-d");
		start.row=searchInt(argv, argc, "-x");
		steps=searchInt(argv, argc, "-n");
		start.column=searchInt(argv, argc, "-y");
		if(array[start.row][start.column]=='0' || ' '){
			start.color=0;
		}
		else
			start.color=1;
		cout<<"The color of the starting part is "<<start.color<<endl;
		cout<<"The beginning position for the ant is ("<<start.row<<","<<start.column<<"), the number of steps the ant will take is "<<steps<<endl;
		cout<<"The starting direction is "<<start.direction<<endl;
	}
}

/*********************************************************************
** Function: assign_vars
** Description: grabs all the user inputted options and assigns them
				to the start
** Parameters: steps, start, array, begin
** Pre-Conditions: the options must have already been filled out
** Post-Conditions: ant should be ready to go
*********************************************************************/
/*void assign_vars(int &steps, ant &start, char** array, options begin){
	cout<<"You have made it inside the function"<<endl;
	start.direction=begin.direction;
	start.row=(int)begin.X;
	start.column=(int)begin.Y;
	steps=begin.iterations;
	if(array[start.row][start.column]=='0'){
		start.color=0;
	}
	else
		start.color=1;
	cout<<"The color of the starting part is "<<start.color<<endl;
	cout<<"start.row is "<<start.row<<endl<<"start.column is "<<start.column<<endl;
	cout<<"start.direction is "<<start.direction<<endl<<"The number of steps is "<<steps<<endl;
}*/

/*********************************************************************
** Function: get_RowColumn
** Description: asks the user for the number of rows and columns
** Parameters: rows, columns
** Pre-Conditions: rows and columns must be ints
** Post-Conditions: rows and columns will have the user specified
					numbers
*********************************************************************/ 
/*void get_RowColumn(int& rows, int& columns, char *argv[], int argc){
	ifstream inFile;
	string filename = searchString(argv, argc, "-f");
	inFile.open(filename.c_str());
	inFile>>rows;
	inFile>>columns;
}*/

/*********************************************************************
** Function: fill_array
** Description: fills the board for the ant with 0's
** Parameters: array, int rows, int columns 
** Pre-Conditions: void
** Post-Conditions: fill array
*********************************************************************/ 
/*void fill_array(char** array, int &rows, int &columns){
	ifstream inFile;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			inFile.get(array[i][j]);
		}
	}
}*/

/*********************************************************************
** Function: print_array
** Description: prints the board, the current values in the array
** Parameters: array, int rows, int columns 
** Pre-Conditions: the array must exist
** Post-Conditions: print array
*********************************************************************/ 
void print_array(int rows, int columns, char** array){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			cout<<"  "<<array[i][j];
		}
		cout<<endl;
	}
}

/*********************************************************************
** Function: change_array
** Description: changes the 0's to spaces and the 1's to *'s and places
				the ant
** Parameters: rows, columns, array, start
** Pre-Conditions: rows and columns must be defined, the array be filled
					the location of the ant must be specified
** Post-Conditions: board is set up and ready to go for the simulation.
*********************************************************************/ 
void change_array(int rows, int columns, char** array, ant start){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(array[i][j]=='0'){
				array[i][j]=' ';
			}
			else{
				array[i][j]='*';
			}
		}
	}
	array[start.row][start.column]='#';
	print_array(rows, columns, array);
}

/*********************************************************************
** Function: get_ant
** Description: gets all the starting information for the struct ant, 
				this was for getting information to test the program
				without command line arguments ONLY!
** Parameters: start, array
** Pre-Conditions: the user must know how many rows and columns there are
** Post-Conditions: everything in the ant struct is defined.
*********************************************************************/ 
/*void get_ant(ant& start, char** array){
	cout<<"What is the starting direction(up, down, left, right)? ";
	cin>>start.direction;
	cout<<"What is the starting row of the ant? ";
	cin>>start.row;
	cout<<"What is the starting column of the ant? ";
	cin>>start.column;
	if(array[start.row][start.column]=='0'){
		start.color=0;
	}
	else
		start.color=1;
	cout<<"The color of the starting part is "<<start.color<<endl;
}*/ 

/*********************************************************************
** Function: go_up
** Description: prepares the ant to take a step up and change directions
** Parameters: start, array, next
** Pre-Conditions: start must be defined
** Post-Conditions: will store next movement in next
*********************************************************************/ 
void go_up(ant start, ant& next, char** array){
	next.row=start.row-1;
	next.column=start.column;
	if(start.color==1){
		next.direction="right";
	}
	else{
		next.direction="left";
	}	
}

/*********************************************************************
** Function: go_right
** Description: prepares the ant to take a step up and change directions
** Parameters: start, array, next
** Pre-Conditions: start must be defined
** Post-Conditions: will store next movement in next
*********************************************************************/ 
void go_right(ant start, ant& next, char** array){
	next.row=start.row;
	next.column=start.column+1;
	if(start.color==1){
		next.direction="down";
	}
	else{
		next.direction="up";
	}
}

/*********************************************************************
** Function: go_left
** Description: prepares the ant to take a step up and change directions
** Parameters: start, array, next
** Pre-Conditions: start must be defined
** Post-Conditions: will store next movement in next
*********************************************************************/ 
void go_left(ant start, ant& next, char** array){
	next.row=start.row;
	next.column=start.column-1;
	if(start.color==1){
		next.direction="up";
	}
	else{
		next.direction="down";
	}
}

/*********************************************************************
** Function: go_down
** Description: prepares the ant to take a step up and change directions
** Parameters: start, array, next
** Pre-Conditions: start must be defined
** Post-Conditions: will store next movement in next
*********************************************************************/ 
void go_down(ant start, ant& next, char** array){
	next.row=start.row+1;
	next.column=start.column;
	if(start.color==1){
		next.direction="left";
	}
	else{
		next.direction="right";
	}
}

/*********************************************************************
** Function: take_step
** Description: figures out where the ant's next step will be and what	
				direction he will turn
** Parameters: start, next, array
** Pre-Conditions: there must be a starting point for the ant
** Post-Conditions: next will be filled out with the ants next position
*********************************************************************/ 
void take_step(ant start, ant& next, char** array){
	if(start.direction=="up"){
		go_up(start, next, array);
	}
	else if(start.direction=="right"){
		go_right(start, next, array);
	}
	else if(start.direction=="down"){
		go_down(start, next, array);
	}
	else{
		go_left(start, next, array);
	}
	if(array[next.row][next.column]==' '){
		next.color=0;
	}
	else{
		next.color=1;
	}
}

/*********************************************************************
** Function: do_step
** Description: takes the actual step predetermined by take_step
** Parameters: start, next, array, rows, columns
** Pre-Conditions: take_step must have happened already
** Post-Conditions: will reset start and take the actual step
*********************************************************************/ 
void do_step(ant& start, ant next, char** array, int rows, int columns){
	cout<<"The color of my square is "<<next.color<<endl;
	cout<<"My current position is ("<<start.row<<","<<start.column<<")"<<endl;
	cout<<"My next position is ("<<next.row<<","<<next.column<<")"<<endl;
	cout<<"I am currently facing "<<start.direction<<" but I will turn to face "<<next.direction<<endl;
	if(start.color==1){
		array[start.row][start.column]=' ';
	}
	else{
		array[start.row][start.column]='*';
	}
	array[next.row][next.column]='#';
	start=next;
	print_array(rows, columns, array);
}

int main(int argc, char *argv[]){
	int rows, columns, steps;
	ant start, next;
	ifstream inFile;
	string filename = searchString(argv, argc, "-f");
	inFile.open(filename.c_str());
	inFile>>rows;
	inFile>>columns;
	char** array;
	array = new char * [rows];
		for(int i=0; i < rows; i++){
			array[i] = new char[columns];
		}
	grab_options(steps, start, array, argv, argc);
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			inFile.get(array[i][j]);
		}
	}
	cout<<"The number of rows is: "<<rows<<endl<<"The number of columns is: "<<columns<<endl;
	change_array(rows, columns, array, start);
	for(int i=0; i<steps; i++){
		take_step(start, next, array);
		do_step(start, next, array, rows, columns);
	}
	inFile.close();
	return 0;
}
