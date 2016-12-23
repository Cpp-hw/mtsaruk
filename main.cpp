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

void fDrawTriangle(int ** triangle, int depth)
{
	int i = 0;
	while (i < depth)
	{
		int j = 0;


		while (j <= depth-i)
		{
			cout<<" ";
			j++;
		}

		j = 0;
		while (j <= i)
		{
			cout<<triangle[i][j]<<" ";
			j++;
		}
		cout<<endl;
		i++;
	}
}

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
				int ** triangle_sums; // for performance purposes, this approach will secure n^2 execution time, otherwise execution is 2^n (much slower), where 'n' is number of triangle rows
				int depth;

				/////////////////////////////////////////////////
				// specifying and filling triangle with numbers//
				cout<<"\tplease, specify triangle depth (number of rows) and press 'enter'\n\t";
				cin >> depth;
				triangle = new int* [depth];
				triangle_sums = new int* [depth];
				cout<<"\twould you like to fill the triangle with random numbers? y - for yes, any other - for no\n\t";
				char user_choice;
				cout<<"\t"; cin >> user_choice;
				if (user_choice == 'y')
					srand(time(NULL));
				int i = 0;
				while (i < depth)
				{
					triangle[i] = new int [i+1];
					triangle_sums[i] = new int [i+1];

					if (user_choice != 'y')
						cout<<"\t\tplease, put row "<<i+1<<" numbers\n";
					int j = 0;
					while (j <= i)
					{
						if (user_choice != 'y')
						{
							cout<<"\t\t\t"<<j+1<<": ";
							cin>>triangle[i][j];
						}
						else
							triangle[i][j] = rand()%10;
						triangle_sums[i][j] = triangle[i][j];
						j++;
					}
					i++;
				}
				// specifying and filling triangle with numbers//
				/////////////////////////////////////////////////

				fDrawTriangle(triangle, depth);


				/////////////////////////////////////
				// searching for shortest way down //
				i = depth-2;
				while (i >= 0) // instead of 'while (i)' in case of negative 'i'
				{
					int j = 0;
					while (j <= i)
					{
						triangle_sums[i][j] += triangle_sums[i+1][j] < triangle_sums[i+1][j+1] ? triangle_sums[i+1][j] : triangle_sums[i+1][j+1];
						j++;
					}
					i--;
				}
				// searching for shortest way down //
				/////////////////////////////////////

				/////////////////////
				// display results //
				if (depth)
					cout<<"\ttotal path length is "<<triangle_sums[0][0];

				cout<<"\tthe path is: "<<triangle[0][0];
				i = 1;
				int j = 0;
				while (i < depth)
				{
					if (triangle_sums[i][j] > triangle_sums[i][j+1])
						j++;
					cout<<", "<<triangle[i][j];
					i++;
				}
				// display results //
				/////////////////////



				//////////////////
				// clear memory //
				int i = 0;
				while (i < depth)
				{
					delete [] triangle[i];
					delete [] triangle_sums[i];
					i++;
				}
				delete [] triangle;
				delete [] triangle_sums;
				// clear memory //
				//////////////////

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

				string str, pattern;
				int s_l = str.length(), p_l = pattern.length();

				cout<<"\toriginal string:\n\t";	cin>>str;
				cout<<"\tpattern:\n\t";			cin>>pattern;

				int * normalized_pattern =	new int[p_l];
				int * tmp_pattern =			new int[p_l];

				///////////////////////////
				// pattern normalization //
				int i = 0;
				// pattern normalization //
				///////////////////////////

				delete [] normalized_pattern;
				delete [] tmp_pattern;
				break;
			}
			case 6:
			{
				string str;
				int depth;
				cout<<"You have selected ZIGZAG CONVERSION task\n";
				cout<<"\tplease, type needed symbols sequence and press 'enter'\n\t";	cin>>str;
				cout<<"\tthank you. Please, enter needed zigzag depth (width) now\n\t";	cin>>depth;
				cout<<"\tconverted string is:\"";

				int i = 0;
				int l = str.length();
				int s = depth*2-2;
				while ( i < depth )
				{
					int j = i;
					int sb = s-2*i; // additional variable in performance purpose, i.e., no need in repeated math operation in below loop
					int sm = 2*i; // additional variable in performance purpose, i.e., no need in repeated math operation in below loop
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
