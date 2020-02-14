//============================================================================
// Name        : GL_fourie.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>


#define f(t)    (sinf(7*t+M_PI/4)+sinf(5*t+M_PI/4)*3+2*cosf(3*t))/15


void display()// Функция перерисовки дисплея
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static double time =0.0;
	static GLubyte color[1500][4];
	static GLfloat graf[1000][2];
	static GLfloat line[2][2];
	if(time==0.0)
	{
		for(int i=0;i<1500;i++)
		{
			color[i][0]=0xff;
			color[i][1]=0;
			color[i][2]=0;
			color[i][3]=0xff;
		}
		graf[0][0]=0;
		for(int i=0;i<1000;i++)
		{
			graf[i][0]=0.002*i;
			float integrate1=0;
			float integrate2=0;
			for(int k=0;k<1000;k++)
			{
				integrate1+=cosf(-(float)i*0.01*(float)k*0.01)*f(k*0.01)*0.01;
				integrate2+=sinf(-(float)i*0.01*(float)k*0.01)*f(k*0.01)*0.01;
			}
			graf[i][1]=powf(integrate2,2.0f)+powf(integrate1,2.0f);
		}
	}

	 static GLfloat cube[2000][2];
	 for(int i=-628;i<628;i++)
	 { cube[i+628][0]=cosf(-(float)i*0.01*time)*f(i*0.01); cube[i+628][1]=sinf(-(float)i*0.01*time)*f(i*0.01);
	  //cube[i][2]=0.00;
	 }

	line[0][0]=graf[int(time/0.003*3/10)][0];
	 line[0][1]=0.0;
	 line[1][0]=line[0][0];
	 line[1][1]=graf[int(time/0.003*3/10)][1];

	 if(time>10)exit(1);

	 //cube[0][0]+=0.001;

	 /* Do our drawing, too. */
	 /* Draw the cube */
	 glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
	 glEnableClientState(GL_COLOR_ARRAY);


	 glVertexPointer(2, GL_FLOAT, 0, cube);
	 glEnableClientState(GL_VERTEX_ARRAY);

	 glLoadIdentity();
	 glTranslatef(0,0.5,time);
	 //glRotatef(angle, 0.0, 1.0, 0.0);
	 //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
	 glDrawArrays(GL_LINE_STRIP,0,1256);

	  glLoadIdentity();

	 glTranslatef(-1,-1.0,0);
	 glVertexPointer(2, GL_FLOAT, 0, graf); glEnableClientState(GL_VERTEX_ARRAY);glDrawArrays(GL_LINE_STRIP,0,1000);

	 glDisableClientState(GL_COLOR_ARRAY);
	 glVertexPointer(2, GL_FLOAT, 0, line); glEnableClientState(GL_VERTEX_ARRAY);
	 glDrawArrays(GL_LINE_STRIP,0,2);

	 time+=0.003;
	 usleep(10000);

		glutSwapBuffers();

}


int main(int argc, char** argv)
{


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1920, 1080);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("graf");
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2, 2, -2, 2, -100, 100);
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glMatrixMode(GL_MODELVIEW);

  glutMainLoop();

  //glutTimerFunc()
}
