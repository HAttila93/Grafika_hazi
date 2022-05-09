//*************************
//  Szamitogepi grafika   *
//  Felevi beadando       *
//  Keszitette:           *
//  Hegedus Attila Laszlo *
//  D2OVJ9                *
//*************************




#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

//***********************
//A koordinatak valtozoi*
//***********************

double hx1,hx2,hx3,hy1,hy2,hy3;
double haromszog_mx[3][3] ={
    {0,0,0},
    {0,0,0},
    {1,1,1}};

int choice = 0, csucsok = 3;

int eltoloX, eltoloY;
double nagyitoX, nagyitoY;
double szog, szog_radian;
char tukrozo_tengely;

//***********************
//Matrix szorzo fuggveny*
//***********************

void mx_szorzas(double transzformacio_mx[3][3], double koordinata_mx[3][3], double eredmeny[3][3], int csucs)
{
    for(int i=0; i<csucs; i++)
    {
        for(int j=0; j<csucs; j++)
        {
            eredmeny[i][j] = 0;
            for(int k=0; k<csucs; k++)
            {
                eredmeny[i][j] += transzformacio_mx[i][k] * koordinata_mx[k][j];
            }
        }
    }
}

//**********************************
//A haromszoget megrajzolo fuggveny*
//**********************************

void haromszog()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2d(haromszog_mx[0][0], haromszog_mx[1][0]);
	glVertex2d(haromszog_mx[0][1], haromszog_mx[1][1]);
	glVertex2d(haromszog_mx[0][2], haromszog_mx[1][2]);
	glEnd();
}

//*********************************
//Az eltolast vegrehajto fuggveny *
//*********************************
//A csucsok eredeti koordinatainak*
//matrixat az eltolas matrixaval  *
//szorozzuk                       *
//*********************************

void haromszog_eltolt(int x, int y)
{

	double eltolo_mx[3][3] ={
    {1,0,x},
    {0,1,y},
    {0,0,1}};

    double eltolt_mx[3][3];

    mx_szorzas(eltolo_mx, haromszog_mx, eltolt_mx, csucsok);


	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
    glVertex2d(eltolt_mx[0][0], eltolt_mx[1][0]);
    glVertex2d(eltolt_mx[0][1], eltolt_mx[1][1]);
    glVertex2d(eltolt_mx[0][2], eltolt_mx[1][2]);

	glEnd();
}

//***********************************
//A nagyitast vegrehajto fuggveny   *
//***********************************
//A csucsok eredeti koordinatainak  *
//matrixat a nagyitas matrixaval    *
//szorozzuk.                        *
//***********************************

void haromszog_nagyitott(double x, double y)
{


    double nagyito_mx[3][3] ={
    {x,0,0},
    {0,y,0},
    {0,0,1}};


    double nagyitott_mx[3][3];
    mx_szorzas(nagyito_mx, haromszog_mx, nagyitott_mx, csucsok);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
    glVertex2d(nagyitott_mx[0][0], nagyitott_mx[1][0]);
    glVertex2d(nagyitott_mx[0][1], nagyitott_mx[1][1]);
    glVertex2d(nagyitott_mx[0][2], nagyitott_mx[1][2]);
	glEnd();
}

//***********************************
//Az elforgatast vegrehajto fuggveny*
//***********************************
//A csucsok eredeti koordinatait    *
//megszorozzuk a megadott szog      *
//radianban vett koszinusz és       *
//szinuszaval                       *
//***********************************

void haromszog_elforgatott(double szog_radian)
{
	double elforgato_mx[3][3] ={
    {cos(szog_radian),-sin(szog_radian),0},
    {sin(szog_radian),cos(szog_radian), 0},
    {0,               0,                1}};

    double elforgatott_mx[3][3];
    mx_szorzas(elforgato_mx, haromszog_mx, elforgatott_mx, csucsok);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
    glVertex2d(elforgatott_mx[0][0], elforgatott_mx[1][0]);
    glVertex2d(elforgatott_mx[0][1], elforgatott_mx[1][1]);
    glVertex2d(elforgatott_mx[0][2], elforgatott_mx[1][2]);
	glEnd();
}

