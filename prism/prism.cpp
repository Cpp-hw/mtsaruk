#include "stdafx.h"
#include "prism.h"


CPrism::CPrism(void)
{
	R = 1.0;				// outline basement radius
	edges_quanity = 3;
	height = 1.0;
	cout<<"Default prism is created: radius is 1.0, basement edges quantity is 6, height is 1.0\n\n";
}


CPrism::~CPrism(void)
{
}


void CPrism::fShow(void)
{
	char user_command = 1;
	while (user_command)
	{
		cout<<"\n";
		cout<<"\tDISPLAY:\n";
		cout<<"\th - height\n";
		cout<<"\tv - volume\n";
		cout<<"\tf - faces quantity\n";
		cout<<"\ts - square of basement\n";
		cout<<"\tl - length of prism edge\n";
		cout<<"\t0, q, b - go back to main menu\n";
		cout<<"\t>";
		cin>>user_command;
		switch (user_command)
		{
			case 'h':
				cout<<"\t\t"<<fGet_Height()<<endl;
				break;
			case 'v':
				cout<<"\t\t"<<fGet_Volume()<<endl;
				break;
			case 'f':
				cout<<"\t\t"<<fGet_FacesQuantity()<<endl;
				break;
			case 's':
				cout<<"\t\t"<<fGet_Square()<<endl;
				break;
			case 'l':
				cout<<"\t\t"<<fGet_Length()<<endl;
				break;

			case 'q':
			case 'b':
			case '0':
			case 0:
				return;
			default:
				cout<<"\t\tUndefined command. Try again.\n";
				break;
		}
	}
}


void CPrism::fChange(void)
{
	char user_command = 1;
	while (user_command)
	{
		cout<<"\n";
		cout<<"\tCHANGE:\n";
		cout<<"\th - height\n";
		cout<<"\tf - faces quantity\n";
		cout<<"\tr - outline basement radius\n";
		cout<<"\t0, q, b - go back to main menu\n";
		cout<<"\t>";
		cin>>user_command;
		switch (user_command)
		{
			case 'h':
			{
				double new_height = 0.0;
				cout<<"\t\tspecify parameter>";
				cin>>new_height; // TODO: use user input safety method intead of cin
				fSet_Height(new_height);
				break;
			}
			case 'f':
			{
				int new_edges_quanity = 0;
				cout<<"\t\tspecify parameter>";
				cin>>new_edges_quanity; // TODO: use user input safety method intead of cin
				if (new_edges_quanity < 3)
				{
					cout<<"\t\tbasement edges quantity must be 3 or greater\n";
				}
				fSet_EdgesQuantity(new_edges_quanity);
				break;
			}
			case 'r':
			{
				double new_R = 0.0;
				cout<<"\t\tspecify parameter>";
				cin>>new_R; // TODO: use user input safety method intead of cin
				fSet_Radius(new_R);
				break;
			}

			case 'q':
			case 'b':
			case '0':
			case 0:
				return;
			default:
				cout<<"\tUndefined command. Try again.";
				break;
		}
	}
}

double CPrism::fGet_Height(void)
{
	return height;
}

double CPrism::fGet_Square(int square_definition)
{
	switch (square_definition)
	{
		case PRISM_BASEMENT_SQUARE:
			return edges_quanity*R*R*sin(M_2_PI/edges_quanity)/2;
		default:
			cout<<"fGet_Square("<<square_definition<<"): undefined parameter error;\n";
			break;
	}
	return 0.0;
}

double CPrism::fGet_Volume(void)
{
	return fGet_Height()*fGet_Square(PRISM_BASEMENT_SQUARE);
}

double CPrism::fGet_FacesQuantity(int faces_definition)
{
	switch (faces_definition)
	{
		case PRISM_BASEMENT_EDGES_QTT: // basement square
			return edges_quanity;
		default:
			cout<<"fGet_FacesQuantity("<<faces_definition<<"): undefined parameter error;\n";
			break;
	}
	return 0.0;
}

double CPrism::fGet_Length(int length_definition)
{
	switch (length_definition)
	{
		case PRISM_BASEMENT_EDGES_LENGTH: // basement square
			return 2*R*sin(M_PI/edges_quanity);
		default:
			cout<<"fGet_Length("<<length_definition<<"): undefined parameter error;\n";
			break;
	}
	return 0.0;
}

void CPrism::fSet_Height(double height)
{
	this->height = height;
}
void CPrism::fSet_EdgesQuantity(int edges_quanity)
{
	this->edges_quanity = edges_quanity;
}
void CPrism::fSet_Radius(double R)
{
	this->R = R;
}