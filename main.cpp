/*
 * main.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: softserve
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;


int main(int argc, char ** argv)
{
	cout<<"Welcome to PSET2!\n";
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
				cout<<"You have selected PASCAL'S TRIANGLE task\n";
				break;
			}
			case 2:
			{
				cout<<"You have selected TRIANGLE ALGORYTHM task\n";

				int ** triangle;

				/////////////////////////
				// user fills triangle //
				cout<<"\tplease, specify triangle depth (number of rows) and press 'enter'\n\t";
				int depth;
				cin >> depth;
				triangle = new int* [depth];
				int i = 0;
				while (i < depth)
				{
					cout<<"\t\tplease, put row "<<i+1<<" numbers\n";
					triangle[i] = new int [i+1];
					int j = 0;
					while (j <= i)
					{
						cout<<"\t\t\t"<<j+1<<": ";
						cin>>triangle[i][j];
						j++;
					}
					i++;
				}
				// user fills triangle //
				/////////////////////////
				break;
			}
			case 3:
			{
				cout<<"You have selected VALIDATE PALINDROME task\n";
				cout<<"\tplease, type needed symbols sequence and press 'enter'\n\t";
				string str;
				cin>>str;

				bool palindrome = true;
				int i = 0;
				int l = str.length()-1;
				int r = (l+1)/2;
				while ( i < r )
				{
					if (str[i] != str[l-i])
					{
						cout<<"\tinputed text is NOT palindrome\n";
						palindrome = false;
						break;
					}
					i++;
				}
				if (palindrome)
					cout<<"\tinputed text is palindrome\n";
				break;
			}
			case 4:
			{
				cout<<"You have selected VALIDATE SUDOKU task\n";
				break;
			}
			case 5:
			{
				cout<<"You have selected WORD PATTERN task\n";
				break;
			}
			case 6:
			{
				string str;
				unsigned int depth;
				cout<<"You have selected ZIGZAG CONVERSION task\n";
				cout<<"\tplease, type needed symbols sequence and press 'enter'\n\t";
				cin>>str;
				cout<<"\tthank you. Please, enter needed zigzag depth (width) now\n\t";
				cin>>depth;
				cout<<"\tconverted string is:\"";

				int i = 0;
				int l = str.length();
				int s = depth*2-2;
				while ( i < depth )
				{
					int j = i;
					int sb = s-2*i;
					int sm = 2*i;
					while (j < l)
					{
						if (sb)
						{
							cout<<str[j];
							j += sb;
						}

						if (sm && j < l)
						{
							cout<<str[j];
							j += sm;
						}
					}
					i++;
				}
				cout<<"\""<<endl;
				break;
			}
			default:
				cout<<"Undefined task number. Input task within the range: 1-6.\n";
				break;
		}
	}
	return 0;
}
