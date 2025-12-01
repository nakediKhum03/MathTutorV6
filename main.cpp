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


#include<iostream> // cin and cout
#include <ctime> // time seeding
#include <cstdlib> // srand and rand
#include <vector> // stroring questions in 2D vector
#include <string> // string data types

#include "mathtutor6.h"
using namespace std;


int main () {
     vector<vector<int>> allQuestions;

     string userName = "?";
     string userInput = "?";

     int totalCorrect = 0;
     int totalIncorrect = 0;
     int mathLevel = 1;

     bool isCorrect = false;

     srand(time(0));

     DisplayGameIntro();
     userName = GetUserName();

     do {
          vector<int> currentQuestion = GenerateRandomQuestion(mathLevel);

          isCorrect = GiveThreeAttempts (userName, currentQuestion);

          if (isCorrect) {
               totalCorrect++;
          } else {
               totalIncorrect++;
          }

          CheckForLevelChange (totalCorrect, totalIncorrect, mathLevel);

          allQuestions.push_back(currentQuestion);

          userInput = YesNoQuestion(userName);

     } while (userInput == "yes" || userInput == "y");

     DisplaySummaryReport(allQuestions);

     cout << "Keep calm and do math" << endl;

     return 0;



}




