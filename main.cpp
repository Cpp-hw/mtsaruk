/*
* main.cpp
*
*  Created on: Dec 19, 2016
*      Author: softserve
*/

// Windows Header Files:
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
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
void fDrawTriangle(int ** triangle, int depth)
{
	int i = 0;
	while (i < depth)
	{
		int j = 0;
		while (j <= (depth-i))
		{
			cout<<" ";
			j++;
		}

		j = 0;
		while (j <= i)
		{
			cout<<" "<<triangle[i][j];
			j++;
		}
		cout<<endl;
		i++;
	}
}
void fDrawSudoku(int ** matrix)
{
	int i = 0, j = 0;
	while (i < 9)
	{
		if (!(i%3))
		{
			j = 0;
			while (j < 22)
			{
				if (!(j%7))
					cout<<"+";
				else
					cout<<"-";
				j++;
			}
			cout<<endl;
		}
		j = 0;
		while (j < 9)
		{
			if (!(j%3))
				cout<<(char)179;
			cout<<" ";
			if (matrix[i][j])
				cout<<matrix[i][j];
			else
				cout<<" ";
			j++;
		}
		cout<<(char)179<<endl;
		i++;
	}
	j = 0;
	while (j < 22)
	{
		if (!(j%7))
			cout<<"+";
		else
			cout<<"-";
		j++;
	}
	cout<<endl;
}

// FAST SUDOKU VALIDATION FUNCTION
// this validation function may treat some invalid sudocus as valid ones
// advantages:
//		+ chance of fail is very low
//		+ it is very fast way of validation
//		+ lower memmory usage
// so it can be used when great number of validations is applied to cast away most of the invalid sudokus
// all "valid" sudokus then go through careful validation
int fIsSudokuValid_Fast(int ** matrix)
{
	// try rows
	int row = 0;
	int sum = 405;
	while (row < 9)
	{
		int cell = 0;
		while (cell < 9)
		{
			sum -= matrix[row][cell];
			cell++;
		}
		row++;
	}

	return !sum;
}
// CAREFUL SUDOKU VALIDATION FUNCTION
int fIsSudokuInvalid(int ** matrix)
{
	int * unique_cells = new int[10]; // contains number of times each unique number was used
	
	int cell = 0;
	// try rows
	int row = 0;
	while (row < 9)
	{
		memset(unique_cells,0,sizeof(int)*10); // clear unique cell

		cell = 0;
		while (cell < 9)
		{
			int the_cell = matrix[row][cell];
			if (the_cell) // to skip blank (unfilled, undefinned) cells
			{
				if (unique_cells[the_cell])
					return (row+1)*100+cell+1;
				unique_cells[the_cell]++;
			}
			cell++;
		}
		row++;
	}

	// try columns
	int coll = 0;
	while (coll < 9)
	{
		memset(unique_cells,0,sizeof(int)*10); // clear unique cell

		cell = 0;
		while (cell < 9)
		{
			int the_cell = matrix[cell][coll];
			if (the_cell) // to skip blank (unfilled, undefinned) cells
			{
				if (unique_cells[the_cell])
					return (cell+1)*100+coll+1;
				unique_cells[the_cell]++;
			}
			cell++;
		}
		coll++;
	}

	row = 0; // now, it is section row
	coll = 0; // now, it is section coll
	while (row < 3)
	{
		while (coll < 3)
		{
			memset(unique_cells,0,sizeof(int)*10); // clear unique cell

			cell = 0;
			while (cell < 9)
			{
				int the_cell = matrix[row*3+cell/3][coll*3+cell%3];
				if (the_cell) // to skip blank (unfilled, undefinned) cells
				{
					if (unique_cells[the_cell])
						return (row+1)*10+coll+1;
					unique_cells[the_cell]++;
				}
				cell++;
			}
			coll++;
		}
		row++;
	}
	return 0;
}
void fRandomizeSudoku(int ** matrix)
{
	int i = 0;
	while (i < 9)
	{
		int j = 0;
		while (j < 9)
		{
			matrix[i][j] = rand()%50-40;
			matrix[i][j] = matrix[i][j] < 0 ? 0 : matrix[i][j];
			j++;
		}
		i++;
	}
}

