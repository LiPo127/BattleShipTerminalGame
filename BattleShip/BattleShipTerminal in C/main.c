#include <stdio.h>


const int gridX = 13;
const int gridY = 28;

int ReadBoardFile(int board [gridX][gridY]);
void PrintBoard (int arr [gridX][gridY]); 

///////////////////////////////////////////// MAIN //////////////////////////////////

int main (void) {
    //variables
    int board [gridX][gridY];
    int err;

    //logic
    err = ReadBoardFile(board);
    if(err) {
	printf("[ERROR opening file]");
	return 1;
    }
    PrintBoard(board);
    return 0;
}

///////////////////////////////////////////// function //////////////////////////////////

int ReadBoardFile(int board [gridX][gridY]) {
    int i = 0;
    int temp;
    int garb;
    FILE *f_ptr;
    f_ptr = fopen("board.txt", "r");

    // exit the function if file can't be opened
    if (f_ptr == NULL) {
	return 1; 
    }

    //going through the file char by char
    while (i <= gridY) {  
	for (int j = 0; j < gridX; j++) {
	    temp = fgetc(f_ptr);
	    //makes sure [linefeed] isn't into the array
	    if (temp == 10) {
		//gets next char after line feed
		temp = fgetc(f_ptr);
	    }
	    board[j][i] = temp;
	}
	i++;
    }	
    fclose(f_ptr);
    return 0;
}

void PrintBoard (int arr [gridX][gridY]) { // prints a 2d array to the console
    for (int i = 0; i < gridY; i++) {
	for (int j = 0; j < gridX; j++ ) {
	    printf("%c", arr[j][i]);
	}
	printf("\n");
    }
}


