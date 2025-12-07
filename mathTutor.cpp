/*
* Title:       Math Tutor V6
*Programer(s): Khumo Nakedi & Kezey Boye
*Date:         10/29/2025
*Github URL:   https://github.com/nakediKhum03/MathTutorV6.git
*Description:  A simple math tutor designed to help students practice and improve their basic  math arithmetic skills.
*              This program randomly generates integer-based math problems—addition, subtraction, multiplication,
*              and division for the user to solve. The user's name is collected using getline, and they are then
*              presented with one randomized problem at a time.
*
*              After each question, the user has up to three attempts to input the correct answer. If the answer
*              is still incorrect after three attempts, the correct solution is will be displayed.
*              The program is then asked if the user would like to continue solving more problems.
*
*              Based on how good the user is, they will affect the difficulty progression:
*              answering three questions correctly in a row levels the user up, increasing the maximum random number
*              range by +10 to make problems even more challenging.
*              Inversely, answering three incorrectly in total will level the user down (unless already at the
*              lowest level), reducing the difficulty range by -10.
*
*              Each session is summarized at the end in a formatted summary report showing all problems attempted, the
*              user’s responses, the number of attempts, and whether the answers were correct or incorrect. The
*              report also displays the user’s total correct, total incorrect, and average score percentage.
*
*              This version serves as the foundation for a more advanced math tutor that will later feature progress
*              tracking, adaptive difficulty, and personalized feedback to help students strengthen their math skills
*              and confidence.
*/


#include <cstdlib>
#include<iomanip>
#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

#include "mathtutor6.h"


constexpr int MAX_ATTEMPTS = 3;
constexpr int LEVEL_CHANGE = 10; //How much to increase the range when leveling up and down
const string FILE_NAME = "mathtutor.txt";

/****************************************************
 * Displays Program header
 ***************************************************/

void DisplayGameIntro() {
    cout << "******************************************************************************************************" <<
            endl; // Simply a header stating what this program is.
    cout << "*                               Welcome to the Simply Silly Math Tutor                               *" <<
            endl;
    cout << "******************************************************************************************************" <<
            endl;
    cout << endl;

    cout << "Fun math facts:" << endl;

    cout << "    * 1000 is the only number with an {A} in it form one to one thousand" << endl;
    // listing a few math facts for the user's entertainment
    cout << "    * There is no Roman numeral for zero" << endl;
    cout << "    * The largest prime digit has over 24 million digits" << endl;
    cout << "    * In a room of 23 people, there is a greater than 50% chance that two will share the same birthday" <<
            endl;
    cout << endl; // formatting whitespace
    cout << "******************************************************************************************************" <<
            endl;
    cout << endl; // formatting whitespace
}

/*******************************************************************
 *Get user's name, welcome user, and return username
 *******************************************************************/

string GetUserName() {
    string userName = "?";

    cout << "What is your name?" << endl; // where the user puts there name
    getline(cin, userName); // gets the user's full names with get line
    cout << "Welcome, " << userName << ", to the Simply Silly Math Tutor!" << endl; // prints and welcomes the user

    return userName;
}


/************************************************************
 *Generate each random question
 *Parameters: mathLevel used to set the left & right ranges
 *Returns the currents question's data as an int vector
 ************************************************************/
