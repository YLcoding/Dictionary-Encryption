#include<iostream>
#include<cmath>
#include<string.h>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<bitset>
#include<iomanip>
#include <direct.h>
#define MAX_KEY 1000

using namespace std;
void Encrypation(string, string a, char(&key)[1000][1000]);
void Decrypation(string,char(&key)[1000][1000]);
void Key();
void Get_Key(char(&key)[1000][1000]);
bool File_Exist(string);
//Mac 125 Project 
int main()
{
	string afile, bfile, cfile,sumfile,notes;
	char key[MAX_KEY][MAX_KEY];
	int x,y;
	afile="c:\\ctest\\";
	cfile=".txt";
	_mkdir("C:\\ctest");
		cout << "Welcome to the, :::Encryption:: program : " << endl;//here is the main selection menu no program name yet
		cout << endl;
		cout << endl;
		cout << "Please select the following options : " << endl;
		cout << endl;
		cout << " Enter #1 to Encrypt data : " << endl;
		cout << endl;
		cout << " Enter #2 to Decrypt data : " << endl;
		cout << endl;
		cout << " Press Any other option to exit program " << endl;
		cin >> x;
		if (File_Exist("c:\\ctest\\key.txt")) {
		}
		else {
			Key();
		}
		Get_Key(key);
		switch (x){
		case 1:
			while (1) {
				cout << "Would you like to create an encrypted file ? : [1] " << endl;
				cout << endl;
				cout << "Would you like to read an existing file ?    : [2] " << endl;
				cin >> y;
				cin.ignore();// this is needed to prevent the getline from being skipped.
				if (y == 1)
				{
					cout << " Please enter file name to create : " << endl;
					cin >> bfile;
					sumfile = afile + bfile + cfile;
					cin.ignore();
					cout << "The file is created in the directory c:\\ctest" << endl;
					cout << " Please enter Text now : " << endl;
					//this is where is skipping my getline ??? why ???
					//i've done some reseach and found out that i need to inlcude a cin.ignore to avoid confilts.
					getline(cin, notes);
					Encrypation(notes, sumfile, key);
					//notes is the file to encrypt.
					cout << "The file is encrypated in the dirctory "<<sumfile << endl;
					break;
				}
				else if (y == 2) {
					string reading;
					cout << " Please put the file into c:\\ctest folder and change the file into txt file"
						<< endl << "Please enter the file name to read   : " << endl;
					cin >> bfile;
					sumfile = afile + bfile + cfile;
					ifstream read(sumfile);
					while (!read.eof()) {
						read >> reading;
						Encrypation(reading,sumfile,key);
					}
					cout << "The file is encrypated in the dirctory c:\\ctest\\encrypated.txt";
					break;
				}
				else {
					cout << "Invalid Input! Please Enter again:";
					continue;
				}
			}
			break;
		case 2:
			cout << "Please Put the file you wish to decrypated input c:\\ctest folder." << endl;
			cout << "Please Enter the file name:";
			cin >> bfile;
			sumfile = afile + bfile + cfile;
			Decrypation(sumfile,key);
		}

	return 0;
}
bool File_Exist(const string a) {        //Check if the KEY file exist
	ifstream infile(a);
	return infile.good();
}
void Key() {                            //Generate KEY file
	srand(time(NULL));
	char key[1];
	ofstream make("c:\\ctest\\key.txt");	//Dictory of the KEY file
	for (int b = 0; b < 999; b++) {		//999 row	
		for (int i = 0; i < 999; i++) {	//999 column
			key[i] = (char)(rand() % 93) + 33;  //ASCII code
			make << key[i];
		}
		make << '\n';
	}
	make.close();
}
void Get_Key(char (&key)[1000][1000]) {         //Get the data from KEY file
	char a;
	ifstream getkey("c:\\ctest\\key.txt");
	for (int b = 0; b < 999; b++) {
		for (int i = 0; i < 1000; i++) {
			getkey.get(a);
			key[b][i] = a;
		}
	}
	getkey.close();
}
void Encrypation(string contain,string filePath,char(&key)[1000][1000]) {    //Encrypation function
	srand(time(NULL));
	const int length = contain.length();
	int ecryp[1000][2];
	int column = 1;
	int rand_row = 1;
	bool control = false;
	int b = 0;
	while (b<length) {
		for (b = 0; b < length; b++) {					     //encryped all the letters
            		control=false;
			rand_row = rand() % 999;				     //Randomly find a row
			while (rand_row<=999){
				for (column = 0; column < 999; column++) {
					if (contain[b] == key[rand_row][column]) {    //Randomly find a row in the KEY file and find the letter in the column 
						ecryp[b][0] = rand_row;               //Record the index number (postion) of that letter
						ecryp[b][1] = column;		      //Record the index number (postion) of that letter
						control = true;			      //Set flag to true to break out the loop to find another letter
					}
					if(contain[b]==' '){
						ecryp[b][0]=0;
						ecryp[b][1]=0;
                      			        control=true;
					}
				}
				rand_row++;						//increase row if there is no match
				if (rand_row > 999) {
					rand_row = rand() % 999 + 1;			//if run out of rows, generate a new start point
				}
				if (control == true) {					//get to the next letter
					break;
              			}
			}
		}
	}
	ofstream encrypate(filePath,ofstream::app);                                     //Record the encrypated sequence
	for (unsigned int i = 0; i < length; i++) {
		for (int a = 0; a < 2; a++) {
			encrypate<< setw(3)<<setfill('0') << ecryp[i][a];
		}
	}
    encrypate<<'\0';
    encrypate.close();
}
void Decrypation(string filePath, char(&key)[1000][1000]){            //Decrypation function
    char decryp[1000];							//Pre-set the varible for store the encrypated string
    char done[1000];							//Pre-set the varible for store the decrypated string
    int i=0,a=3,row=0,column=0,z=0;
    ifstream decrypate(filePath);					//Reading the encrypated file
    decrypate.getline(decryp,1000);					//Reading the encrypated file
    while(decryp[i]!='\0'){						//Loop until all the letters are decrypated
        for(;i<a;i++){
            row+=((int)decryp[i]-48);					//get the string to row number 
            row*=10;
        }
        row/=10;
        a+=3;
        for(;i<a;i++){
            column+=((int)decryp[i]-48);				//get the string to column number
            column*=10;
        }
        column/=10;
        a+=3;
		if (row == 0 && column == 0) {                          //if row and column equal to 0, means it's a space
			cout << " ";
		}
		else {
			cout << key[row][column];     			//another wise find the represent letter in the KEY file
		}
        row=0,column=0;
		z++;
    }
	cout << endl;
	decrypate.close();

}
