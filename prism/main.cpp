#include "stdafx.h"
#include "prism.h"


void fShow_WelcomeScreen();
void fShow_UserMenu();


int main(int argc, char* argv[])
{
	fShow_WelcomeScreen();

	CPrism * pPrism = new CPrism();

	char user_command = 1;
	while (user_command)
	{
		fShow_UserMenu();
		cin>>user_command;
		switch (user_command)
		{
			case '1':
				pPrism->fChange();
				break;
			case '2':
				pPrism->fShow();
				break;
			case '3':
				system("cls");
				break;
			case 'q':
			case 'e':
			case '0':
			case 0:
				return 0;
			default:
				break;
		}
	}
	
	cout<<"Bye\n";
	return 0;
}




void fShow_WelcomeScreen()
{
	system("cls");
	cout<<"Wellcome to prism generator.\n\n";
	cout<<" __ \n";
	cout<<"/  \\\n";
	cout<<"\\__/\n";
	cout<<"\\__/\n\n";
}
void fShow_UserMenu()
{
	cout<<"\nUse below commands for prism interaction:\n";
	cout<<"1 - set parameter\n";
	cout<<"2 - display parameter\n";
	cout<<"3 - clear screen\n";
	cout<<"0, q, e - quit\n";
	cout<<">";
}