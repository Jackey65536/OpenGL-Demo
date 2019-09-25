#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

namespace Ch03 {
    namespace Stencil {
        GLfloat x = 0.0f;
        GLfloat y = 0.0f;
        GLfloat rsize = 25.0f;
        
        GLfloat xstep = 1.0f;
        GLfloat ystep = 1.0f;
        
        GLfloat windowWidth;
        GLfloat windowHeight;
        
        
        void RenderScene()
        {
            GLdouble dRadius = 0.1;
            GLdouble dAngle;
            
            glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
            
            glClearStencil(0.0f);
            glEnable(GL_STENCIL_TEST);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            
            glStencilFunc(GL_NEVER, 0x0, 0x0);
            glStencilOp(GL_INCR, GL_INCR, GL_INCR);
            
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINE_STRIP);
            for (dAngle = 0; dAngle < 400.0; dAngle += 0.1) {
                glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
                dRadius *= 1.002;
            }
            glEnd();
            
            glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            
            glColor3f(1.0f, 0.0f, 0.0f);
            glRectf(x, y, x + rsize, y - rsize);
            
            glutSwapBuffers();
        }
        
        void TimerFunction(int value)
        {
            if (x > windowWidth-rsize || x < -windowWidth) {
                xstep = -xstep;
            }
            if (y > windowHeight || y < -windowHeight+rsize) {
                ystep = -ystep;
            }
            if (x > windowWidth-rsize) {
                x = windowWidth-rsize-1;
            }
            if (y > windowHeight) {
                y = windowHeight-1;
            }
            x += xstep;
            y += ystep;
            
            glutPostRedisplay();
            glutTimerFunc(33, TimerFunction, 1);
        }
        
        void ChangeSize(int w, int h)
        {
            GLfloat aspectRatio;
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            
            aspectRatio = (GLfloat)w/(GLfloat)h;
            if (w <= h) {
                windowWidth = 100.0;
                windowHeight = 100.0/aspectRatio;
                glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);
            }else{
                windowWidth = 100.0 * aspectRatio;
                windowHeight = 100.0;
                glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        int main0(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutCreateWindow("OpenGL Stencil Test");
            glutInitWindowSize(800, 600);
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            glutTimerFunc(33, TimerFunction, 1);
            glutMainLoop();
            return 0;
        }
    }
}
