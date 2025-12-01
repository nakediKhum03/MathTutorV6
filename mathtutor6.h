//
// Created by Moeketsi Reatshepa Khumo Nakedi on 2025/11/21.
//

/**************************************************************************************************
 Program.....: MathTutor V5
 Programmer..:Khumo Nakedi
 Date........:11/16/2025
 replit URL..:https://github.com/nakediKhum03/MathTutorV5.git
 Description.:This file contains all the prototypes for the functions that the m,ain function calls
 **************************************************************************************************/

#ifndef MATHTUTOR_H
#define MATHTUTOR_H

#include <string>
#include <vector>
using namespace std;

void DisplayGameIntro ();
string GetUserName ();
vector <int>GenerateRandomQuestion (int mathLevel);
int GetNumericValue();
bool GiveThreeAttempts (const string& userName, vector <int> currentQuestion);
void CheckForLevelChange (int &totalCorrect, int &totalIncorrect,
                          int &mathLevel);
string YesNoQuestion (string userName);
void DisplaySummaryReport(const vector<vector <int>> &allQuestions);
void SaveCurrentGame (string username, const vector<vector <int>> &allQuestions);


#endif //MATHTUTOR_H

#ifndef MATHTUTORV6_MATHTUTOR6_H
#define MATHTUTORV6_MATHTUTOR6_H

#endif //MATHTUTORV6_MATHTUTOR6_H