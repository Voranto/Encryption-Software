// EncryptionFib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> // se encarga de abrir ficheros
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string Decrypt(string text, string key) {

    vector<char> odd_arr;
    vector<char> even_arr;
    //split into even and odd
    for (int i = 0; i < text.size(); i++) {
        if (i % 2 == 0) {
            odd_arr.emplace_back(text[i]);
        }
        else {
            even_arr.emplace_back(text[i]);
        }
    }

    //calculate fibonacci
    int a = 0;
    int b = 1;
    int c = 0;

    for (int x = 0; x < key.size(); x++) {
        a = b;
        b = c;
        c = a + b;
    }


    //change values in array
    int start = int(' ');
    int end = int('z');
    for (int j = 0; j < even_arr.size(); j++) {
        int val = int(even_arr[j]);
        val += c;
        if (val > end) {
            val = val + start - end -1;
        }
        even_arr[j] = char(val);
    }

    //change values in even array

    for (int j = 0; j < odd_arr.size(); j++) {
        int val = int(odd_arr[j]);
        val -= c;
        if (val < start) {
            val += end - start;
        }
        odd_arr[j] = char(val);
    }

    string output;
    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < text.size(); i++) {
        if (i % 2 == 0) {
            output += odd_arr[p1];
            p1++;
        }
        else {
            output += even_arr[p2];
            p2++;
        }
    }

    output.erase(output.size() - key.size());


    reverse(output.begin(), output.begin() +  key.size()) ;
    reverse(output.begin() + key.size(), output.end());
    reverse(output.begin(), output.end());




    return output;


}


string Encrypt(string text, string key) {
    //reversing string

    reverse(text.begin(), text.begin() + text.size() - key.size());
    reverse(text.begin() + text.size() - key.size(), text.end());
    reverse(text.begin(), text.end());

    // public key, symmetric encryption
    

    //combine text and key
    string combination = text + key;
    vector<char> combination_arr;
    for (char letter : combination) {
        combination_arr.emplace_back(letter);
    }

    vector<char> odd_arr;
    vector<char> even_arr;

    for (int i = 0; i < combination_arr.size(); i++) {
        if (i % 2 == 0) {
            odd_arr.emplace_back(combination_arr[i]);
        }
        else {
            even_arr.emplace_back(combination_arr[i]);
        }
    }


    // fibonacci initial sequence
    int a = 0;
    int b = 1;
    int c = 0;

    for (int x = 0; x < key.size(); x++) {
        a = b;
        b = c;
        c = a + b;
    }



    //change values in array
    int start = int(' ');
    int end = int('z');
    for (int j = 0; j < odd_arr.size(); j++) {
        int val = int(odd_arr[j]);
        val += c;
        if (val > end) {
            val = val + start - end;
        }
        odd_arr[j] = char(val);
    }

    //change values in even array

    for (int j = 0; j < even_arr.size(); j++) {
        int val = int(even_arr[j]);
        val -= c;
        if (val < start) {
            val += end - start +1 ;
        }
        even_arr[j] = char(val);
    }

    string output;
    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < combination_arr.size(); i++) {
        if (i % 2 == 0) {
            output += odd_arr[p1];
            p1++;
        }
        else {
            output += even_arr[p2];
            p2++;
        }
    }
    cout << output << endl;
    return output;
}


int main()
{
    string filename;
    char mode;
    cout << "Welcome to the encrytption tool, please make sure that the document to be encrypted is in the same directory as the .cpp file." << endl;
    cout << "Input your filename (with the .txt): ";
    cin >> filename;
    cout << "Do you want to Encrypt(E) or Decrypt(D): ";
    cin >> mode;

    string key = "contrasena";


    // read file
    ifstream inputFile(filename);
    
    // initialize line and text variables
    string text;
    string line;
    ofstream MyFile;
    // loop through all the lines in the text
    if (inputFile.is_open()) {
        if (mode == 'E') {
            MyFile.open("Encrypted_" + filename);
        }
        else if (mode == 'D') {
            MyFile.open("Decrypted_" + filename);

        }
        while (getline(inputFile, line)) {
            //check if decrypt or encrypt
            if (mode == 'E') {
                string answer = Encrypt(line, key);
                MyFile << answer << "\n";
            }
            else if (mode == 'D') {
                string answer = Decrypt(line, key);
                MyFile << answer << "\n";
                
            }
            else {
                cerr << "ERROR: Mode not inputted correctly";
                return -1;
            }
        }
        
    }
    else {
        cout << "File not found" << endl;
        return -1;
    }

    inputFile.close();
    string answer;
    //Placeholder

    

    
    
    return 0;
}