int fGetCellNextVariant(int ** matrix, int row, int col, int * used_variants, int current_variant = 1)
{
	memset(used_variants, 0, sizeof(int)*10); // reset variants
	used_variants[0] = 1; // to secure that 0 is never used as variant for sudoku solving

	// define by row
	int cell = 0;
	while (cell < 9)
	{
		int the_cell = matrix[row][cell];
		if (the_cell) // to skip blank (unfilled, undefinned) cells
			used_variants[the_cell]++;
		cell++;
	}

	// define by column
	cell = 0;
	while (cell < 9)
	{
		int the_cell = matrix[cell][col];
		if (the_cell) // to skip blank (unfilled, undefinned) cells
			used_variants[the_cell]++;
		cell++;
	}


	
	row /= 3; // now, it is section row. It is important to devide by 3 without remaining.
	col /= 3; // now, it is section col. It is important to devide by 3 without remaining.
	cell = 0;
	while (cell < 9)
	{
		int the_cell = matrix[row*3+cell/3][col*3+cell%3];
		if (the_cell) // to skip blank (unfilled, undefinned) cells
			used_variants[the_cell]++;
		cell++;
	}

	while (++current_variant < 10)
	{
		if (!used_variants[current_variant])
			return current_variant;
	}
	return 0;
}

int fGetFirstUnset(int ** matrix, int &row, int &col)
{
	int i = row*9+col;
	while (i < 81)
	{
		if (!matrix[i/9][i%9])
		{
			row = i/9;
			col = i%9;
			return 1;
		}
		i++;
	}
	return 0;
}
int fGetPrevUnset(int ** matrix, int &row, int &col)
{
	int i = row*9+col;
	while (i--)
	{
		if (!matrix[i/9][i%9])
		{
			row = i/9;
			col = i%9;
			return 1;
		}
	}
	return -1;
}
int fSolveSudoku(int ** matrix, int & iteration)
{
	// initialization
	int * used_variants = new int[10]; // contains number of times each unique number was used
	int ** res_matrix = new int*[9];
	int ** variant_number = new int*[9];
	int row = -1;
	while (++row < 9)
	{
		res_matrix[row] = new int[9];
		variant_number[row] = new int[9];
		memcpy(res_matrix[row], matrix[row], sizeof(int)*9);
		memset(variant_number[row], 0, sizeof(int)*9); // clear unique cell
	}

	// processing start
	int cur_row = 0;
	int cur_col = 0;
	int res = fGetFirstUnset(res_matrix,cur_row,cur_col);
	int itr = 0;
	while (res > 0) // main loop that moves along sudoku matrix back and forth serching for proper solution
	{
		int new_var = fGetCellNextVariant(res_matrix, cur_row, cur_col, used_variants, variant_number[cur_row][cur_col]);
		variant_number[cur_row][cur_col] = new_var;
		res_matrix[cur_row][cur_col] = new_var;
		if ( new_var ) // there are some available variants
			res = fGetFirstUnset(res_matrix,cur_row,cur_col);
		else // roll back
			res = fGetPrevUnset(matrix,cur_row,cur_col);

		itr++;
		if (!(itr%1000))
		{
			//system("cls");
			cout<<"iteration: "<<itr<<".\nCurrent possition ["<<cur_row+1<<":"<<cur_col+1<<"]\n         |\n         |\n         v\n"<<endl;
			fDrawSudoku(res_matrix);
		}
	}


	// copy result
	row = -1;
	while (++row < 9)
		memcpy(matrix[row], res_matrix[row], sizeof(int)*9);

	iteration = itr;
	return res+1;
}


int fCompareArrays(int * arr_1, int * arr_2, int elems_to_cmp)
{
	int i = -1;
	while (++i < elems_to_cmp)
	{
		int res = arr_1[i] - arr_2[i];
		if (res)
			return res;
	}
	return 0;
}
void fPatternNormalization(int * normalized, string src, int offset = 0, int p_length = -1 )
{
	if (p_length == -1)
		p_length = src.length() - offset;

	normalized[0] = 0;

	int i = 0;
	while (++i < p_length)
	{
		normalized[i] = i;
		int j = -1;
		while (++j < i)
		{
			if (src[i+offset] == src[j+offset])
				normalized[i] = normalized[j];
		}
	}
}
int fFitsPattern(int * normalized_pattern, int p_length, string str, int offset)
{
	int * tmp_normalized =		new int[p_length];

	int s_l = str.length() - p_length + 1;
	int i = offset-1;
	while (++i < s_l)
	{
		fPatternNormalization(tmp_normalized, str, i, p_length );
		int res = fCompareArrays(normalized_pattern, tmp_normalized, p_length);
		if (!res)
			return i;
	}
	return -1;
}

