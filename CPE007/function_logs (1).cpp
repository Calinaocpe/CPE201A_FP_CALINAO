#include <iostream>	// Input/output
#include <iomanip>	// Formatting output
#include <string>	// String handling
#include <fstream>	// File reading/writing
#include <cstdlib>	// System("cls") for clearing screen
#include <limits> // Checks inputs for errors when putting the wrong type
#include <cstdio> // For account/log deletion

#include "function_logs.h"	// Include header file for function declarations

using namespace std;

struct userInformation {	// Stores user information
 	string firstname;
 	string surname;
	string gender;
	string birthdate;
	int age;
    float weight;
    float height;
    float BMI;
};

bool continueConfirm() {	// Returns true if user enters 1, false if 0
	int choice;
	
	while (true) {	// Loop until a valid input is entered
		while (true) {	// Inner loop for numeric input validation	
		    cin >> choice;
		    
			if (cin.fail()) { // Check if input is not an integer
			    cout << "Invalid Input. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear buffer
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear buffer
						break;
		        }
		    }
	
		if (choice < 0 || choice > 1) {	// Input must be 0 or 1
			cout << "Invalid Input. Try again.\n";
		}
		else {
			break; // Valid input
		}
	}
		
	if (choice == 1) {	// Return true if 1, false if 0
			return 1;
	}
	else {
		return 0;
	}
}

