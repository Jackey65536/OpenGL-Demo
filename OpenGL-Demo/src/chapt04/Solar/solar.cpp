//// Solar.cpp
//// OpenGL SuperBible
//// Demonstrates OpenGL nested coordinate transformations
//// and perspective
//// Program by Richard S. Wright Jr.
//
//#include "GLTools.h"    // OpenGL toolkit
//#include "math3d.h"
//#include <glut/glut.h>
//#include <math.h>
//
//
//// Lighting values
//GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//GLfloat     lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//
//
//// Called to draw scene
//void RenderScene(void)
//{
//    // Earth and Moon angle of revolution
//    static float fMoonRot = 0.0f;
//    static float fEarthRot = 0.0f;
//
//    // Clear the window with current clearing color
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // 对模型视景操作
//    glMatrixMode(GL_MODELVIEW);
//    // 把当前状态做一个副本放入堆栈之中
//    glPushMatrix();
//
//    // 将整个场景坐标系往后移动300像素
//    glTranslatef(0.0f, 0.0f, -300.0f);
//
//    // Set material color, Red
//    glDisable(GL_LIGHTING);
//    // 设置画笔颜色为黄色
//    glColor3ub(255, 255, 0);
//    // 在当前坐标系原点画一个太阳
//    glutSolidSphere(50.0f, 30, 17);
//    glEnable(GL_LIGHTING);
//
//    // Move the light after we draw the sun!
//    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
//
//    // 将当前坐标系沿Y轴旋转
//    glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
//
//    // Draw the Earth
//    // 设置画笔颜色为蓝色
//    glColor3ub(0,0,255);
//    // 将当前坐标系沿X轴平移120像素
//    glTranslatef(120.0f,0.0f,0.0f);
//    // 在当前坐标系原点，画一个地球
//    glutSolidSphere(15.0f, 30, 17);
//
//
//    // Rotate from Earth based coordinates and draw Moon
//    // 设置画笔颜色为灰白色
//    glColor3ub(200,200,200);
//    // 沿Y轴旋转当前坐标系
//    glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
//    // 沿X轴平移当前坐标系
//    glTranslatef(30.0f, 0.0f, 0.0f);
//    // 在当前坐标系原点画个月球
//    glutSolidSphere(6.0f, 30, 17);
//
//    // 还原坐标系
//    glPopMatrix();    // Modelview matrix
//
//    fMoonRot+= 15.0f;
//    if(fMoonRot > 360.0f)
//        fMoonRot = 0.0f;
//
//    // Step earth orbit 5 degrees
//    fEarthRot += 5.0f;
//    if(fEarthRot > 360.0f)
//        fEarthRot = 0.0f;
//
//    // Show the image
//    glutSwapBuffers();
//}
//
//
//// This function does any needed initialization on the rendering
//// context.
//void SetupRC()
//{
//    // Light values and coordinates
//    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
//    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
//    glEnable(GL_CULL_FACE);        // Do not calculate inside of jet
//
//    // Enable lighting
//    glEnable(GL_LIGHTING);
//
//    // Setup and enable light 0
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
//    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
//    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
//    glEnable(GL_LIGHT0);
//
//    // Enable color tracking
//    glEnable(GL_COLOR_MATERIAL);
//
//    // Set Material properties to follow glColor values
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//    // Black blue background
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
//}
//
//
//void TimerFunc(int value)
//{
//    glutPostRedisplay();
//    glutTimerFunc(100, TimerFunc, 1);
//}
//
//void ChangeSize(int w, int h)
//{
//    GLfloat fAspect;
//
//    // Prevent a divide by zero
//    if(h == 0)
//        h = 1;
//
//    // Set Viewport to window dimensions
//    glViewport(0, 0, w, h);
//
//    // Calculate aspect ratio of the window
//    fAspect = (GLfloat)w/(GLfloat)h;
//
//    // Set the perspective coordinate system
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    // field of view of 45 degrees, near and far planes 1.0 and 425
//    gluPerspective(45.0f, fAspect, 1.0, 425.0);
//
//    // Modelview matrix reset
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Earth/Moon/Sun System");
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutTimerFunc(250, TimerFunc, 1);
//    SetupRC();
//    glutMainLoop();
//
//    return 0;
//    }
//
//
