/*
 * Board.hpp
 *
 * Irvin Favors
 */

#include "Board.hpp"

using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//COMMENT the above line BACK IN AFTER YOU WRITE YOUR DOG CLASS
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;
	// Next:
	// Write the boardConfig Method using the instructions inside the BoardConfig
	// method below, and then test it.
//	startx = 2;
//	starty = 0;
//	endx = 2;
//	endy = size-2;
//	boardConfig();
//	level = 'e';
//	//cout << "should have set level to e" << "\n";
//	addFood();
//	//cout << "should have added food" << "\n";
//	printBoard();
//	cout << "***************************************" << endl;
//	boardConfig();
//	level = 'm';
//	addFood();
//	printBoard();
//	cout << "***************************************" << endl;
//	boardConfig();
//	level = 'h';
//	addFood();
//	printBoard();
//	cout << "***************************************" << endl;
//
//	level = 'e';
//	addFood();
//	addTraps();
//	printBoard();
//	cout << "***************************************" << endl;
//	boardConfig();
//	level = 'm';
//	addFood();
//	addTraps();
//	printBoard();
//	cout << "***************************************" << endl;
//	boardConfig();
//	level = 'h';
//	addFood();
//	addTraps();
//	printBoard();
//	cout << "***************************************" << endl;

//
// ****************************************************************************
//  Part 2:
//  Dog.hpp and Dog.cpp
// *****************************************************************************
//	Now you'll have to write the Dog class and header file before you can write'
//	and test the moveDog method.
//  The instructions for this are below the Board.hpp and Board.cpp files in the
//  lab instructions.
//	Once you are done writing the Dog class and header, you'll need to do the '
//	uncomment out (comment in?) the following
//	 * 1) in the .hpp class, you'll have to comment in the Dog myDog line Board.hpp
//	 * (it's around line 47)
//	 * 2) In the 3rd Board Constructor, you'll need to comment in the mydog.name line
//	 *  (it's around line 37 in this file)
//	 * 3) And you'll have add to your printBoard method a line for printing out
//	 *    the dog object's name and the dog object's strength.
//
// And now write moveDog() as described inside the  moveDog method, below.
// Once done, uncomment out the following 4 lines and test with the following code:
//	moveDog('d');
//	moveDog('u');
//	moveDog('r');
//	moveDog('l');
	// your dog should move down, up, right, and then left.  If you hit a food
	// or a trap, you should get a message as described in the moveDog method, below.





	/*********************************************************************/
	//End of Testing.  Now comment out the above testing stuff, and
	// comment in the rest of the init method, below
	/*********************************************************************/


	/**********************************************************************/
	/* PART THREE
	 * COMMENT OUT THE ABOVE TESTING CODE AND COMMENT IN THE BELOW CODE TO RUN
	 * THE GAME.
	 */

	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size+1;
		starty = 0;
		endx = rand() % size+1;
		endy = size-1;

		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}


/***********************************************************************/
/* HERE'S WHERE THE CODE GOES!                                         */
/***********************************************************************/

void Board::printBoard() {
//	 It prints a blank space for any square (for squares that do not have
//	 food, traps, walls, the dog, and aren't the beginning or the ending.
//   (at first, there will be no food or traps, or even walls or dog, but we
//   will be adding food as 'F' character, traps as 'T' character, walls as
//   '|' or '_' characters, and the dog 'D' character to the board, so you want
//   to print a space for everything that isn't a 'T','F','|','_',or'D'.
//	 Otherwise it prints out the character in the square. Note that I printed a
//	 border around the entire board so it was easier to look at, and, equally,
//	 I placed an -> arro (thats a minus and a greater than sign) in the border
//	 for where the beginning of the game was and where the end of the game was.
	mydog.printDog();  // COMMENT THIS IN WHEN YOU Write your Dog class!!
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			char c = board[i][j];
			if (i == startx && j == starty) cout << ">" << board[i][j];
			if (i == mydog.x && j == mydog.y) cout << "D" << " ";
			else if (i == endx && j == endy) cout << board[i][j] << ">" ;
			else if (c == 'T' || c == 'F' || c == '|' || c == '_' || c == 'D'){
				cout << board[i][j] << " ";
			}
			else cout << "  ";
		}
		cout << endl;
	}
}