void registerUser() {	// Handles new user creation, input validation, and file storage
				
	string username, password, checker;
    userInformation User;
    		
		while (true) {
			system("cls"); // Clears console screen
			
			while (true) { 
		        cout << "NEW USER";
				line();
				cout << "Input your Username: "; 
		        cin >> username;
		        cout << "Input your Password: "; 
		        cin.ignore();	// Clear buffer for getline
				getline (cin, password);
		        ifstream profilecheck(username + ".txt"); // Check if account exists
		        
				if (profilecheck.is_open()) {
		        	cout << "\nUser already exists. Try again." << endl;
		        	cout << "Press <Enter> to return.\n";
					cin.get();
					system("cls");
		        	profilecheck.close();
		        	return;	// Exit function if username already exists
				}	
				else {
					break;	// Username available
				}
		    }

	        cout << "Input your First Name: ";	// Personal Information Input
	        cin.ignore();
	        getline(cin,User.firstname);
	        cout << "Input your Surname: ";
	        getline(cin,User.surname);
	        
			while (true) {	// Gender input and validation	
			    cout << "Input your Gender (Male, Female, Others): ";
			    cin >> User.gender;
			
			    if (User.gender == "Male" || User.gender == "male" || User.gender == "MALE") {
			        break;
			    } 
			    else if (User.gender == "Female" || User.gender == "female" || User.gender == "FEMALE") {
			        break;
			    } 
			    else if (User.gender == "Others" || User.gender == "others" || User.gender == "OTHERS") {
			        break;	// Valid gender input
			    } 
			    else {
			        cout << "Invalid Input. Try again." << endl;
			    }
			}
	        
	        while (true) {	// Birthdate input and validation
			    cout << "Input your Birthdate (MM/DD/YY): ";
			    cin >> User.birthdate;
				// Check format and digits
			    if (User.birthdate.length() == 8 && User.birthdate[2] == '/' && User.birthdate[5] == '/' &&  
					isdigit(User.birthdate[0]) && isdigit(User.birthdate[1]) && isdigit(User.birthdate[3]) && 
					isdigit(User.birthdate[4]) && isdigit(User.birthdate[6]) && isdigit(User.birthdate[7])) {
			
			        int month = stoi(User.birthdate.substr(0, 2));
			        int day = stoi(User.birthdate.substr(3, 2));
			        int year = stoi(User.birthdate.substr(6, 2));
			
			        if (month >= 1 && month <= 12) {
			            if (day >= 1 && day <= 31) {
			                if (year >= 0 && year <= 99) {
			                    break; // Check valid birthdate
			                } 
							else {
			                    cout << "Invalid year. Try again." << endl;
			                }
			            } 
						else {
			                cout << "Invalid day. Try again." << endl;
			            }
			        } 
					else {
			            cout << "Invalid month. Try again." << endl;
			        }
			    } 
				else {
			        cout << "Invalid format. Try again. (e.g. 12/25/05)." << endl;
			    }
			}
	        
	      	while (true) {	// Age input and validation
		        cout << "Input your Age (number): ";
		        cin >> User.age;
		        
				if (cin.fail()) { // Check for invalid input
		        	cout << "Invalid Input. Try again." << endl;
			        cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear buffer
				}
				else {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear buffer 
					break;
				}
	    	}
	    	
	        cout << "\nAre all information correct? [1/0] \nEnter selection (Check if changes are needed): "; // Confirmation
	        int infoCorrect;
	        
			while (true) {	// Confirm Information
	        	while (true) {
					
		        	cin >> infoCorrect;
		        	cout << endl;
		        	
					if (cin.fail()) { // Checks if input is ok
			        	cout << "Invalid Input. Try again." << endl;
				        cin.clear();
				        cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else { 
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
						break;
		        	}
		    	}
	        		
				if (infoCorrect < 0 || infoCorrect > 1) {
	        		cout << "Invalid Input. Try again."<< endl; // Check for invalid input
				}
				else {
					break;
				}
			}
				
			if (infoCorrect == 1) {	// Confirmed correct info
	       		break;	// Exit registration loop
	       	}
		}
			
	ofstream clientInfo;	// Save user data to files
	clientInfo.open(username + ".txt");
	clientInfo << username << endl << password;
	clientInfo.close();
	        
	ofstream personInfo;
	personInfo.open(username + "profile.txt");
	personInfo << "------------------------------\n";
	personInfo << "Name: " << User.firstname << " " << User.surname << endl << endl;
	personInfo << "Gender: " << User.gender << endl << endl;
	personInfo << "Birthdate: " << User.birthdate << endl << endl;
	personInfo << "Age: " << User.age << endl;
	personInfo << "------------------------------\n";
	personInfo.close();
	    	
	system("cls"); // Clears console screen
}

void editProfile(string user) {	// Allows user to update basic profile information
	userInformation User;
	
	while (true) {	  // Ask for updated information
		system("cls"); // Clears console screen
		cout << "EDIT PROFILE";
		line();
	    cout << "Input your First Name: ";
	    cin.ignore();
	    getline(cin,User.firstname);
	    cout << "Input your Surname: ";
	    getline(cin,User.surname);
	        
		while (true) {
			cout << "Input your Gender (Male, Female, Others): ";
			cin >> User.gender;
			
			if (User.gender == "Male" || User.gender == "male" || User.gender == "MALE") {
			    break;
			} 
			else if (User.gender == "Female" || User.gender == "female" || User.gender == "FEMALE") {
			    break;
			} 
			else if (User.gender == "Others" || User.gender == "others" || User.gender == "OTHERS") {
			    break;
			} 
			else {
			    cout << "Invalid Input. Try again." << endl;
			}
		}
	        
	    while (true) {
			cout << "Input your Birthdate (MM/DD/YY): ";
			cin >> User.birthdate;
			
			if (User.birthdate.length() == 8 && User.birthdate[2] == '/' && User.birthdate[5] == '/' &&  
				isdigit(User.birthdate[0]) && isdigit(User.birthdate[1]) && isdigit(User.birthdate[3]) && 
				isdigit(User.birthdate[4]) && isdigit(User.birthdate[6]) && isdigit(User.birthdate[7])) {
			
			    int month = stoi(User.birthdate.substr(0, 2));
			    int day = stoi(User.birthdate.substr(3, 2));
			    int year = stoi(User.birthdate.substr(6, 2));
			
			    if (month >= 1 && month <= 12) {
			        if (day >= 1 && day <= 31) {
			            if (year >= 0 && year <= 99) {
			                break; // Check valid birthdate
			            } 
						else {
			                cout << "Invalid year. Try again." << endl;
			            }
			        } 
					else {
			            cout << "Invalid day. Try again." << endl;
			        }
			    } 
				else {
			        cout << "Invalid month. Try again." << endl;
			    }
			} 
			else {
			    cout << "Invalid format. Try again. (e.g. 12/25/05)." << endl;
			}
		}
	        
	    while (true) {
		    cout << "Input your Age (number): ";
		    cin >> User.age;
		        
			if (cin.fail()) { // Checks if input is ok
		        cout << "Invalid Input. Try again." << endl;
			    cin.clear();
			    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Checks for incompatible inputs
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
				break;
			}
	    }
	    	
	    cout << "\nAre all information correct? [1/0] \nEnter selection (Check if changes are needed): "; // Confirmation
	    int infoCorrect;
	        
		while (true) {
	        while (true) {
					
		        cin >> infoCorrect;
		        cout << endl;
		        	
				if (cin.fail()) { // Checks if input is ok
			        cout << "Invalid Input. Try again." << endl;
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else { 
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
					break;
		        }
		    }
	        		
			if (infoCorrect < 0 || infoCorrect > 1) {
	        	cout << "Invalid Input. Try again."<< endl; // Error Checker
			}
			else {
				break;
			}
		}
				
		if (infoCorrect == 1) { // Confirmed if 0, repeats profile creation process
	       	break;
	    }
	}	
			
	ofstream personInfo;	 // Rewrite user profile file with updated info
	personInfo.open(user + "profile.txt");
	personInfo << "------------------------------\n";
	personInfo << "Name: " << User.firstname << " " << User.surname << endl << endl;
	personInfo << "Gender: " << User.gender << endl << endl;
	personInfo << "Birthdate: " << User.birthdate << endl << endl;
	personInfo << "Age: " << User.age << endl;
	personInfo << "------------------------------\n";
	personInfo.close();
			
	system("cls");	
}

string LoginCheck() {  // Validates user login credentials and returns username if successful
    string username, password, user, pass;
	system("cls");
	cout << "LOG IN";
	line();
	cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin.ignore();
	getline (cin, password);
    ifstream check(username + ".txt");	// Open file with username	
    getline(check,user);
    getline(check,pass);
    
    if (user == username && pass == password) {
    	system("cls"); // Clears console screen
    	return username;	// Return username if valid
	}
	else {
		return "";	// Return empty string if failed
	}
}

void dailyLogsMenu() { // Shows the main menu options for logging
    cout << "MAIN MENU";
	line();
	cout << "(1) Create New Log" << endl;
    cout << "(2) View Log History" << endl;
    cout << "(3) Check Profile" << endl;
    cout << "(4) BMI Checker" << endl;
    cout << "(5) Edit Profile" << endl;
    cout << "(6) Delete Log History" << endl;
    cout << "(7) Delete Account" << endl;
    cout << "(8) Log Out" << endl;
    cout << "Select option: ";
}

void logMenu(const string &username, userDailyInput &inputs, foodtrack &foodInputs) {	// Allows user to create new daily logs for activity and food
    int option;
    
	do {
		cout << "NEW LOG";
		line();
		cout << "(1) Physical Activity Log\n";
		cout << "(2) Daily Food Log\n";
		cout << "(3) Exit\n";
        
		while (true) {
			cout << "Enter your selection: ";
			cin >> option;
			
			if (cin.fail() || option < 1 || option > 3) { // checks if input is valid
				cout << "\nInvalid Input. Try again." << endl;
				cin.clear();
				cout << "Press <Enter> to return.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
				system("cls");
				cout << "NEW LOG";
				line();
				cout << "(1) Physical Activity Log\n";
				cout << "(2) Daily Food Log\n";
				cout << "(3) Exit\n";
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break; // exits input loop when valid
			}
		}
	
		switch (option) {
			case 1: {
				system("cls");
				cout << "ACTIVITY LOG";
				logActivity(username, inputs); 
				break;
			}
			case 2: {
				system("cls");
				cout << "FOOD LOG";
				logFood(username, foodInputs); 
				break;
			}
			case 3: {
				break;
			}
			default: {
				cout << "Invalid Input. Try again.\n";
				cout << "\nPress <Enter> to return.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
				break;
			}
		}
	} 

	while (option != 3);
}

void logActivity(const string &username, userDailyInput &inputs) {	// Stores user's daily activity log into file
    line();
    inputs.date = getDate("Date (MM/DD/YY): ");
    inputs.restingHeartrate = getFloat("Resting Heartrate: ", 30, 200);
    inputs.typePhysicalActivity = getString("Physical Activity: ");
    inputs.intensity = getString("Intensity: ");
    inputs.maximalHeartrate = getFloat("Maximal Heartrate: ", 50, 220);
    inputs.duration = getFloat("Duration (minutes): ", 1, 600);
    inputs.totalSteps = getInt("Total Steps: ", 0, 100000);
    
	ofstream activityLog(username + "activityLog.txt", ios::app);	 // Save data to user’s activity log file
    
	if (activityLog.is_open()) {
        activityLog << "Date: " << inputs.date << endl
             << "Resting HR: " << inputs.restingHeartrate << endl
             << "Activity: " << inputs.typePhysicalActivity << endl
             << "Intensity: " << inputs.intensity << endl
             << "Max HR: " << inputs.maximalHeartrate << endl
             << "Duration: " << inputs.duration << " mins\n"
             << "Steps: " << inputs.totalSteps << endl
             << "------------------------------\n\n";
        activityLog.close();
        cout << "\nActivity log saved.\n";
        cout << "Press <Enter> to return.\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get(); 
    } 
	else {
        cout << "Error opening exercise log.\n";
    }
    
    system("cls");
}

void logFood(const string &username, foodtrack &foodInputs) {	// Stores user's food log into file
    line();
    foodInputs.date = getDate("Date (MM/DD/YY): ");
    foodInputs.breakfast = getString("Breakfast: ");
    foodInputs.lunch = getString("Lunch: ");
    foodInputs.dinner = getString("Dinner: ");
    foodInputs.snacks = getString("Snacks: ");

    ofstream foodlog(username + "foodlog.txt", ios::app);	 // Save data to user’s food log file	
    
	if (foodlog.is_open()) {
        foodlog << "Date: " << foodInputs.date << endl
             << "Breakfast: " << foodInputs.breakfast << endl
             << "Lunch: " << foodInputs.lunch << endl
             << "Dinner: " << foodInputs.dinner << endl
             << "Snacks: " << foodInputs.snacks << endl
             << "------------------------------\n";
        foodlog.close();
        cout << "Food log saved.\n";
        cout << "Press <Enter> to return.\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
    } 
	else {
        cout << "Error opening foodlog.\n";
    }
    
    system("cls");
}

string getDate(const string &prompt) {	// Prompts user for a valid date and validates format and digits
    string date;

    while (true) {
        cout << prompt;
        getline(cin, date);

        if (date.length() == 8 && date[2] == '/' && date[5] == '/' &&
            isdigit(date[0]) && isdigit(date[1]) &&
            isdigit(date[3]) && isdigit(date[4]) &&
            isdigit(date[6]) && isdigit(date[7])) {	// Check for correct format (MM/DD/YY)

            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 2));

            if (month >= 1 && month <= 12) {
                if (day >= 1 && day <= 31) {
                    if (year >= 0 && year <= 99) {
                        return date;	// Valid date
                    } 
					else {
                        cout << "Invalid year. Try again.\n";
                    }
                } 
				else {
                    cout << "Invalid day. Try again.\n";
                }
            } 
			else {
                cout << "Invalid month. Try again.\n";
            }
        } 
		else {
            cout << "Invalid format. Try again. (e.g. 12/25/05)\n";
        }
    }
}

