#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void retrievePassword() {
    system("color e");
    cout << "\nsamz>\t";
    system("netsh wlan show profile");
    
    cout << "WHICH ONE?--";

    string networkName;
    getline(cin, networkName);

    string command = "netsh wlan show profile \"" + networkName + "\" key=clear > temp.txt";
    system(command.c_str());

    ifstream file("temp.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find("Key Content") != string::npos) {
                found = true;
                size_t pos = line.find(":");
                if (pos != string::npos) {
                    string password = line.substr(pos + 2);
                    cout << "Your password is: " << password << endl;
                } else {
                    cout << "Password not found." << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Network not found or password not available." << endl;
        }
        file.close();
        remove("temp.txt");
    } 

    cout << "Press Enter to run the program again" << endl;
}

int main() {
    char key;
    do {
        retrievePassword();
        key = cin.get();
        system("cls");
    } while (true); 
    return 0;
}