int main(int argc, char ** argv)
{
	cout<<"Welcome to PSET2!\n";
	int user_command = 1;
	while (user_command)
	{
		cout<<"\nInput task number you want to check (0 for exit):\n";
		cout<<" 1 - PASCAL'S TRIANGLE\n";
		cout<<" 2 - TRIANGLE ALGORYTHM\n";
		cout<<" 3 - VALIDATE PALINDROME\n";
		cout<<" 4 - VALIDATE SUDOKU\n";
		cout<<" 5 - WORD PATTERN\n";
		cout<<" 6 - ZIGZAG CONVERSION\n";
		user_command = fGetIO_Int();
		switch (user_command)
		{
			case 0:
				cout<<"Thank you for your attention. Bye.\n";
				return 0;
			case 1:
			{
				cout<<"You have selected PASCAL'S TRIANGLE task\n";

				int ** triangle;
				int depth = fGetIO_Int("\tplease, specify triangle depth (number of rows): ");
				if (!depth)
					break;

				triangle = new int* [depth];

				// I have chosen direct approach, as it is good for triangle complete generation thus it is bad for generation exact element at axact row.
				// to generate element of the triangle without generation the whole triangle, we can use math equisitions with factorials
				int i = -1;
				while (++i < depth)
				{
					int j = -1, range = (depth-i-1)*3-1;
					while (++j <= (depth-i-1)*3-1) // formated output
					{
						cout<<" ";
					}

					triangle[i] = new int [i+1];
					triangle[i][0] = 1;
					cout<<"    1 ";
					j = 0;
					while (++j < i)
					{
						triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
						printf("%5d ", triangle[i][j]);
					}
					if (i)
					{
						triangle[i][j] = 1;
						cout<<"    1 ";
					}
					cout<<endl;
				}
				i = 0;
				while (i < depth)
				{
					delete [] triangle[i];
					i++;
				}
				delete [] triangle;

				break;
			}
			case 2:
			{
				cout<<"You have selected TRIANGLE ALGORYTHM task\n";

				int ** triangle;
				int ** triangle_sums;	// for performance purposes, this approach will secure n^2 execution time, otherwise execution is 2^n (much slower), where 'n' is number of triangle rows
										// i.e., for triangle with 32 rows, this approach will use about 500 iterations while brutforce approach will need up to about 2 000 000 000
				int depth = fGetIO_Int("\tplease, specify triangle depth (number of rows): ");

				// generating triangle with numbers//
				triangle = new int* [depth];
				triangle_sums = new int* [depth];
				int i = -1;
				while (++i < depth)
				{
					triangle[i] = new int [i+1];
					triangle_sums[i] = new int [i+1];
					int j = -1;
					while (++j <= i)
						triangle[i][j] = triangle_sums[i][j] = rand()%10;
				}

				fDrawTriangle(triangle, depth);

				// looking for shortest way //
				i = depth-1;
				while (--i >= 0) // instead of 'while (i)' in case of negative 'i'
				{
					int j = -1;
					while (++j <= i)
						triangle_sums[i][j] += triangle_sums[i+1][j] < triangle_sums[i+1][j+1] ? triangle_sums[i+1][j] : triangle_sums[i+1][j+1];
				}
				
				// display results //
				if (depth)
					cout<<"\ttotal path length is "<<triangle_sums[0][0];

				cout<<"\tthe path is: "<<triangle[0][0];
				i = 0;
				int j = 0;
				while (++i < depth)
				{
					j += (triangle_sums[i][j] > triangle_sums[i][j+1]);
					cout<<", "<<triangle[i][j];
				}
				
				// clear memory //
				i = 0;
				while (i < depth)
				{
					delete [] triangle[i];
					delete [] triangle_sums[i];
					i++;
				}
				delete [] triangle;
				delete [] triangle_sums;

				cout<<endl;
				break;
			}
			case 3:
			{
				cout<<"You have selected VALIDATE PALINDROME task\n";

				cout<<"\tplease, type needed symbols sequence and press 'enter'\n\t";
				string str = fGetIO_String("\tplease, type needed symbols sequence and press 'enter'\n\t");

				bool palindrome = true;
				int i = -1;
				int l = str.length()-1;
				int r = (l+1)/2; // additional variable to avoid excessive (repeated) math operation on each loop iteration 
				while ( ++i < r )
				{
					if (str[i] != str[l-i])
					{
						cout<<"\tinputed text is NOT palindrome\n";
						palindrome = false;
						break;
					}
				}
				if (palindrome)
					cout<<"\tinputed text is palindrome\n";
				break;
			}
			case 4:
			{
				cout<<"You have selected VALIDATE SUDOKU task\n";

				// create matrix //
				int ** matrix = new int* [9];
				srand(time(NULL));
				int i = -1;
				while (++i < 9)
				{
					matrix[i] = new int [9];
				}

				// randomize sudoku until it is valide
				fRandomizeSudoku(matrix);
				int res = fIsSudokuInvalid(matrix);
				while (res)
				{
					system("cls");
					cout<<"Random sudoku generation:"<<endl;
					if (res >= 100)
						cout<<"invalid sudoku (row: "<<res/100<<"; cell "<<res%100<<")"<<endl;
					else if (res >= 10)
						cout<<"invalid sudoku (section: "<<res/10<<":"<<res%10<<")"<<endl;
					fDrawSudoku(matrix);
					fRandomizeSudoku(matrix);
					res = fIsSudokuInvalid(matrix);
					Sleep(300);
				}
				
				// draw chosen sudike
				system("cls");
				cout<<"This sudoku may be valid:"<<endl;
				fDrawSudoku(matrix);

				// solve sudoku
				int iterations = 0;
				res = fSolveSudoku(matrix, iterations);
				if (res)
					cout<<"Sudoku is valid and filled.\n         |\n         |\nsolved in "<<iterations+1<<" iterations\n         |\n         v\n";
				else
					cout<<"Sudoku is invalid.\n         |\n         |\nstopped at below result\nafter "<<iterations+1<<" iterations\n         |\n         v";
				fDrawSudoku(matrix);
				break;
			}
			case 5:
			{
				cout<<"You have selected WORD PATTERN task\n";

				// initializations, validations
				string str = fGetIO_String("\toriginal string: "), pattern = fGetIO_String("\tpattern: ");
				int s_l = str.length(), p_l = pattern.length();
				if (!s_l || !p_l)
				{
					cout<<"Original string and word pattern cannot be empty"<<endl;
					break;
				}

				// normalization // it is needed to make 'abbc', 'cbba' or 'bffa' to be the same pattern
				int * normalized_pattern = new int[p_l];
				fPatternNormalization(normalized_pattern, pattern); // it is needed to make 'abbc' and 'bffa' be the same pattern

				int pos = -1;
				do // find all pattern matches
				{
					pos = fFitsPattern(normalized_pattern, p_l, str, pos+1);
					if (pos != -1)
					{
						cout<<"\n\t\tPatternt was found at position "<<pos+1<<".";
						int i = pos, r = s_l - p_l;
						while (++i < r)
						{
							if (!str.compare(i,p_l, str, pos, p_l))
								cout<<" "<<i+1;
						}
					}
				} while (pos != -1);
				cout<<"\n\tSearch completed, the results are above (if any!)"<<endl;

				delete [] normalized_pattern;
				break;
			}
			case 6:
			{
				cout<<"You have selected ZIGZAG CONVERSION task\n";

				string str = fGetIO_String("\tplease, type needed symbols sequence and press 'enter':\n");
				int depth = fGetIO_Int("\tthank you. Please, enter needed zigzag depth (width) now\n\t");
				
				cout<<"\tconverted string is:\"";

				int i = 0, l = str.length(), s = depth*2-2;
				while ( i < depth )
				{
					int j = i, sb = s-2*i, sm = 2*i; // additional variable in performance purpose, i.e., no need in repeated math operation in below loop
					while (j < l)
					{
						if (sb)
							cout<<str[j];
						j += sb;

						if (sm && j < l)
							cout<<str[j];
						j += sm;
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