float getFloat(const string &prompt, float min, float max) {	// Uses try-catch to handle invalid string-to-float conversions
    string input;
    
	while (true) {
        cout << prompt;
        getline(cin, input);
        
		try {
            float value = stof(input);	// Attempt to convert string to float
            if(value >= min && value <= max) return value;	// Check range
        } 
		catch(...) {}	 // Catch invalid conversions (non-numeric input)
        
		cout << "Invalid Input. Enter a number between " << min << " and " << max << ".\n";
    }
}

int getInt(const string &prompt, int min, int max) {	// Uses try-catch to handle invalid string-to-int conversions
    string input;
    
	while (true) {
        cout << prompt;
        getline(cin, input);
        
		try {
            int value = stoi(input);	// Attempt to convert string to int
            if(value >= min && value <= max) return value;	// Check range
        } 
		catch(...) {}	// Catch invalid conversions (non-numeric input)
        
		cout << "Invalid Input. Enter a number between " << min << " and " << max << ".\n";
    }
}

string getString(const string &prompt) {	 // Prompts user for a non-empty string input
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
		if (!input.empty()) {	// Accept if not empty
			return input;
		}
		
		cout << "Input cannot be empty.\n";
	}
}

void line() {	// Prints a visual divider line for readability
	cout << "\n============================\n\n";
}

