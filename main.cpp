/*
 * main.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: softserve
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

void fSwap(int &a, int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}
bool fChessBoardColor(int m, int n, int k, int l)
{
	return (n%2+m%2)%2 == (l%2+k%2)%2;
}
int fTCByDelimeter(int i, int k)
{
	if (!(i%k))
		return i - k;
	else if (!(k%i)) // actually, there is NO NEED IN 'else', as 'return' will go back to caller and terminate this function. 'Else' is used in performance purpose, as it is generated in very low assembly level anyways, as 'if' is hardware command with two case branches. So, using 'else' will save one 'NOP' or 'GOTO' command
		return k - i;
	else // the same performance issue described above, otherwice, no need in 'else'
		return k + i;
}

int main(int argc, char ** argv)
{
	cout<<"Welcome to PSET1!\n";
	int user_command = 1;
	while (user_command)
	{
		cout<<"\nInput task number you want to check (0 for exit):\n";
		cin>>user_command;
		switch (user_command)
		{
			case 0:
				cout<<"Thank you for your attention. Bye.\n";
				return 0;
			case 1:
			{
				cout<<"You have selected SWAP TASK\n";
				int a,b;
				cout<<"\ta = "; cin>>a;
				cout<<"\tb = "; cin>>b;
				fSwap(a,b);
				cout<<"\tSWAPPED: a is "<<a<<" now and b is "<<b<<endl;
				break;
			}
			case 2:
			{
				cout<<"You have selected unimplemented task\n";
				break;
			}
			case 3:
			{
				cout<<"You have selected unimplemented task\n";
				break;
			}
			case 4:
			{
				cout<<"You have selected EVERYTHING EXCEPT @ task\n\tplease, type needed symbols sequence terminated with '@' and press 'enter'\n\t";
				char inputed_symbol;
				do
				{
					cin>>inputed_symbol;
					if (inputed_symbol != 'A' && inputed_symbol != 'a' && inputed_symbol != '@') // I do not use any of "to lower case" functions in intension
						cout<<inputed_symbol;
				}
				while (inputed_symbol != '@');
				//cout<<"\b"; // TO clear last symbol, i.e. '@'. NOT WORKING IN LINUX :(((( No intension to search for proper character for compatibility purpose
				break;
			}
			case 5:
			{
				cout<<"You have selected CHESS BOARDS COLORS task\n";
				int m,n,k,l;
				cout<<"\tm = "; cin>>m;
				cout<<"\tn = "; cin>>n;
				cout<<"\tk = "; cin>>k;
				cout<<"\tl = "; cin>>l;
				if (fChessBoardColor(m,n,k,l))
					cout<<"\tselected chess board cells are of the same color\n";
				else
					cout<<"\tselected chess board cells differ by color\n";
				break;
			}
			case 6:
			{
				cout<<"You have selected unimplemented task\n";
				break;
			}
			case 7:
			{
				cout<<(char)49<<"You have selected ALPHA AND NUMERIC SYMBOLS COUNTER task\n\tplease, type needed symbols sequence terminated with '$' and press 'enter'\n\t";
				char inputed_symbol;
				int alpha = 0;
				int numeric = 0;
				do
				{
					cin>>inputed_symbol;
					/*
					 // varian 1 (not very one due to need in additional functions and thus additional stack operations. Using of inline functions will somehow solve the issues, i.e. stack ones)
					 alpha += isAlpha(inputed_symbol);
					 number += isDecimal(inputed_symbol);
					*/

					 // varian 2
					numeric += (inputed_symbol >= 48 && inputed_symbol <= 57 );
					alpha += ((inputed_symbol >= 'A' && inputed_symbol <= 'Z')  ||  (inputed_symbol >= 'a' && inputed_symbol <= 'z'));
				}
				while (inputed_symbol != '$');
				cout<<"\tquanity of numeric symbols is "<<numeric;
				cout<<"\tquanity of alpha symbols is "<<alpha<<endl;
				break;
			}
			case 8:
			{
				cout<<(char)49<<"You have selected TRIPPLE CONDITION BY DELIMETER task\n";
				int i,k;
				cout<<"\ti = "; cin>>i;
				cout<<"\tk = "; cin>>k;
				cout<<"\tz is "<<fTCByDelimeter(i, k)<<endl;
				break;
			}
			case 10:
			{
				cout<<(char)49<<"You have selected BELONGS TO PREDEFINED RANGE task\n";
				double x;
				cout<<"\tx = "; cin>>x;
				cout<<"S = "<<((x >= 2.0 && x <= 5.0) || (x >= -1.0 && x <= 1))<<endl;
				break;
			}
			case 9:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			{
				cout<<"You have selected unimplemented task\n";
				break;
			}
			default:
				cout<<"Undefined task number. Input task within the range: 1-15.\n";
				break;
		}
	}
	return 0;
}
