/*
 #include <GLTools.h>
 #include <glut/glut.h>
 
 void Display()
 {
 //画分割线 ，分成四个视图区域
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0, 0.0, 0.0);
 glViewport(0, 0, 400, 400);
 glBegin(GL_LINES);
 glVertex2f(-1.0, 0);
 glVertex2f(1.0, 0);
 glVertex2f(0, -1.0);
 glVertex2f(0, 1.0);
 glEnd();
 //定义左下角区域
 glColor3f(0.0, 1.0, 0.0);
 glViewport(0, 0, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 glBegin(GL_LINES);
 glVertex2f(-1.0, -1.0);
 glVertex2f(1.0, 1.0);
 glVertex2f(1.0, -1.0);
 glVertex2f(-1.0, 1.0);
 glEnd();
 //定义右上角区域
 glColor3f(0.0, 0.0, 1.0);
 glViewport(200, 200, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 glBegin(GL_LINES);
 glVertex2f(-1.0, -1.0);
 glVertex2f(1.0, 1.0);
 glVertex2f(1.0, -1.0);
 glVertex2f(-1.0, 1.0);
 glEnd();
 //定义在左上角的区域
 glColor3f(1.0, 0.0, 0.0);
 glViewport(0, 200, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 glBegin(GL_LINES);
 glVertex2f(-1.0, -1.0);
 glVertex2f(1.0, 1.0);
 glVertex2f(1.0, -1.0);
 glVertex2f(-1.0, 1.0);
 glEnd();
 //定义在右下角的区域
 glColor3f(1.0, 1.0, 1.0);
 glViewport(200, 0, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 glBegin(GL_LINES);
 glVertex2f(-1.0, -1.0);
 glVertex2f(1.0, 1.0);
 glVertex2f(1.0, -1.0);
 glVertex2f(-1.0, 1.0);
 glEnd();
 glFlush();
 }
 
 int main(int argc, char* argv[])
 {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(400, 400);
 glutCreateWindow("glViewport");
 glutDisplayFunc(Display);
 glutMainLoop();
 return 0;
 }

 */
