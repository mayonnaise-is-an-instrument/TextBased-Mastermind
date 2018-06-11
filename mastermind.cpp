#include <iostream> //input output streams
#include <cstdlib>
#include <ctime>
#include <fstream> // to write to a file
using namespace std;
//global variable to display the answer if true
bool debug = false;

//function prototypes
void pegColor(int &peg1, int &peg2, int &peg3, int &peg4, int seed);
void userGuess(int &guess1, int &guess2, int &guess3, int &guess4);
int returnCorrectPeg(int peg1, int peg2, int peg3, int peg4, int guess1, int guess2, int guess3, int guess4);
int returnCorrectPegColor(int peg1, int peg2, int peg3, int peg4, int guess1, int guess2, int guess3, int guess4);
void printBoard(int guess1, int guess2, int guess3, int guess4, int blacks, int whites, ofstream& fout);


int main() {
    
    //welcome
    cout << "Welcome to Mastermind." << endl;
    
    // variable declarations
    int guesstaken = 1;
    int peg1,peg2,peg3,peg4;
    int guess1,guess2,guess3,guess4;
    bool win = false;
    int seed;
    int i = 1;
    int blacks;
    int whites;
    
    //opening the file to write to
    ofstream fout;
    fout.open("mastermind.txt");
    
    //seed entry
    cout << "Please enter a seed: ";
    cin >> seed;
    
    // while loop to repeat 10 times
    while(win==false && i<=10) {
        cout << "Guesses taken: " << guesstaken-1<<endl;
        
        blacks = 0;
        whites = 0;
        
        //calling functions
        pegColor(peg1,peg2,peg3,peg4, seed);
        userGuess(guess1,guess2,guess3,guess4);
        
        //outputting amount of pegs
        cout << "You have " << returnCorrectPeg(peg1,peg2,peg3,peg4,guess1,guess2,guess3,guess4) << "Black Peg(s) and " << returnCorrectPegColor(peg1,peg2,peg3,peg4,guess1,guess2,guess3,guess4) << " White Peg(s)." << endl;
        guesstaken++;
       
       //defining blacks and whites as their values
       blacks = returnCorrectPeg(peg1,peg2,peg3,peg4,guess1,guess2,guess3,guess4);
       whites = returnCorrectPegColor(peg1,peg2,peg3,peg4,guess1,guess2,guess3,guess4);
       
       //if they win
       if(guess1==peg1 && guess2==peg2 && guess3==peg3 && guess4==peg4) {
           cout << "You Win!";
           win = true;
       }
       
       //calling the function to print board to text file
       printBoard(guess1, guess2, guess3, guess4, blacks, whites, fout);
       
       if(debug==true) {
           cout << peg1 << peg2 << peg3 << peg4 << endl;
       }
       //counter
       i++;
    }
    
    //if player loses
    if(guess1!=peg1 && guess2!=peg2 && guess3!=peg3 && guess4!=peg4) {
        
        cout  << "Game Over. You lost." << endl;
        
    }
    
return 0;

}

//generates the pattern the user needs to guess
void pegColor(int &peg1, int &peg2, int &peg3, int &peg4, int seed) {
    
    srand(seed);
    
    peg1 = rand() % 4+1;
    peg2 = rand() % 4+1;
    peg3 = rand() % 4+1;
    peg4 = rand() % 4+1;
    
}

//prompts user to guess
void userGuess(int &guess1, int &guess2, int &guess3, int &guess4) {
    
    bool validentry = false;
    
    do {
        cout << "Input your Guess: " << endl;
        cin >> guess1;
        cin >> guess2;
        cin >> guess3;
        cin >> guess4;
        
        //if entry is invalid
        if(!cin || guess1>4 || guess1<1 || guess2>4 || guess2<1 || guess3>4 || guess3<1 || guess4>4 || guess4<1 ) {
            validentry = false;
            cin.clear();
            cin.ignore(1, '\n');
            cerr << "Invalid input. Please try again." << endl;
        }
        //if input is valid
        else {
            validentry = true;
        }
    }while(validentry==false);
    
}
//returns black pegs
int returnCorrectPeg(int peg1, int peg2, int peg3, int peg4, int guess1, int guess2, int guess3, int guess4) {
    int correctposition = 0;
    if(guess1==peg1) {
        correctposition++;
    }
    else if(guess2==peg2) {
        correctposition++;
    }
    else if(guess3==peg3) {
        correctposition++;
    }
    else if(guess4==peg4) {
        correctposition++;
    }
    
    return correctposition;
}

//returns white pegs
int returnCorrectPegColor(int peg1, int peg2, int peg3, int peg4, int guess1, int guess2, int guess3, int guess4) {
    
    int correctcolor = 0;
    
    if((guess1==peg1) || (guess1==peg2) || (guess1==peg3) || (guess1==peg4)) {
        correctcolor++;
    }
    else if((guess2==peg1) || (guess2==peg2) || (guess2==peg3) || (guess2==peg4)) {
        correctcolor++;
    }
    else if((guess3==peg1) || (guess3==peg2) || (guess3==peg3) || (guess3==peg4)) {
        correctcolor++;
    }
    else if((guess4==peg1) || (guess4==peg2) || (guess4==peg3) || (guess4==peg4)) {
        correctcolor++;
    }
    return correctcolor;
}

//prints board onto a text file
void printBoard(int guess1, int guess2, int guess3, int guess4, int blacks, int whites, ofstream& fout) {
    
    fout << "| " << guess1 << " | " << guess2 << " | " << guess3 << " | " << guess4 << " | " << "Black Pegs: " << blacks << " " << "White Pegs: " << whites << endl;
}