int GetNumericValue() {
    int userAnswer; // stores users answer

    //
    while (!(cin >> userAnswer)) {

        cin.clear();
        // clears error flag in cin can be used again

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // removes all remaining characters in the input buffer
        // gets rid of invalid text eg. abc or symbols

        cout << "\tInvalid input!\n\tPlease enter a number:" << endl; // user should try again
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // after a valid number is entered
    // removes any leftover characters


    return userAnswer; // back to main
}

/*******************************************************
 Generate random question  based on mathLevel
 Returns: vector <int> {level, leftNum, mathOperator,
          rightNum, totalNum}
 *****************************************************/
vector<int> GenerateRandomQuestion(int mathLevel) {
    enum MATH_TYPE { MT_ADD = 1, MT_SUB = 2, MT_MUL = 3, MT_DIV = 4 };
    MATH_TYPE mathType = MT_ADD;

    int tempNum = 0;
    int leftNum = 0;
    int rightNum = 0;
    char mathOperator = '?';
    int totalNum = 0;


    srand(time(0)); // Randomizing numbers

    //random numbers based on current level change,
    //LEVEL_CHANGE increases difficulty
    leftNum = rand() % (mathLevel * LEVEL_CHANGE) + 1;
    rightNum = rand() % (mathLevel * LEVEL_CHANGE) + 1;

    // Randomly chooses one of the four math operating numbers
    mathType = static_cast<MATH_TYPE>(rand() % 4 + 1);

    switch (mathType) {
        // logic behind generating problems based of the math type
        case MT_ADD:
            mathOperator = '+';
            totalNum = leftNum + rightNum; // answer for addition
            break;
        case MT_SUB:
            mathOperator = '-';
            if (rightNum > leftNum) {
                // making sure that we won't get a negative number when subtracting
                tempNum = leftNum;
                leftNum = rightNum;
                rightNum = tempNum;
            }
            totalNum = leftNum - rightNum; // answer for subtraction
            break;
        case MT_MUL:
            mathOperator = '*';
            totalNum = leftNum * rightNum; //answer for multiplication
            break;
        case MT_DIV:
            mathOperator = '/';
            totalNum = leftNum; // makes sure there is no fractions and correct answer
            leftNum = leftNum * rightNum; // makes sure there is no fractions
            break;
        default: // if math type is invalid and it ends the program
            cout << "Invalid Question type: " << mathOperator << endl;
            cout << "Please contact Khumo for further assistance" << endl;
            throw runtime_error("Invalid Math Type:" + mathType); // caught in main
    }


    return {mathLevel, leftNum, mathOperator, rightNum, totalNum}; // return these values back to main
}

/*************************************************
 Give 3 attempts to use to give them a display of
 what level they are currently on
 *************************************************/

bool GiveThreeAttempts(string userName, vector<int>& currentQuestion) {
    // boolean because it returns if the user got the question right/wrong
    int userAnswer = 0;
    bool isCorrect = false; // tracks whether the user answered correctly
    int attemptsUsed = 0;

    // extracts all data from the currentquestions.at() variables
    int mathLevel = currentQuestion.at(0);
    int leftNum = currentQuestion.at(1);
    char mathOperator = static_cast<char>(currentQuestion.at(2)); // convert stored int to a char
    int rightNum = currentQuestion.at(3);
    int totalNum = currentQuestion.at(4);

    //loops through MAX_ATTEMPTS
    for (int i = 1; i <= MAX_ATTEMPTS; ++i) { // int = 1; because user already starts at one attempts
        cout << "[Level #" << mathLevel << "] " << userName << ", what is " << leftNum << " " << mathOperator << " " <<
                rightNum << " = " << "?" << endl; // displays the question
        // ... your input handling stays the same ...

        userAnswer = GetNumericValue(); // calls the getnumericvalue funtions


        if (userAnswer == totalNum) { // if user's answer is correct
            cout << "Excellent Job Einstein!" << endl;
            isCorrect = true;
            attemptsUsed = i; // records which attempt they succeeded on
            currentQuestion.push_back(attemptsUsed);
            break; // stop asking this question
        }

        // if user has reached max attempts of 3
        if (i == MAX_ATTEMPTS) {
            cout << "Sorry, you're out of attempts. Correct answer: " << totalNum << endl;
            attemptsUsed = 0; //0 means incorrect after all attempts
            currentQuestion.push_back(attemptsUsed);
        } else {
            // otherwise the user know how many attempst left
            cout << (MAX_ATTEMPTS - i) << " attempt/s left." << endl;
            cout << "Try Again" << endl;
        }
    }
    return isCorrect; // return back to main
}


/**************************************************
 *Asks the user if they would want to continue
 *playing the game
 *Param: The yes or no option from the user
 *Returns the user's input as a string
 *************************************************/

string YesNoQuestion(string question) {
    string userInput; // declares new variable

    while (true) { //loops while as long as yes/no answers come through
        cout << question << endl;
        getline(cin, userInput); // get full line & user's answer

        for (char &i: userInput) {
            // converts ALL characters from input as lower case
            i = static_cast<char>(tolower(i));
        }
        // if any of these answers are given in
        if (userInput == "y" || userInput == "yes" ||
            userInput == "n" || userInput == "no") {
            break; // break the loop
        } else {
            // otherwise display this
            cout << "Invalid input, please try again..." << endl;
            cout << endl;
        }
    } // end of while true loop


    return userInput; // returns to main
}

/******************************************************
 Check for level change (up or down)
 ******************************************************/
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLevel) { //declares all functions to be used
    int LEVEL_RANGE_CHANGE = 10; // create level change and make it harder

    if (totalCorrect == 3) { // if they have gotten 3 answers correct they can level up with range = mathLevel x level range change
        mathLevel++; // increments positively
        totalCorrect = 0; // declaring sum total of right answers
        totalIncorrect = 0; // declaring sum totals of wrong answers
        cout << "You are currently on level " << mathLevel << endl;
        cout << "Your range is now from 1 to " << mathLevel * LEVEL_RANGE_CHANGE << endl;
        cout << endl;
    } else if (totalIncorrect == 3) { // if they get 3 total incorrect they will go down a level range change
        mathLevel--; // increments negatively
        totalIncorrect = 0;
        totalCorrect = 0;
        cout << "You are currently on level " << mathLevel << endl;
        cout << "Your range is now from 1 to " << mathLevel * LEVEL_RANGE_CHANGE << endl;
        cout << endl;
    }
    return;
}

