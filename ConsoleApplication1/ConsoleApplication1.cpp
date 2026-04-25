
#include <iostream>
#include <conio.h>
#include <math.h>

#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glaux.h"

using namespace std;
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib, "glaux.lib")

#pragma comment(lib, "legacy_stdio_definitions.lib")

#pragma comment(lib, "winmm.lib")

void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b, float size = 2)
{
	glLineWidth(size);//Толщина линии 
	glBegin(GL_LINES);
	glColor3d(r, g, b);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}


double anglez = 0, anglex = 0, rz = 50;
double ex = 0, ey = 0, ez = rz;
double cx = 0, cy = 0, cz = 0;
//размеры окна
int w;
int h;



void CALLBACK resize(int width, int height)
{
	w = width;
	h = height;

	// Здесь вы указываете ту часть окна,
	// куда осуществляется вывод OpenGL.
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Устанавливаем тип проекции.
	// glOrtho - параллельная
	// glFrustum - перспективная
	// Параметры у этих функций одинаковые.
	// Они определяют объем, который вы видите.
	// левая стенка - пять единиц влево
	// правая - пять единиц вправо
	// далее, нижняя стенка и верхняя
	// и наконец, передняя и задняя
	gluPerspective(45.0, (GLfloat)width / height, 1.0, 10000.0);
	//   glOrtho(-5,5, -5,5, 2,12);
	   // Устанавливаем точку, в которой
	   // находится наш глаз ---(0,0,5)
	   // направление, куда смотрим --- (0,0,0)
	   // вектор, принимаемый за направление вверх --- (0,1,0)
	   // этим вектором является ось Y
	ex = rz * sin(anglez);
	ez = rz * cos(anglez);

	gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
	// glFrustum ( -1 , 1 , -1 , 1 , 1.25 , 10.0 ); //Область видимости
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.2, 0.3, 0.4, 0.0); //цвет фона
	//glClearDepth(1.0); // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST); //включить тест глубины
}

void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}


void DrawCircle(float x, float y, float r1, float r2, int slices)
{
	float angle = 2.0f * 3.141591f / slices;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < slices; i++)
	{
		float dx = r1 * cosf(angle * i);
		float dy = r2 * sinf(angle * i);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

GLuint texture[5];

GLvoid LoadBarashTextures()
{
	AUX_RGBImageRec* texture1;
	texture1 = auxDIBImageLoad(L"Barash.bmp");
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	AUX_RGBImageRec* texture2;
	texture2 = auxDIBImageLoad(L"Kub Kobein.bmp");
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
}

void DrawBarash(float xt, float yt, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) {
	glBegin(GL_QUADS);
	glTexCoord2f(xt, yt);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(xt + 0.19, yt);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(xt + 0.19, yt + 0.25);
	glVertex3f(x3, y3, z3);
	glTexCoord2f(xt, yt + 0.25);
	glVertex3f(x4, y4, z4);
	glEnd();
}

void Draw()
{
	
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//Бараш
	glRotated(GetTickCount64() * 0.1, 1, 1, 1);
	DrawBarash(0.48, 0.39, 0, 0, 0, 10, 0, 0, 10, 10, 0, 0, 10, 0); //Лицо
	DrawBarash(0.07, 0.39, 0, 10, 0, 10, 10, 0, 10, 10, -10, 0, 10, -10); //Макушка
	DrawBarash(0.07, 0.39, 0, 0, -10, 10, 0, -10, 10, 10, -10, 0, 10, -10); //Спина
	DrawBarash(0.07, 0.39, 0, 0, 0, 10, 0, 0, 10, 0, -10, 0, 0, -10); //Низ
	DrawBarash(0.28, 0.39, 0, 0, -10, 0, 0, 0, 0, 10, 0, 0, 10, -10); //Левый бок
	DrawBarash(0.68, 0.39, 10, 0, 0, 10, 0, -10, 10, 10, -10, 10, 10, 0); //Правый бок
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//Куб Кобейн
	glRotated(GetTickCount64() * 0.1, 1, 1, 1);
	DrawBarash(0.48, 0.39, 20, 0, 0, 30, 0, 0, 30, 10, 0, 20, 10, 0); //Лицо
	DrawBarash(0.07, 0.39, 20, 10, 0, 30, 10, 0, 30, 10, -10, 20, 10, -10); //Макушка
	DrawBarash(0.28, 0.39, 20, 0, -10, 30, 0, -10, 30, 10, -10, 20, 10, -10); //Спина
	DrawBarash(0, 0, 20, 0, 0, 30, 0, 0, 30, 0, -10, 20, 0, -10); //Низ
	DrawBarash(0.28, 0.39, 20, 0, -10, 20, 0, 0, 20, 10, 0, 20, 10, -10); //Левый бок
	DrawBarash(0.68, 0.39, 30, 0, 0, 30, 0, -10, 30, 10, -10, 30, 10, 0); //Правый бок
	glDisable(GL_TEXTURE_2D);
	


}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glTranslated(0, 0, -10);

	Draw();


	auxSwapBuffers();
}

void RunOpenGL()
{
	// указываем координаты окна на экране
	// верхний левый угол (50,10)
	// ширина и высота - 400
	auxInitPosition(0, 0, 1000, 1000);
	// устанавливаем параметры контекста OpenGL
	//
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);
	// создаем окно на экране
	auxInitWindow(L"Glaux Template");
	// наше окно будет получать сообщения
	// от клавиатуры, мыши, таймера или любые другие
	// когда никаких сообщений нет
	// будет вызываться функция display
	// так мы получаем анимацию
	// если вам нужна статическая картинка,
	// то закомментируйте следующую строку
	auxIdleFunc(display);
	// при изменении размеров окна
	// придет соответствующее сообщение
	// в Windows - это WM_SIZE
	// мы устанавливаем функцию resize,
	// которая будет вызвана
	// при изменении размеров окна
	auxReshapeFunc(resize);


	// и последнее, устанавливаем
   // функцию display отрисовки окна
   // эта функция будет вызываться всякий раз,
   // когда потребуется перерисовать окно
   // например, когда вы развернете окно на весь экран
   // в windows - это обработчик сообщения WM_PAINT

	glEnable(GL_BLEND);//разрешаем смешивание при наложении
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//устанавливаем наиболее подходящие параметры смешивания

	LoadBarashTextures();
}

void main()
{
	PlaySound(TEXT("Nirvana-Smells-Like-Teen-Spirit-Devonshire-Mix-_audiovk.com_.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ShowWindow(GetConsoleWindow(), 0); //handle window

	//if (startTime==0) startTime=GetTickCount();
	RunOpenGL();
	
	auxMainLoop(display);

}