void Board::boardDummyValues(){
	for (int i = 1; i < size-1; ++i){
		for (int j = 1; j < size-1; ++j){
			board[i][j] = '+';
		}
	}
}

void Board::boardConfig() {
	 /* This method first puts dummy values in every square (I used '+' - I just didn't want
	 * every square to have gibberish, so I chose a character I wasn't using for any other
	 * purpose and initialized every square to have that value).
	 * I then added my random horizontal and vertical walls.
	 *
	 * Here's how I did it the walls:
	 *
	 * I only placed walls in the odd numbered rows and columns (in other words, row one might
	 * have a row, but then row 2 would not, whereas row three could and row 4 could not.
	 * Same with columns (although you can have flexibility.
	 *
	 * I picked an odd row or column that did not already have a wall in it at all.
	 *
	 * I generated a total of 10 walls.

	 * For each wall, I picked randomly for vertical or horizontal (just rand() % 2 to get either
	 * 0 for vertical, 1 for horizontal.
	 *
	 * I set the easy version to have at most 9 squares in a row or column as a wall, the
	 * medium to have at most 13 squares as walls in a row or column, and the hard version to
	 * have at most 16 squares per row or column.(but you can play with this because sometimes
	 * the hard version was seriously hard!!!
	 *
	 * Let's say I randomly decided to place a wall in row 3.  I then randomly chose 9 squares in
	 * row 3 to be a wall (if it was the easy version, 13 if it was the medium, and 16 if it was
	 * the hard)
	 *
	 * So that's the walls.  Then I added the 'D' to the beginning square nad an 'E' to the end square.
	 */
	boardDummyValues();
	int maxR = 0, maxC = 0, maxW=0;
	if (level == 'e'){maxW = 9;} else if (level == 'm'){maxW = 13;} else {maxW = 16;}
	maxR = rand()%maxW + 2;
	maxC = rand()%maxW + 2;
	for (int i = 1; i < size-1; i+=3){
		for (int k = 0; k < maxR; ++k){
			int r = rand()%size-1;
			if (r >= 1) board[r][i] = '|';
		}
		for (int k = 0; k < maxC; ++k){
			int c = rand()%size-1;
			if (c >= 1) board[i][c] = '_';
		}
	}
	board[endx][endy] = 'E';
}


void Board::addFood() {
	// (5 pts)
	/* Instructions for writing addFood:
	/* this method randomly adds food around the board.  For easy, I added the field size
	 * number of foods randomly around the board.  For medium, I added size-2 foods, and for
	 * hard I added size-4 foods.  The amount of strength the dog gets when they eat (aka
	 * move onto) the food is determined in the moveDog method.
	 */
	int count = size;
	if (level == 'm') count = size-2;
	if (level == 'h') count = size-4;
	for (int i = 1; i < count; ++i){
		int r = rand()%size-1;
		int c = rand()%size-1;
		if (r >= 1 && c >= 1 && board[r][c] == '+') board[r][c] = 'F';
	}
}

void Board::addTraps() {
	// (5 pts)
	//Instructions for addTraps
	/* this method randomly adds traps around the board.  For easy I added size - 6 traps,
	 * for medium, I added size - 8 traps, and for hard I added size - 10 traps.  Note: Traps are
	 * only printed on the board when the game is in debug mode.  The amount of strength each trap
	 * saps from the dog is determined in the moveDog method when the dog moves on a Trap.
	 */
	int count = size-6;
	if (level == 'm') count = size-8;
	if (level == 'h') count = size-10;
	for (int i = 0; i < count; ++i){
		int r = rand()%size-1;
		int c = rand()%size-1;
		if (r >= 1 && c >= 1 && board[r][c] == '+') board[r][c] = 'T';
	}
}

int Board::checkValidPath(int x, int y){
	if (x <= 0 || x >= size || y <= 0 || y >= size) return 0;
	return 1;
}