//*********************************
//A tukrozest vegrehajto fuggveny *
//*********************************
//A csucsok eredeti koordinatainak*
//matrixat a tukrozes matrixaval  *
//szorozzuk.                       *
//*********************************

void haromszog_tukrozott(char tukrozo_tengely)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	double tukrozott_mx[3][3];

	if (tukrozo_tengely == 'x' || tukrozo_tengely == 'X')
	{

		double tukrozes_x_mx[3][3] ={
                                {1,0, 0},
                                {0,-1,0},
                                {0,0, 1}};

        mx_szorzas(tukrozes_x_mx, haromszog_mx, tukrozott_mx, csucsok);
        glVertex2d(tukrozott_mx[0][0], tukrozott_mx[1][0]);
        glVertex2d(tukrozott_mx[0][1], tukrozott_mx[1][1]);
        glVertex2d(tukrozott_mx[0][2], tukrozott_mx[1][2]);

	}
	else if (tukrozo_tengely == 'y' || tukrozo_tengely == 'Y')
	{
	    double tukrozes_y_mx[3][3] ={
                                {-1,0, 0},
                                {0, 1, 0},
                                {0, 0, 1}};

        mx_szorzas(tukrozes_y_mx, haromszog_mx, tukrozott_mx, csucsok);
        glVertex2d(tukrozott_mx[0][0], tukrozott_mx[1][0]);
        glVertex2d(tukrozott_mx[0][1], tukrozott_mx[1][1]);
        glVertex2d(tukrozott_mx[0][2], tukrozott_mx[1][2]);

	}
	glEnd();

}

//****************************
//Az OpenGL ablak beallitasai*
//****************************

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -240.0, 240.0);   //Igy meg lehet adni pixelekben a koordinatakat
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	if (choice == 1)
	{
		haromszog();
		haromszog_eltolt(eltoloX, eltoloY);

	}
	else if (choice == 2)
	{
		haromszog();
		haromszog_nagyitott(nagyitoX, nagyitoY);
	}
	else if (choice == 3)
	{
		haromszog();
		haromszog_elforgatott(szog_radian);
	}
	else if (choice == 4)
	{
		haromszog();
		haromszog_tukrozott(tukrozo_tengely);

	}


	glFlush();
}

int main(int argc, char** argv)
{
    //*********************
    //A menu megjelenitese*
    //*********************

	cout << "*********MENU********" << endl;

	cout << "1. Eltolas" << endl;
	cout << "2. Nagyitas/Kicsinyites/Skalazas" << endl;
	cout << "3. Forgatas" << endl;
	cout << "4. Tukrozes" << endl;
	cout << "5. Kilepes" << endl;

	cout << "*********************\n" << endl;

	cin >> choice;

	if (choice == 5) {
		return 0;       //Kilepes
	}

	//***********************
	//A koordinatak bekerese*
	//***********************

	cout << "\nHaromszog:\n" << endl;

    cout << "Adja meg a csucsok koordinatait: " << 1 << " : "; cin >> hx1 >> hy1;
    cout << "Adja meg a csucsok koordinatait: " << 2 << " : "; cin >> hx2 >> hy2;
    cout << "Adja meg a csucsok koordinatait: " << 3 << " : "; cin >> hx3 >> hy3;

    haromszog_mx[0][0] = hx1;
    haromszog_mx[0][1] = hx2;
    haromszog_mx[0][2] = hx3;
    haromszog_mx[1][0] = hy1;
    haromszog_mx[1][1] = hy2;
    haromszog_mx[1][2] = hy3;

    //*******************************************
	//If elagazas, funkciok valtozoinak bekerese*
	//*******************************************

	if (choice == 1)
	{
		cout << "Ajda meg az eltolas X es Y merteket: "; cin >> eltoloX >> eltoloY;
	}
	else if (choice == 2)
	{
		cout << "Adja meg a nagyitas X es Y merteket: "; cin >> nagyitoX >> nagyitoY;
	}
	else if (choice == 3)
	{
		cout << "Adja meg a forgatas szoget: "; cin >> szog;
		szog_radian = szog * 3.1416 / 180;
	}
	else if (choice == 4)
	{
		cout << "Adja meg a tukrozes tengelyet: "; cin >> tukrozo_tengely;
	}

    //************
	//Ablak setup*
	//************

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Sikbeli transzformaciok");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();


}
