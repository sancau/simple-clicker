// SimpleClicker game
// implemented via C++ / freeglut OpenGL
// by Alexander Tatchin

#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class HUDline // ��������� "��������"
{
public:
	float r, g, b;
	float y1 = 91.0;
	float y2 = 100.0; 
	float i;

	HUDline(float _i) // ����������� ���������� ���� ����� 
	{
		if (_i <= 50)
		{
			r = 0.3;
			g = 0.0;
			b = 0.0;
		}
		else
		{
			r = 0.0;
			g = 0.3;
			b = 0.0;
		}
		i = _i;
	}

	void drawline() // ����� ��������� ��������� ����� "��������"
	{
		glLineWidth(5.0);
		glColor3f(r, g, b);
		glBegin(GL_LINES);
		glVertex2f(i, y1);
		glVertex2f(i, y2);
		glEnd();
	}

	void deleteline()
	{
		glLineWidth(5.0);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(i, y1);
		glVertex2f(i, y2);
		glEnd();
	}
};

class UI // ����� ������� User Interface
{
public:
	float k = 50; //��������-���������� (�� �� ���������� "������")
	int score = 0;
	float hits;
	float clicks;
	int acc;
	int stage = 1;
	const char* numchar;

	UI(){}; // ����������� 

	void renew() // ����� ��� ��������������� ����������
	{
		clicks = 0;
		hits = 0;
		acc = 0;
		stage = 1;
		score = 0;
	}

	void drawHUD() // ��������� HUD, ����������� �������� k
	{
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(10.0);
		glBegin(GL_LINES);
		glVertex2f(0, 90);
		glVertex2f(100, 90);	
		glEnd();
		glLineWidth(5.0);
		glBegin(GL_LINES);
		glVertex2f(0, 10);
		glVertex2f(100, 10);
		glEnd();
		
		drawLevel();
		drawScore();
		drawAcc();
		drawText(3, 87, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "PRESS SPACE TO PAUSE THE GAME");

		for (float i = 1; i <= k; i++)
		{
			HUDline line(i);
			line.drawline();
		}

	}
	
	void drawAcc() // �������� ���������
	{
		if (clicks > 0)
		{
			acc = (hits / clicks) * 100;
			stringstream temp_str;
			temp_str << (acc);
			string str = temp_str.str();
			numchar = str.c_str();
			drawText(80, 14, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "Your accuracy:");
			drawText(92, 14, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, numchar);
			drawText(95, 14, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "%");
		}
		else
			return;
	}

	void drawLevel() // ��������� ������ ������
	{
		stringstream temp_str;
		temp_str << (stage);
		string str = temp_str.str();
		numchar = str.c_str();
		drawText(5, 7, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "CURRENT LEVEL:");
		drawText(32, 7, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numchar);
	}

	void drawScore() // ��������� �����
	{
		stringstream temp_str;
		temp_str << (score);
		string str = temp_str.str();
		numchar = str.c_str();
		drawText(65, 7, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "GAINED SCORE:");
		drawText(90, 7, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numchar);
	}

	void drawText(float _x, float _y, float _r, float _g, float _b, void *font, const char *_str) // ����� ��� ��������� ������
	{
		glColor3f(_r, _g, _b);
		glRasterPos2f(_x, _y);
		int len, i;
		len = (int)strlen(_str);
		for (i = 0; i < len; i++) 
		{
			glutBitmapCharacter(font, _str[i]);
		}
	}

	void drawIntro() // ��������� �����
	{
		drawText(10, 10, 0.0, 0.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "Welcome to SIMPLECLICKER!");
		drawText(10, 20, 0.0, 0.0, 1.0, GLUT_BITMAP_HELVETICA_18, "Hit targets with your mouse and progress through levels to GAIN MORE SCORE!");
		drawText(33, 50, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "PRESS SPACE TO START");
		drawText(10, 80, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "Made by Alexander Tatchin");
		drawText(10, 85, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "Implemented via Visual C++ / Freeglut OPEN_GL");
		drawText(10, 90, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, "Feb 2015");
	}

	void drawPause() // ����� �����
	{
		drawText(17, 50, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "GAME PAUSED. PRESS SPACE TO CONTINUE.");
	}
		
	void strike() // �������� ���� �� ����, ����� ++
	{
		k++; k++;
	}

	void fail()  // �������� ���� �� ����, ����� --
	{
		k--; k--;
	}