/***********************************************************
 Displays summary report to the user to give them their
 level advancement, math questions answered with the math
 symbols being displayed, attempts used for each level and
 question. It also displays the total of correct and incorrect
 answered questions with an average percentage score given at
 the end.
 ***********************************************************/
void DisplaySummaryReport(const vector<vector<int> > &allQuestions) { // allQuestions will be stored as a vector constantly as an int.
    int totalIncorrect = 0;
    int totalCorrect = 0;
    int mathLevel = 1;
    int leftNum = 0;
    int rightNum = 0;
    int totalNum = 0;
    int attemptsUsed = 0; // declares functions that will hold values that might change
    char mathOperator = '?'; // char is declared but needs a placeholder

    cout << "===================================" << endl;
    cout << "          Summary Report           " << endl;
    cout << "===================================" << endl;

    cout << left << setw(7) << "Level" // set precesion to the left with 7 spaces
            << left << setw(22) << "Question"
            << left << setw(10) << "Attempts"
            << "Results" << endl;
    cout << "____ ______________________ __________ _______" << endl;
    cout << endl;
    // Displays summary report for all previously saved questions

    // loops through all questions and isplays the ONE BY ONE
    for (int i = 0; i < allQuestions.size(); ++i) { //
        mathLevel = allQuestions.at(i).at(0);
        leftNum = allQuestions.at(i).at(1);
        mathOperator = static_cast<char>(allQuestions.at(i).at(2)); // converts it into a char
        rightNum = allQuestions.at(i).at(3);
        totalNum = allQuestions.at(i).at(4);
        attemptsUsed = allQuestions.at(i).at(5);

        // prints into formatted lines using set precision
        cout << left << setw(7) << mathLevel
                << left << setw(4) << leftNum
                << " " << mathOperator << " "
                << setw(4) << rightNum
                << " = "
                << setw(6) << totalNum
                << "  ";

        cout << left << setw(10) << attemptsUsed;

        if (attemptsUsed > 0) { // if attemots used is more than zero dispplay correct
            cout << "Correct!" << endl;
            totalCorrect++;
        } else {
            cout << "Incorrect!" << endl; // otherwise display incorrect
            totalIncorrect++;
        }
    }

    // Cal percentage score
    int totalQs = totalCorrect + totalIncorrect; // declares with using previous data
    int percent = 0; // declare new varaiable
    if (totalQs > 0) {
        percent = totalCorrect * 100 / totalQs;
    }

    cout << endl;
    cout << "Total Correct:   " << totalCorrect << endl;
    cout << "Total Incorrect: " << totalIncorrect << endl;
    cout << "Average:         " << percent << "%" << endl;

    cout << endl;
    cout << "That's all folks!" << endl;
    cout << "End of program" << endl; // end of program
    cout << endl;
}

