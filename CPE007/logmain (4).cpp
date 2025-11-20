#include <iostream>	// Input/output stream
#include <iomanip>	// Formatting output
#include <string>	// std::string
#include <fstream> 	// File handling
#include <cstdlib> 	// System("cls") for clearing screen
#include <limits>	// For input validation 
#include <vector>	// Dynamic array to store lines
#include <cstdio>	// For account/log deletion

#include "function_logs.h"	// Include header file with functions

using namespace std;

int main() {
    
	while (true) {	// Main program loop
		system ("cls");
		cout << "DAILY FITNESS LOGGING SYSTEM";
		line();
		int choice;
	    cout << "(1) Register New User" << endl;
		cout << "(2) Log In" << endl;
		cout << "(3) Exit" << endl;
		
		while(true) {	// Input validation loop for main menu
		    cout << "Enter your selection: ";
			cin >> choice;
		    
			 if (cin.fail() || choice < 1 || choice > 3) {	// Invalid input check
				cout << "\nInvalid Input. Try again." << endl;
				cin.clear();
				cout << "Press <Enter> to return.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
		        system ("cls");
		        cout << "FITNESS MONITORING SYSTEM" << endl; // Re-display menu after invalid input
            	line();
            	cout << "(1) Register New User" << endl;
				cout << "(2) Log In" << endl;
				cout << "(3) Exit" << endl;
			}			
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
				break;
			}
		}
			
	    cout << endl;
	    
	    if (choice == 1) {	// Register new user
	    	registerUser();
	    }
	    else if (choice == 2) {	// Log in
	        string confirm;	// Stores logged-in username
	        confirm = LoginCheck();
	        
			if (confirm != "") {	// Successful login
		        bool accountDeleted = false;
				
				while (true) {	// Logged-in user menu loop
					int option;
					system("cls");
					
			        dailyLogsMenu();	// Display user menu
			        cin >> option;
			        cout << endl;
			        
			        if (cin.fail()) {	// Invalid menu input
					    cin.clear();
					    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
					    cout << "Invalid Input. Try again.\n";
					    cout << "Press <Enter> to return.\n";
					    cin.get();
					    system("cls");
					    continue;	// Redisplay menu
					}
			        
					if (option == 8) {	// Log out
			        	cout << "Press <Enter> to Log out.";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin.get();
						system("cls");
						break;
					}
					
			        switch(option) {
			        	case 1: {	// Create new logs
						    system("cls");
						    userDailyInput inputs;
						    foodtrack foodInputs;
						    logMenu(confirm, inputs, foodInputs);	// Call log menu
						    cout << "\nLogs created successfully.\n";
						    cout << "Press <Enter> to return.\n";
						    cin.get();
						    break;
						}
			        	case 2: { // View Log History
						    system("cls"); // clear screen
						    ifstream logFile(confirm + "activityLog.txt");
						    vector <string> lines;
						    cout << "LOG HISTORY";
							line();
							string line, linefood;
						
							if (logFile.is_open()) {	// Read exercise log
						        while (getline(logFile, line)) {
						            lines.push_back(line);
						        }
						        logFile.close();
								cout << "Exercise Logs:\n" << endl;
								cout << "------------------------------\n";
						        int start = (lines.size() > 30) ? lines.size() - 30 : 0;	// Last 30 lines
						        
								for (int i = start; i < lines.size(); ++i) {
						            cout << lines[i] << endl;
						        }
						    } 
							else {
						        cout << "No logged activity history found for the user: " << confirm << endl << endl;
						    }
						    
						    ifstream logFileFood(confirm + "foodlog.txt");
						    vector <string> lines1;
						    
	
						    if (logFileFood.is_open()) {	// Read food log
						        while (getline(logFileFood, linefood)) {
						            lines1.push_back(linefood);
						        }
						        cout << "\nFood Logs:\n" << endl;
								cout << "------------------------------\n";
						        logFileFood.close();	// Show up to the last 7 lines
						        int start = (lines1.size() > 30) ? lines1.size() - 30 : 0;	// Last 30 lines
						        
								for (int i = start; i < lines1.size(); ++i) {
						            cout << lines1[i] << endl;
						        }
						    } 
							else {
						        cout << "No logged food history found for the user: " << confirm << endl;
						    }
						    
						    cout << "\nPress <Enter> to return.\n";
						    cin.ignore(numeric_limits<streamsize>::max(), '\n');
						    cin.get();
					    	break;
						}	
			        	case 3: {	// View profile
						    system("cls");
						    cout << "USER PROFILE";
							line();
							string proLine;
						    ifstream check(confirm + string("profile.txt"));
						    
							if (check.is_open()) {
						        while (getline(check, proLine)) {
						            cout << proLine << endl;
						        }
						        check.close();
						    } 
							else {
						        system("cls");
						        cout << "Error opening profile." << endl;
						    }
						    
						    cout << "\nPress <Enter> to return.\n";
						    cin.ignore(numeric_limits<streamsize>::max(), '\n');
						    cin.get();
					    break;
						}
						case 4: {	// BMI Calculator
							bool choiceBMI;
							while(true) {
								system("cls");
								BMIdisplayHeader();    
							    computeBMI(); 
							    cout << "\nReturn to Menu? [1/0]: ";
							    choiceBMI = continueConfirm();
							    
								if (choiceBMI == 1){
							    	break;
								}
							}
							break;
						}
						case 5: {	// Edit profile 
							system("cls");
							editProfile(confirm);
							break;
						}
						case 6: {	// Delete logs
						    system("cls");
						    deleteLogs(confirm);
						    break;
						}
						case 7: {	// Delete account
							system("cls");
						    accountDeleted = deleteUserAccount(confirm); // true if account deleted
						    break;
						}
						default: {	// Invalid menu option
							cout << "Invalid Input. Try again." << endl;
							cout << "Press <Enter> to return.\n";
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cin.get();
		        			system ("cls");
							break;
						}
					}
					
					if (accountDeleted) {	// Exit if account deleted
				        system("cls");
					    cout << "You no longer have access to this account.\n";
					    cout << "Double press <Enter> to Log out.\n";
					    cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin.get();
					    break;
				    }
				} 
	        }
	        else if (confirm == "") {	// Failed login
				cout << "\nInvalid Login. Try again." << endl;
		        cout << "Press <Enter> to return.\n";
				cin.get();
		        system ("cls");
			}
		}
		else if (choice == 3) {	// Exit program
			return 0;
		}
	    else if (choice < 1 || choice > 3) {	// Extra safety check
	    	cout << "Invalid Input. Try again." << endl;
		}
	}
}
