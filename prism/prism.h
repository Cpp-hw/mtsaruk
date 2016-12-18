#pragma once


#define PRISM_BASEMENT_SQUARE		0
#define PRISM_BASEMENT_FACES_QTT	0
#define PRISM_BASEMENT_EDGES_QTT	0
#define PRISM_BASEMENT_RADIUS		0
#define PRISM_BASEMENT_EDGES_LENGTH	0

class CPrism
{
public:
	double fGet_Volume();
	double fGet_Square(int square_definition = PRISM_BASEMENT_SQUARE); // total, bottom face square, top face square, side face square, side faces square
	double fGet_Height();
	double fGet_FacesQuantity(int faces_definition = PRISM_BASEMENT_FACES_QTT); // total faces quantity, basement faces quantity, edge faces qunatity
	double fGet_EdgesQuantity(int edges_definition = PRISM_BASEMENT_EDGES_QTT); // total edges quantity, basement edges quantity, side edges quantity
	double fGet_Radius(int radius_definition = PRISM_BASEMENT_RADIUS); // insite base radius, outsite basement radius, inline sphere radius, outline sphere radius
	double fGet_Length(int length_definition = PRISM_BASEMENT_EDGES_LENGTH); // edge length, base perimeter length
	
	void fSet_Height(double height);
	void fSet_EdgesQuantity(int edges_quanity);
	void fSet_Radius(double R);

	void fShow();
	void fChange();
private:
	double R;				// outline basement radius
	int edges_quanity;	// basement edges quantity
	double height;			
public:
	CPrism(void);
	~CPrism(void);
};