/****************************************************************************
Save Current game logic; uses data to be stored INTO the file
 ****************************************************************************/

void SaveCurrentGame(string userName, vector<vector<int> > &allQuestions) {
    //saves current game with names, constant integer 2D vector with all questions

    string userInput;
    ofstream outFS; // the file for the data to be saved TO

    userInput = YesNoQuestion("Do you want to save the game? (y/n)");
    // calling YesNoQuestions function

    if (userInput == "n" || userInput == "no") { // if they user's input will be no the display
        cout << "Save game cancelled" << endl;

        return; // return to main
    }

    cout << "Saving game...please wait" << endl; //displays to user

    outFS.open(FILE_NAME); // open file to save the user's answers

    if (!outFS.is_open()) { // if unable to open
        throw runtime_error("Could not open file " + FILE_NAME + " for writing.");
    }

    for (int i = 0; i < allQuestions.size(); ++i) { // 2D vector for loop
        outFS << allQuestions.at(i).at(0) << " "
                << allQuestions.at(i).at(1) << " "
                << allQuestions.at(i).at(2) << " "
                << allQuestions.at(i).at(3) << " "
                << allQuestions.at(i).at(4) << " "
                << allQuestions.at(i).at(5) << endl; // 5 attempts to store data
    }
    outFS.close(); // closes file

    cout << allQuestions.size() << " questions saved succesfully." << endl; //size of questions saved

    return;
}
/**************************************************************************
 Load Previous Game logic to help with opening up the already stored files
 *************************************************************************/


int LoadPreviousGame(string username, vector<vector<int> > &allQuestions) {
    string userInput;
    ifstream inFS; //Declaring to fetch the saved data
    int mathLevel = 1;
    int leftNum = 0;
    int mathOperator = 0;
    int rightNum = 0;
    int totalNum = 0; // Declared variables

    int attemptsUsed = 0;

    inFS.open(FILE_NAME); //opening file to a global variable FILE_NAME

    if (!inFS.is_open()) { // if file not found
        cout << "Looks like you've never played this game before" << endl;
        cout << "Good luck!" << endl; // display to user

        return mathLevel; // return  value for mathLevel in main cpp
    } // end if

    userInput = YesNoQuestion("Do you want to load the game?"); // load previous game by calling YesNoQuestion function

    if (userInput == "n" || userInput == "no") { // if user says no the cout Not loading file...
        cout << "Not loading file...";

        return mathLevel; // return back to main
    }
    cout << "Loading file please wait..." << endl; // Displayed to user

    while (inFS >> mathLevel >> leftNum >> mathOperator >> rightNum >> totalNum >> attemptsUsed) {
        allQuestions.push_back({mathLevel, leftNum, mathOperator, rightNum, totalNum, attemptsUsed});
    } //while loop for to read these in a 2D Vector

    if (!inFS.eof()) { // if we did not read to the end of the file
        throw runtime_error("Something went wrong with reading the" + FILE_NAME + " file."); // caught in main.cpp
    }
    inFS.close(); // closes input file

    cout << "There were " << allQuestions.size() << " questions saved" << endl;
    // / allQuestion.size() has the number of how many questions were saved previously

    return mathLevel; // back to main
}
