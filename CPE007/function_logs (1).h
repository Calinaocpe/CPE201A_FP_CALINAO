#ifndef FUNCT_LOGS_H	// Include guard start
#define FUNCT_LOGS_H
#include <string>	// Include string library for std::string

struct userDailyInput {
    std::string date;    // Date of activity
    float restingHeartrate;		// User's resting heart rate
    std::string typePhysicalActivity;	// Type of physical activity	
    std::string intensity;    // Intensity level
    float maximalHeartrate;    // Max heart rate during activity
    float duration;		// Duration of activity in minutes
    int totalSteps;		// Total steps taken
};

struct foodtrack {
    std::string date; 
    std::string breakfast;
    std::string lunch;
    std::string dinner;
    std::string snacks;
};

bool continueConfirm();		// Confirms user choice to continue or exit 
std::string LoginCheck();	// Verifies login credentials
void dailyLogsMenu();	// Displays daily log menu options
void editProfile(std::string);		// Allows user to edit profile info
void registerUser();	// Registers a new user
void BMIdisplayHeader();	// Displays BMI calculator header
void computeBMI();		// Computes user's BMI
void deleteLogs(const std::string &username);	// Deletes exercise and food logs
bool deleteUserAccount(const std::string &username);	// Deletes entire user account

float getFloat(const std::string &prompt, float min, float max);
int getInt(const std::string &prompt, int min, int max);
std::string getString(const std::string &prompt);
std::string getDate(const std::string &prompt);

void logMenu(const std::string &username, userDailyInput &inputs, foodtrack &foodInputs);    // Records exercise logs
void logActivity(const std::string &username, userDailyInput &inputs);    	// Records food logs
void logFood(const std::string &username, foodtrack &foodInputs);
void line();

#endif		// Include guard end