bool Board::moveDog(char c) {
	// (12 pts)
	//Instructions for moveDog
	/* This is a somewhat long method.
		 * First, it determines the new coordinats of the dog, based on teh direction in which the
		 * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
		 *
		 * If the dog is at teh edge of the board, teh dog should not move
		 *
		 * If the dog moves over food, a random number between 2 and 17 is generated, and the
		 * dog's changeStrength method is used to increase the dog's strength by the random amount.
		 *
		 * If the dog moves over the end of the board, the dog's won method is called and false is
		 * returned from this method.
		 *
		 * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
		 * changeStrength method is called with that negative number.  (Note that the changeStrength
		 * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
		 * thus the dog has died and the game is over. That boolean value is returned from this method).
		 *
		 * If the dog moves over a wall, the method checks to see if the dog has enough strength to
		 * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
		 * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
		 * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
		 * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
		 *
		 * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
		 * method (which, again, will return false if the dog has lost all their strength and died.
		 *
		 * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
		 * random numbers for food, if you are worried about whether you still lose 2 strength points for
		 * moving even though you gained points for moving over food - I'm leaving all that to your preference.
		 * I am concerned that you are using classes, objects, and object methods and accessing object
		 * fields correctly!
		 *
		 */
	board[startx][starty] = ' ';
	if (tolower(c) == 'u'){
		int tmp = checkValidPath(mydog.x-1, mydog.y);
		mydog.x -= 1;
		if (tmp == 0) return false;
		//cout << "x: " << mydog.x << "y: " << mydog.y << endl;
		if (board[mydog.x][mydog.y] == '+'){return mydog.changeStrength(-2);}
	}
	else if (tolower(c) == 'd'){
		int tmp = checkValidPath(mydog.x+1, mydog.y);
		mydog.x += 1;
		if (tmp == 0) return false;
		//cout << "x: " << mydog.x << "y: " << mydog.y << endl;
		if (board[mydog.x][mydog.y] == '+'){return mydog.changeStrength(-2);}
	}
	else if (tolower(c) == 'l'){
		int tmp = checkValidPath(mydog.x, mydog.y-1);
		mydog.y -= 1;
		if (tmp == 0) return false;
		//cout << "x: " << mydog.x << "y: " << mydog.y << endl;
		if (board[mydog.x][mydog.y] == '+'){return mydog.changeStrength(-2);}
	}
	else if (c == 'r'){
		int tmp = checkValidPath(mydog.x, mydog.y+1);
		mydog.y += 1;
		if (tmp == 0) return false;
		//cout << "x: " << mydog.x << "y: " << mydog.y << endl;
		if (board[mydog.x][mydog.y] == '+'){return mydog.changeStrength(-2);}
	}
	if (mydog.x == endx && mydog.y == endy){
		mydog.won();
		//cout << "x: " << mydog.x << "y: " << mydog.y << endl;
		return false;
	}
	if (board[mydog.x][mydog.y] == 'T'){
		cout << mydog.name << " hit a trap." << endl;
		board[mydog.x][mydog.y] = ' ';
		int x = rand()%17 + 2;
		return mydog.changeStrength(-x);
	}

	if (board[mydog.x][mydog.y] == 'F'){
		board[mydog.x][mydog.y] = ' ';
		int x = rand()%17 + 2;
		return mydog.changeStrength(x);
	}
	if (board[mydog.x][mydog.y] == '|' || board[mydog.x][mydog.y] == '_'){
		if (mydog.strength >= 6){
			cout << mydog.name << " hit a wall." << "\n";
			cout << "Do you want to know down the wall?" << "\n";
			string s = "no";
			cin >> s;
			if (s == "yes" || s == "Yes" || s == "y" || s == "Y"){
				mydog.changeStrength(-6);
				board[mydog.x][mydog.y] = ' ';
				return true;
			}
			else {
				return mydog.changeStrength(-1);

			}
		}
		else {
			mydog.changeStrength(-6);
		}
	}
	return mydog.strength != 0;
}


void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}

}