/*
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <windows.h> //only used for sleep function

const int gridY=28;
const int gridX=13;


static void ClearTerminal();

void CopyBoard(char board [gridY][gridX],char boardCopy[gridY][gridX]);
void GetBoard(char arr [gridY][gridX]);
void GenerateShips (char board [gridY][gridX], bool player, int shipLength);
void PrintBoard (char arr [gridY][gridX]);
void MakeUserBoard (char arr [gridY][gridX]);
void MasterBoardUpdate (char arr [gridY][gridX], int x, int y);
void ViewUpdate (char arr [gridY][gridX], int x, int y, bool isHit, bool player);
int HitDetect (char arr1 [gridY][gridX], char arr2 [gridY][gridX], int x, int y, int score, bool player);

void GetUserInput(int input[2]);

void AiFire(int input [2], bool arr [gridY][gridX]);
void BoolArrayInit(bool arr [gridY][gridX]);

void PlayAnimation(bool player, int input[2],char board [gridY][gridX], char animBoard [gridY][gridX]);

int main() {

    //variables >>
    bool boardHits [gridY][gridX];
    char masterBoard [gridY][gridX];
    char animBoard [gridY][gridX];
    char userBoard [gridY][gridX];
    int userInput [2];
    int aiInput [2];
    int aiScore = 0;
    int userScore = 0;
    int turn = 0;
    bool gameRunning = true;
    //need a vector for ai logic
    //variables <<

    //game init >>
    GetBoard(masterBoard);
    GenerateShips (masterBoard, true, 0);
    std::cout << "Player ships generated" << std::endl;
    GenerateShips (masterBoard, false, 0);
    std::cout << "Ai ships generated" << std::endl;
    CopyBoard(masterBoard, userBoard);
    MakeUserBoard(userBoard);
    BoolArrayInit(boardHits);
    //game init <<
    //game logic >>
    while(gameRunning) {
	ClearTerminal();
	std::cout << "First to 17 wins!" << std::endl;
	std::cout << "AI score: " << aiScore << std::endl;
	PrintBoard(userBoard); //change back to user board
    std::fstream mapFile; //needed for reading the file
    std::string line; // needed for reading the file
    std::string temp; // stores a row in a string
    int i = 0; // used to iterate through each row of the array
    mapFile.open("map.txt", std::ios::in); //opens file in read mode
    if (mapFile.is_open()) {
	while (getline(mapFile, line)) {
	    std::stringstream num(line);
	    getline(num, temp, '\n');
	    for (int j = 0; j < gridX; j++) {
		arr [i][j] = temp [j];
	    }
	    i++;
	}
	mapFile.close(); //closes file
    }
	std::cout << "Player score: " << userScore << std::endl; 
	std::cout << "Turn: " << turn << std::endl;

	GetUserInput(userInput);
	PlayAnimation(true, userInput, userBoard, animBoard);
	userScore = HitDetect (masterBoard, userBoard, userInput[1], userInput[0], userScore, true);

	AiFire(aiInput, boardHits);
	PlayAnimation(false, aiInput, userBoard, animBoard);
	aiScore = HitDetect (masterBoard, userBoard, aiInput[1], aiInput[0], aiScore, false);

	//win conditions >>
	if (userScore == 17) {
	    ClearTerminal();
	    PrintBoard(masterBoard);
	    std::cout << "Player Wins!!" << std::endl;
	    gameRunning = false;
	}

	if (aiScore == 17) {
	    ClearTerminal();
	    PrintBoard(masterBoard);
	    std::cout << "AI Wins!!" << std::endl;
	    gameRunning = false;
	}
	//win conditions <<
    turn++;
    }
    //game logic <<
}

static void ClearTerminal() {
    std::system("cls"); //cls for windows, clear for linux
}

void GetUserInput(int input[2]) {
    int i = 0;
    char tempX;
    char tempY;
    char tempSwap;
    bool swap = false;
    char lowercase[10] = {97,98,99,100,101,102,103,104,105,106};
    char numbers[10] = {48,49,50,51,52,53,54,55,56,57};
    std::cin >> tempX;
    std::cin >> tempY;

    while(i < 10){
	if(tempY == numbers[i]){
	    swap = true;
	}
	i++;
    }
    if (swap){
	tempSwap = tempX;
	tempX = tempY;
	tempY = tempSwap;

    }
    i = 0;

    while(i < 10){
	if(tempY == lowercase[i]){
	    tempY = tempY - 32;
	}
	i++;
    }
    i = 0;

    input [0] = tempY - 62;
    input [1] = tempX - 45;
}



void PrintBoard (char arr [gridY][gridX]) { // prints a 2d array to the console
    for (int i = 0; i < gridY; i++) {
	for (int j = 0; j < gridX; j++ ) {
	    std::cout << arr[i][j];
	}
	std::cout << std::endl;
    }
}

void MakeUserBoard (char arr [gridY][gridX]) { // initializes a 2d array with all ~
    std::string tilda = "~";
    std::string pound = "#";
    for (int i = 0; i < 14; i++) {
	for (int j = 0; j < gridX; j++ ) {
	    if (arr[i][j] == pound[0]){
		arr[i][j] = tilda[0];
	    }
	}
    }
}	

int HitDetect (char arr1 [gridY][gridX], char arr2 [gridY][gridX], int x, int y, int score, bool player) {
    if (arr1 [y][x] == 126) { //126 is the ascii decimal value for ~
	ViewUpdate (arr2, x, y, false, player);
	return score;
    }
    if (arr1 [y][x] == 35) { //35 is the ascii decimal value for #
	ViewUpdate (arr2, x, y, true, player);
	MasterBoardUpdate (arr1, x, y); // updates the map to keep track of hits
	score ++;
	return score;
    }
    return score;
}

void MasterBoardUpdate (char arr [gridY][gridX], int x, int y) { // changes the # to a ~
    std::string tilda = "~";
    arr [y][x] = tilda[0];
}

void ViewUpdate (char arr [gridY][gridX], int x, int y, bool isHit, bool player) { // updates the view array so user can see hits and misses
    std::string miss = "o";
    if (player == false) {
	miss = "~";
    }
    std::string hit = "X";
    if (isHit == false){
	arr [y][x] = miss[0];
    }
    if (isHit == true){
	arr [y][x] = hit[0];    
    }
}

void AiFire(int input [2], bool arr [gridY][gridX]){
    std::random_device rd;  // Obtain a random seed from the hardware
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
    std::uniform_int_distribution<> dis(0, 9);  // Uniform distribution between 0 and 9

    int tempX = dis(gen);
    int tempY = dis(gen);
    int randX = tempX + 3;
    int randY = tempY + 17;
    if (arr [randY] [randX] == 1) {
	AiFire(input, arr);
    }
    if (arr [randY] [randX] == 0) {
	arr [randY] [randX] = 1;
	input [1] = randX;
	input [0] = randY;
    }

}

void BoolArrayInit(bool arr [gridY][gridX]) { // sets entire array to zero
    for (int i = 0; i < gridY; i++) {
	for (int j = 0; j < gridX; j++ ) {
	    arr[i][j] = 0;
	}
    }
}	

void PlayAnimation(bool player, int input[2],char board [gridY][gridX], char animBoard [gridY][gridX]) {
    bool play = true;
    int playtime = 125;
    int endtime = 75;
    int i;
    if (player) {
	i = 26;
	while(play) {
	    CopyBoard(board, animBoard);
	    animBoard [i][input[1]] = 65;
	    ClearTerminal();
	    PrintBoard(animBoard);
	    Sleep(playtime);
	    if(i < input[0] + 1){
		animBoard [i][input[1]] = 64;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		animBoard [i][input[1]] = 35;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		animBoard [i][input[1]] = 42;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		play = false;
	    }
	    i--;
	}
    } else {
	i = 0;
	while(play) {
	    CopyBoard(board, animBoard);
	    animBoard [i][input[1]] = 86;
	    ClearTerminal();
	    PrintBoard(animBoard);
	    Sleep(playtime);
	    if(i > input[0] - 1){
		animBoard [i][input[1]] = 64;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		animBoard [i][input[1]] = 35;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		animBoard [i][input[1]] = 42;
		ClearTerminal();
		PrintBoard(animBoard);
		Sleep(endtime);
		play = false;
	    }
	    i++;
	}
    }
}

void CopyBoard(char board [gridY][gridX],char boardCopy[gridY][gridX]){
    for (int i = 0; i < gridY; i++) {
	for (int j = 0; j < gridX; j++ ) {
	    boardCopy[i][j] = board[i][j];
	}
    }
}


void GenerateShips (char board [gridY][gridX], bool player, int index){
    std::random_device rd;  // Obtain a random seed from the hardware
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
    std::uniform_int_distribution<> dis(0, 9);  // Uniform distribution between 0 and 9

    int tempX = dis(gen);
    int tempY = dis(gen);
    int orientation = dis(gen);
    int randX = tempX;
    int randY = tempY;
    int j = 0;
    int yOffset = 0;
    int length [5] = {2,3,3,4,5};

    if (player) {
	randX = randX + 3;
	randY = randY + 17;
	yOffset = 17;
    } else {
	randX = randX + 3;
	randY = randY + 3;
	yOffset = 3;
    }
    
    // Generate Virtical >>
    if (orientation < 5){
	if ((randY - length[index]) < yOffset){ 
	    return GenerateShips(board, player, index);
	}
	j = randY;
	for (int i = 0; i < length [index]; i++){
	    if(board [j][randX] == 35){
		return GenerateShips(board, player, index);
	    }
	    j--;
	}
	for (int i = 0; i < length [index]; i++){
	    board [randY][randX] = 35;
	    randY--;
	}
	// Generate Virtical <<
	
	// Generate Horizontal >>
    } else {
	if ((randX + length[index]) > 12){ 
	    return GenerateShips(board, player, index);
	}
	j = randX;
	for (int i = 0; i < length [index]; i++){
	    if(board [randY][j] == 35){
		return GenerateShips(board, player, index);	
	    }
	    j++;
	}
	for (int i = 0; i < length [index]; i++){
	    board [randY][randX] = 35;
	    randX++;
	}
    }
    //Generate horizontal <<
    if (index < 4){
	GenerateShips(board, player, index + 1);
    }
}
*/