void BMIdisplayHeader() {	// Displays the BMI calculator heading and information
    cout << "BMI CHECKER";
	line();
	cout << "--------------------------------------------------------------------------\n";
    cout << "                          B M I   C A T E G O R Y";
    cout << "\n--------------------------------------------------------------------------\n";
    cout << setw(15) << " Morbidly Obese " << setw(10) << " Obese " << setw(15) 
         << " Overweight " << setw(18) << " Normal Weight " << setw(15) << " Underweight " << endl;
    cout << setw(12) << "40 above" << setw(15) << "30.0/39.9" << setw(13) 
         << "25.0/29.9" << setw(17) << "18.5/ 24.9" << setw(16) << "18.5 below";
    cout << "\n--------------------------------------------------------------------------\n";
}

void computeBMI() {	// Calculates Body Mass Index based on user height and weight	
	float height, weight;
		while (true) {
			cout << "\nEnter Height (in meters): ";
    		cin >> height;
	        	
				if (cin.fail()) { // Checks if input is ok
		        	cout << "Invalid Input. Try again.";
			        cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}	
				else {
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
					break;
		        }
		    }
		    
    	while (true) {
			cout << "Enter Weight (in kg): ";
			cin >> weight;
		        
				if (cin.fail()) { // Checks if input is ok
			       	cout << "Invalid Input. Try again.\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}	
				else {
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
					break;
		        }
		    }
    
    system("cls");
    
    double bmi = weight / (height * height);	// Formula for computing BMI
    cout << "Your BMI result is " << bmi << ".\n";   

	// Interpret the result
    if (bmi >= 40) {	// BMI is Morbidly Obese
        cout << endl;
		cout << left << setw(10) << "Status: Morbidly Obese\n";
		cout << "Workout Suggestions:\n";
		cout << "-----------------------------------------------------------------\n";
		
		cout << char(254) << " Aerobic Exercises (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Walking" << "(2x / 10 mins)   3x a week\n";
		cout << "  -> " << left << setw(18) << "Jogging" << "(2x / 10 mins)   3x a week\n";
		cout << "  -> " << left << setw(18) << "Stair Climbing" << "(10 mins)   2x a week\n\n";
		
		cout << char(254) << " Before You Start:\n";
		cout << "  -> " << left << setw(20) << "Consult a Doctor" << "(especially for medical conditions)\n";
		cout << "  -> " << left << setw(20) << "Eat Healthy Foods" << "(Calorie Deficit Diet)\n\n";
		
		cout << char(254) << " Food Suggestions:\n";
	    cout << "  -> High-protein foods (eggs, lean meat, tofu)\n";
	    cout << "  -> Fiber-rich vegetables\n";
	    cout << "  -> Limit fried and sugary foods\n\n";
		
		cout << char(254) << " Don't push yourself too hard, rest after workouts.\n";
		cout << "-----------------------------------------------------------------\n";
    }
    
    else if (bmi >= 30) {	// BMI is Obese
        cout << endl;
		cout << left << setw(10) << "Status: Obese\n";
		cout << "Workout Suggestions:\n";
		cout << "-----------------------------------------------------------------\n";
		
		cout << char(254) << " Aerobic Exercises (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Walking" << "(3x / 10 mins)   5x a week\n";
		cout << "  -> " << left << setw(18) << "Jogging" << "(3x / 10 mins)   5x a week\n";
		cout << "  -> " << left << setw(18) << "Stair Climbing" << "(10 mins)   3x a week\n\n";
		
		cout << char(254) << " Body Weight Exercises (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Push Ups / Knee Push Ups" << "(2-3 sets / 8-10 reps)\n";
		cout << "  -> " << left << setw(18) << "Squats" << "(2-3 sets / 8-10 reps)\n\n";
		
		cout << char(254) << " Before You Start:\n";
		cout << "  -> " << left << setw(20) << "Consult a Doctor" << "(especially for medical conditions)\n";
		cout << "  -> " << left << setw(20) << "Eat Healthy Foods" << "(Calorie Deficit Diet)\n\n";
		
		cout << char(254) << " Food Suggestions:\n";
	    cout << "  -> Lean protein (chicken, fish, eggs, tofu)\n";
	    cout << "  -> Plenty of vegetables and fiber\n";
	    cout << "  -> Limit sugar, fried foods, and processed snacks\n\n";
		
		cout << char(254) << " Don't push yourself too hard, rest after workouts.\n";
		cout << "-----------------------------------------------------------------\n";
    }
    
    else if (bmi >= 25) {	// BMI is Overweight
        cout << endl;
		cout << left << setw(10) << "Status: Overweight\n";	
	    cout << "Workout Suggestions:\n";
	    cout << "-----------------------------------------------------------------\n";
	
	    cout << char(254) << " Aerobic Exercises (Low Intensity)\n";
	    cout << "  -> " << left << setw(18) << "Walking" << "(5x / 10 mins)   5x a week\n";
	    cout << "  -> " << left << setw(18) << "Jogging" << "(5x / 10 mins)   5x a week\n";
	    cout << "  -> " << left << setw(18) << "Stair Climbing" << "(2x / 10 mins)   3x a week\n\n";
	
	    cout << char(254) << " Body Weight Exercises (Low Intensity)\n";
	    cout << "  -> " << left << setw(18) << "Push Ups / Knee Push Ups" << "(2-3 sets / 8-12 reps)\n";
	    cout << "  -> " << left << setw(18) << "Squats" << "(2-3 sets / 8-10 reps)\n\n";
	
	    cout << char(254) << " Light Weight Strength Training (Low Intensity)\n";
	    cout << "  -> " << left << setw(18) << "Push Pull Leg Program" << "\n";
	    cout << setw(8) << " " << "- 2-3 sets / 8-12 reps\n";
	    cout << setw(8) << " " << "- 2-3x a week (Gym Activities)\n\n";
	
	    cout << char(254) << " Before You Start:\n";
	    cout << "  -> " << left << setw(20) << "Consult a doctor" 
	         << "(especially for medical conditions)\n";
	    cout << "  -> " << left << setw(20) << "Eat healthy foods" 
	         << "(Calorie Deficit Diet)\n\n";
	         
	    cout << char(254) << " Food Suggestions:\n";
	    cout << "  -> High-protein foods (chicken, fish, eggs, tofu)\n";
	    cout << "  -> Plenty of vegetables and fiber-rich foods\n";
	    cout << "  -> Limit sugar, fried foods, and processed snacks\n\n";
	         
		cout << char(254) << " Lift weights you can carry, start with low weights.\n\n";
	
	    cout << char(254) << " Don't push yourself too hard, rest after workouts.\n";
	    cout << "-----------------------------------------------------------------\n";
    }
    
    else if (bmi >= 18.5) {	// BMI is Normal Weight
        cout << endl;
		cout << left << setw(10) << "Status: Normal Weight\n";
		cout << "Workout Suggestions\n";
		cout << "-----------------------------------------------------------------\n";
		
		cout << char(254) << " Aerobic Exercises (Low/Moderate Intensity)\n";
		cout << "  -> " << left << setw(18) << "Walking" << "(6x / 10 mins)   4x a week\n";
		cout << "  -> " << left << setw(18) << "Jogging" << "(6x / 10 mins)   4x a week\n\n";
		
		cout << char(254) << " Body Weight Exercises (Low/Moderate Intensity)\n";
		cout << "  -> " << left << setw(18) << "Push Ups / Knee Push Ups" << "(2-3 sets / 8-12 reps)\n";
		cout << "  -> " << left << setw(18) << "Squats" << "(2-3 sets / 8-10 reps)\n";
		cout << "  -> " << left << setw(18) << "Pull Ups" << "(2-3 sets / 8-10 reps)\n\n";
		
		cout << char(254) << " Equipment Weight Strength Training (Low/Moderate Intensity)\n";
		cout << "  -> " << left << setw(18) << "Push Pull Leg Program" << "\n";
		cout << setw(8) << " " << "- 2-3 sets / 8-12 reps\n";
		cout << setw(8) << " " << "- 4x a week (Gym Activities)\n\n";
		
		cout << char(254) << " Food Suggestions:\n";
	    cout << "  -> Balanced diet with carbs, protein, and healthy fats\n";
	    cout << "  -> Include vegetables, fruits, and whole grains\n";
	    cout << "  -> Maintain proper hydration\n\n";
		
		cout << char(254) << " Lift weights you can carry, start with low weights.\n\n";
		
		cout << char(254) << " Keep it up, don't push yourself too hard, rest after workouts.\n";
		cout << "-----------------------------------------------------------------\n";
    }
    
    else {	// BMI is Underweight
        cout << endl;
		cout << left << setw(10) << "Status: Underweight\n";
		cout << "Workout Suggestions:\n";
		cout << "-----------------------------------------------------------------\n";
		
		cout << char(254) << " Aerobic Exercises (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Walking" << "(2x / 10 mins)   2x a week\n";
		cout << "  -> " << left << setw(18) << "Jogging" << "(2x / 10 mins)   2x a week\n\n";
		
		cout << char(254) << " Body Weight Exercises (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Push Ups / Knee Push Ups" << "(2 sets / 8 reps)\n";
		cout << "  -> " << left << setw(18) << "Squats" << "(2 sets / 8 reps)\n";
		cout << "  -> " << left << setw(18) << "Pull Ups" << "(2 sets / 8 reps)\n\n";
		
		cout << char(254) << " Equipment Weight Strength Training (Low Intensity)\n";
		cout << "  -> " << left << setw(18) << "Dumbbell Activities" << "\n";
		cout << setw(8) << " " << "- 2 sets / 8 reps\n";
		cout << setw(8) << " " << "- 2x a week (Gym Activities)\n\n";
		
		cout << char(254) << " Food Suggestions:\n";
	    cout << "  -> High-calorie, protein-rich foods (nuts, eggs, dairy, lean meat)\n";
	    cout << "  -> Include healthy carbs (rice, oats, whole grains)\n";
	    cout << "  -> Snack between meals to gain weight safely\n\n";
		
		cout << char(254) << " Lift weights you can carry, start with low weights.\n\n";
		
		cout << char(254) << " Don't push yourself too hard, rest after workouts. You can do it!\n";
		cout << "-----------------------------------------------------------------\n";
    }
}

void deleteLogs(const string &username) {	// Removes both exercise and food logs for the specified user
    int option;

    while (true) {
        system("cls");	// Clear at the start of menu display
        cout << "DELETE LOGS MENU";
        line();
        cout << "(1) Delete Activity Log\n";
        cout << "(2) Delete Food Log\n";
        cout << "(3) Exit\n";

        while (true) {
            cout << "Enter your selection: ";
            cin >> option;

            if (cin.fail() || option < 1 || option > 3) {
                cout << "\nInvalid Input. Try again." << endl;
				cin.clear();
				cout << "Press <Enter> to return.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
				system("cls");	// Clear at the start of menu display
		        cout << "DELETE LOGS MENU";
		        line();
		        cout << "(1) Delete Activity Log\n";
		        cout << "(2) Delete Food Log\n";
		        cout << "(3) Exit\n";
            } 
			else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear buffer
                break;	// valid option, exit input loop
            }
        }

        switch (option) {
            case 1: {
                int confirm;
                while (true) {
                    system ("cls");
					cout << "ACTIVITY LOG DELETION";
	    			line();
					cout << "Are you sure you want to delete the Activity Log? [1/0]: ";
                    cin >> confirm;

                    if (cin.fail() || (confirm != 0 && confirm != 1)) {
                        cin.clear();
			            cout << "\nInvalid Input. Try again.\n";
						cout << "Press <Enter> to return.\n";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin.get();
					    system ("cls");
                    } 
					else {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear buffer
                        break;	// valid confirmation
                    }
                 }

                if (confirm == 1) {
                    if (remove((username + "activityLog.txt").c_str()) == 0) {
                        cout << "\nActivity log deleted successfully.\n";
                    } 
					else {
                        cout << "\nNo activity log found to delete.\n";
                    }
                } 
				else {
                    cout << "\nActivity log deletion cancelled.\n";
                }

                cout << "Press <Enter> to return.";
                cin.get();
                break;
            }

            case 2: {
                int confirm;
                while (true) {
                    system ("cls");
					cout << "FOOD LOG DELETION";
	    			line();
					cout << "Are you sure you want to delete the Food Log? [1/0]: ";
                    cin >> confirm;

                    if (cin.fail() || (confirm != 0 && confirm != 1)) {
                        cin.clear();
			            cout << "\nInvalid Input. Try again.\n";
						cout << "Press <Enter> to return.\n";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin.get();
					    system ("cls");
                    } 
					else {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');	 // clear buffer
                        break;	// valid confirmation
                    }
                }

                if (confirm == 1) {
                    if (remove((username + "foodlog.txt").c_str()) == 0) {
                        cout << "\nFood log deleted successfully.\n";
                    } 
					else {
                        cout << "\nNo food log found to delete.\n";
                    }
                } 
				else {
                    cout << "\nFood log deletion cancelled.\n";
                }

                cout << "Press <Enter> to return.";
                cin.get();
                break;
            }

            case 3:
                return;	// Exit delete logs menu

            default:
                cout << "Invalid Input. Try again." << endl;
				cout << "Press <Enter> to return.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
		        system ("cls");
				break;
        }
    }
}

bool deleteUserAccount(const string &username) {	// Permanently deletes user credentials and profile
    int choice;

    while (true) {
    	system("cls");
		cout << "ACCOUNT DELETION";
	    line();
        cout << "Are you sure you want to delete this account? [1/0]: ";
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 1) {
            cin.clear();
            cout << "\nInvalid Input. Try again.\n";
			cout << "Press <Enter> to return.\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		    system ("cls");
        } 
		else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            break;
        }
    }

    if (choice == 1) {	// delete all files linked to the user
        remove((username + ".txt").c_str());
        remove((username + "profile.txt").c_str());
        remove((username + "foodlog.txt").c_str());
        remove((username + "activityLog.txt").c_str());

        cout << "\nAccount deleted successfully.\n";
        cout << "Press <Enter> to return to main menu.\n";
        cin.get();
        system("cls");
        return true;	// Account deleted
    } 
	else {
        cout << "\nAccount deletion cancelled.\n";
        cout << "Press <Enter> to return.\n";
        cin.get();
        system("cls");
        return false;	// Deletion canceled
    }
}
