/*
 * main.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: softserve
 */

#include <stdlib.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
using namespace std;

int fGetIO_Int(const char * message = NULL)
{
	if (message != NULL)
		cout<<message;
	int number;
	while (! (cin >> number))
	{
		cin.clear();
		cin.ignore();
		cout<<"! invalid input ! Try again: "<<endl;
	}
	return number;
}
string fGetIO_String(const char * message)
{
	if (message != NULL)
		cout<<message;
	cin.ignore();
	string str;
	getline(cin, str, '\n');
	return str;
}

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
		user_command = fGetIO_Int("\nInput task number you want to check (0 for exit):\n");
		switch (user_command)
		{
			case 0:
				cout<<"Thank you for your attention. Bye.\n";
				return 0;
			case 1:
			{
				cout<<"You have selected SWAP TASK\n";
				int a = fGetIO_Int("\ta = "), b = fGetIO_Int("\tb = ");
				fSwap(a,b);
				cout<<"\tSWAPPED: a is "<<a<<" now and b is "<<b<<endl;
				break;
			}
			case 2:
			{
				cout<<"You have selected MULTIPLICATION LOOP task\n";
				int n = fGetIO_Int("\tn = ");
				double res = 1.0;
				while (n > 0)
				{
					res *= (1.0+1/pow(n,0.25));
					n++;
				}
				break;
			}
			case 3:
			{
				cout<<"You have selected SUM LOOP task\n";
				int n = fGetIO_Int("\tn = ");
				double res = 0;
				while (n > 0)
				{
					double variant = n%3 ? 3 : n-3;
					res += pow((n/variant), 2);
					n++;
				}
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
				int m = fGetIO_Int("\tm = "), n = fGetIO_Int("\tn = "), k = fGetIO_Int("\tk = "), l = fGetIO_Int("\tl = ");
				if (fChessBoardColor(m,n,k,l))
					cout<<"\tselected chess board cells are of the same color\n";
				else
					cout<<"\tselected chess board cells differ by color\n";
				break;
			}
			case 6:
			{
				cout<<"You have selected NEIGHBOURS task\n";
				cout<<"\tplease, type needed numbers splited by 'enter'. The array is terminated by '0'\n\t";
				int diff_sign_qtt = 0;
				int cur_sign = 0;
				int tmp = 1;
				int tmp_p = 0;
				while (tmp)
				{
					tmp = fGetIO_Int("\t");
					if (tmp)
					{
						diff_sign_qtt += !(cur_sign+tmp/tmp);
						cur_sign = abs(tmp)/tmp;
					}
				}
				cout<<"\tthere where "<<diff_sign_qtt<<" neighbours with different signs\n";
				break;
			}
			case 7:
			{
				cout<<"You have selected ALPHA AND NUMERIC SYMBOLS COUNTER task\n";
				cout<<"\tplease, type needed symbols sequence terminated with '$' and press 'enter'\n\t";
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
				cout<<"You have selected TRIPPLE CONDITION BY DELIMETER task\n";
				int i = fGetIO_Int("\ti = "),k = fGetIO_Int("\tk = ");
				cout<<"\tz is "<<fTCByDelimeter(i, k)<<endl;
				break;
			}
			case 9:
			{
				cout<<"You have selected CHESS BOARDS COLORS task\n";
				int m = fGetIO_Int("\tm = "), n = fGetIO_Int("\tn = "), k = fGetIO_Int("\tk = "), l = fGetIO_Int("\tl = ");

				int dx = abs(m-k);
				int dy = abs(n-l);

				if (dx == dy || !dx || !dy)
					cout<<"\tbeats";
				else
					cout<<"\tno threats";
				break;
			}
			case 10:
			{
				cout<<"You have selected BELONGS TO PREDEFINED RANGE task\n";
				double x;
				cout<<"\tx = "; cin>>x;
				cout<<"S = "<<((x >= 2.0 && x <= 5.0) || (x >= -1.0 && x <= 1))<<endl;
				break;
			}
			case 11:
			{
				cout<<"You have selected NUMBER DELIMETERS task\n";
				int n = fGetIO_Int("\tthe number is: ");
				int d = 1;
				int range = n/2+1;
				while (d < range)
				{
					if (!(n%d))
						cout<<d<<endl;
					d++;
				}
				break;
			}
			case 12:
			{
				cout<<"You have selected CALCULATOR task\n";
				char operation = 1;
				double number1 = 1;
				double number2 = 1;

				while (operation)
				{
					cout<<"\twhat you want to do?\n\t\t+ - add two numbers,\n\t\t- - differ two numbers,\n\t\t* - multiply two numbers,\n\t\t/ - divide two numbers,\n\t\tany other sign for exit.\n";
					cout<<"\t\t:";
					cin>>operation;
					switch (operation)
					{
					case '+':
						cout<<"\t\tenter first number: ";
						cin>>number1;
						cout<<"\t\tenter second number: ";
						cin>>number2;
						cout<<"\t\tresult is "<<number1+number2<<endl;
						break;
					case '-':
						cout<<"\t\tenter first number: ";
						cin>>number1;
						cout<<"\t\tenter second number: ";
						cin>>number2;
						cout<<"\t\tresult is "<<number1-number2<<endl;
						break;
					case '*':
						cout<<"\t\tenter first number: ";
						cin>>number1;
						cout<<"\t\tenter second number: ";
						cin>>number2;
						cout<<"\t\tresult is "<<number1*number2<<endl;
						break;
					case '/':
						cout<<"\t\tenter first number: ";
						cin>>number1;
						cout<<"\t\tenter second number: ";
						cin>>number2;
						cout<<"\t\tresult is "<<number1/number2<<endl;
						break;
					default:
						operation = 0;
						break;
					}
				}
				break;
			}
			case 13:
			{
				cout<<"You have selected MATH FUNCTION task\n";
				double x;
				cout<<"\tx = ";
				cin>>x;
				cout<<(x <= 0.5 ? 1 : sin((x-1)*M_PI_2))<<endl;
				break;
			}
			case 14:
			{
				cout<<"You have selected SQRT task\n";
				double x,y;
				cout<<"\tx = "; cin>>x;
				y = x;
				int i = 0;
				while (true)
				{
					double tmp = 0.5*(y+x/y);
					if (y-tmp < 0.00001)
						break;
					y = tmp;
					i++;
				}
				cout<<"\t"<<(char)251<<x<<" = "<<y<<endl;
				break;
			}
			case 15:
			{
				cout<<"You have selected SUM OF DIGITS task\n";
				int n,s=0;
				cout<<"\tN = "; cin>>n;
				while (n)
				{
					s += n%10;
					n /= 10;
				}
				cout<<"\tSum is "<<s<<endl;
				break;
			}
			default:
				cout<<"Undefined task number. Input task within the range: 1-15.\n";
				break;
		}
	}
	return 0;
}
