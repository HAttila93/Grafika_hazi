#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

//***********************
//A koordinatak valtozoi*
//***********************

int pntX1, pntY1, choice = 0, csucsok = 3;
vector<int> pntX;
vector<int> pntY;
int eltoloX, eltoloY;
double nagyitoX, nagyitoY;
double szog, szog_radian;
char tukrozo_tengely;

double round(double d)
{
	return floor(d + 0.5);
}

//************************************
//A haromszogeket megrajzolo fuggveny*
//************************************

void haromszog()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < csucsok; i++)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}

//*********************************
//Az eltolast vegrehajto fuggveny *
//*********************************
//A csucsok eredeti koordinataihoz*
//hozzaadjuk az eltolas meretkeit *
//*********************************

void haromszog_eltolt(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < csucsok; i++)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

//***********************************
//A nagyitast vegrehajto fuggveny   *
//***********************************
//A csucsok eredeti koordinatait    *
//megszorozzuk a nagyitas mertekevel*
//***********************************

void haromszog_nagyitott(double x, double y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < csucsok; i++)
	{
		glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
	}
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
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < csucsok; i++)
	{
		glVertex2i(round((pntX[i] * cos(szog_radian)) - (pntY[i] * sin(szog_radian))), round((pntX[i] * sin(szog_radian)) + (pntY[i] * cos(szog_radian))));
	}
	glEnd();
}

//*********************************
//A tukrozest vegrehajto fuggveny *
//*********************************
//A csucsok eredeti koordinatait  *
//-1-el szorozzuk. Ha az X-tengely*
//menten tukrozunk az Y-vektort	  *
//,ha az Y-tengely menten, az X-et*
//*********************************

void haromszog_tukrozott(char tukrozo_tengely)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	if (tukrozo_tengely == 'x' || tukrozo_tengely == 'X')
	{
		for (int i = 0; i < csucsok; i++)
		{
			glVertex2i(round(pntX[i]), round(pntY[i] * -1));

		}
	}
	else if (tukrozo_tengely == 'y' || tukrozo_tengely == 'Y')
	{
		for (int i = 0; i < csucsok; i++)
		{
			glVertex2i(round(pntX[i] * -1), round(pntY[i]));
		}
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
	cout << "2. Nagyitas" << endl;
	cout << "3. Forgatas" << endl;
	cout << "4. Tukrozes" << endl;
	cout << "5. Kilepes" << endl;

	cout << "*********************\n" << endl;

	cin >> choice;

	if (choice == 5) {
		return 0;
	}

	//********************
	//A valtozok bekerese*
	//********************

	cout << "\nHaromszog:\n" << endl;


	for (int i = 0; i < csucsok; i++)
	{
		cout << "Adja meg a csucsok koordinatait:  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
		pntX.push_back(pntX1);
		pntY.push_back(pntY1);
	}

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




	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Sikbeli transzformaciok");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