	void scores() // ���� "game over"
	{
		drawText(17, 20, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU'VE RAN OUT OF ENERGY! GAME OVER.");

		stringstream temp_str;
		temp_str << (score);
		string str = temp_str.str();
		numchar = str.c_str();
		drawText(40, 40, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "GAINED SCORE:");
		drawText(65, 40, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numchar);

		stringstream temp_str1;
		temp_str1 << (stage);
		string str1 = temp_str1.str();
		numchar = str1.c_str();
		drawText(38, 50, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL ACHIVED:");
		drawText(65, 50, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numchar);

		stringstream temp_str2;
		temp_str2 << (acc);
		string str2 = temp_str2.str();
		numchar = str2.c_str();
		drawText(30, 60, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "AVERAGE ACCURACY:");
		drawText(65, 60, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numchar);
		drawText(69, 60, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "%");
				
		drawText(28, 80, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "PRESS SPACE TO TRY AGAIN!");
	}
};

UI ui;

class Target // �������� ����������� ��������-�����
{
public:
	float x, y, r;
	Target(float _x, float _y, float _r)
	{
		x = _x; y = _y; r = _r; 
	}
}; 

class TargetManager // ���������� ������������ ����� � �� ����������
{
public:
	float x, y, r;
	float diff_r = 0.05; // �������� ����� ������� ���� - > �������� �� ���� ���������
	unsigned int intended; // ���������� ����� - > �������� �� ���� ��������� 
	float maxr = 8.0; // ������ ��� ���������� �������� ���� ������������
	const unsigned int max_targ = 5;

	
	void stagecreate() // ������� ����� ��������
	{
		if (intended < max_targ)
		{
			intended = ui.stage + 1;
		}
		if (ui.k >= 100)
		{
			ui.stage++; 
			diff_r += 0.01;
			maxr -= 0.3;
			ui.k = 50;
		}
	}

	vector<Target> targetlist; 
	void createTarget() // ������� ����
	{
		x = 10 + rand() % 80;
		y = 20 + rand() % 60;
		r = 2;
		Target target(x, y, r);
		targetlist.push_back(target);
	}

	void listfiller() // ��������� ������
	{
		// ���������� ����� 
		while (targetlist.size() != intended)
		{
			createTarget();
		}
	}
	
	void drawTargets()
	{
		vector<Target>::iterator i = targetlist.begin();
		while (i != targetlist.end())
		{
			glColor3f(0.0, 0.0, 0.7);
			glLineWidth(10.0);
			glBegin(GL_LINE_LOOP);
			for (float k = 0.0; k < 2 * 3.14; k += 3.14 / 18)
			{
				glVertex2f(i->x + i->r*sin(k), i->y + i->r*cos(k));
			}
			glEnd();
			++i;
		}
	}

	void statuscheck() // ����� �����, ���� �������
	{
		vector<Target>::iterator i = targetlist.begin();   // <<<- ����������� �������� � while �� �� �������� ����� for. ������???
		while (i != targetlist.end())
		{
			if (i->r > maxr)// ����� ����� ����
			{
				i = targetlist.erase(i); //������� ������
				ui.fail(); //�������������� ����������� �������� 
				ui.score -= 7*ui.stage*10*0.7;
				if (ui.score < 0)
				{
					ui.score = 0;
				}
			}
			else
			{
				i->r+=diff_r; // ��������� �������
				++i;
			}
		}
	}

	void strikecheck(float _x0, float _y0) // �������� ���������
	{
		float x0 = _x0;
		float y0 = _y0;

		vector<Target>::iterator i = targetlist.begin();
		while (i != targetlist.end())
		{
			float delta = abs(sqrt((x0 - i->x)*(x0 - i->x) + (y0 - i->y)*(y0 - i->y)));
			if (delta <= i->r)
			{
				i = targetlist.erase(i);
				ui.strike();
				ui.score += 10*10*ui.stage;
				ui.hits++;
				return;
			}
			++i;
		}
	}

	void destructor() // ������� ������, ���������� ��� ����������� ���������� � ����������� ���������
	{
		vector<Target>().swap(targetlist);
		ui.k = 50;
		x, y, r;
		diff_r = 0.05; 
		intended = 0;
	}
};

TargetManager targetmanager;

class GameDirector // ����� ����������� �������
{
public:
	int state = 0; // ���������� ���� - ��� ����������� � ����� ��������� �������� ����
	bool spacepressed = false; // ����� �� ������

	GameDirector(){} // ����������� �� ���������

	void mainmenu() // intro ������� ���� ���������� ������ ����, �������� �������, "press space to start!"
	{
		ui.drawIntro();
	}

	void gameprocess() // ����� ��������� ������� ����, � ������� ����������� (������� �� ������) / ����� - �������, ����, "press space to pause"
	{
		ui.drawHUD();
		targetmanager.stagecreate();
		targetmanager.listfiller();
		targetmanager.drawTargets();
		targetmanager.statuscheck();
		if (ui.k <= 0)
		{
			state = 3;
		}
	}

	void gamepause() // ������ �� ����� 
	{
		ui.drawHUD();
		targetmanager.drawTargets();
		ui.drawPause(); 
	}

	void gameover() // ����������� ����, ���������� �������, ���������� ��������� ����, ������� top score, "press space to restart, ������� �������� ������ ��������, ����� � �.�.
	{
		ui.scores();
		targetmanager.destructor();
	}
};

GameDirector director;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 

	//��������� "��������" ���������
	
	switch (director.state)
	{
	case 0: 
		director.mainmenu();
		break;
	case 1:	 
		director.gameprocess();
		break;
	case 2: 
		director.gamepause();
		break;
	case 3:	
		director.gameover();
		break;
	default: 
		return;
	}

	if (director.spacepressed)
	{
		switch (director.state)
		{
		case 0: 
			director.gameprocess();
			director.state = 1;
			break;
		case 1:	
			director.gamepause();
			director.state = 2;
			break;
		case 2:	
			director.state = 1;
			break;
		case 3:	
			ui.renew();
			director.gameprocess();
			director.state = 1;
			break;
		default:
			return;
		}
		director.spacepressed = false;
	}
	
	glutSwapBuffers();
}

void Timer(int) 
{	
	glutPostRedisplay();
	display();
	glutTimerFunc(50, Timer, 0);
}

void MouseFunc(int button, int state, int x, int y) // ������������ ����
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		if (director.state == 1)
		{
			ui.clicks++;
			targetmanager.strikecheck(x / 8, y / 8);
		}
	}
}

void KeyboardFunc(unsigned char key, int x, int y) // ������������ ����������
{
	switch (key)
	{
	case ' ':
		if (director.spacepressed == false)
		{
			director.spacepressed = true;
		}
		else
		{
			director.spacepressed = false;
		}
		break;
	default: return;
	}
}

int main(int argc, char **argv)
{
	srand(time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SimpleClicker");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100, 100, 0, -1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(MouseFunc);
	glutKeyboardFunc(KeyboardFunc);
	Timer(0);
	glutMainLoop();
}