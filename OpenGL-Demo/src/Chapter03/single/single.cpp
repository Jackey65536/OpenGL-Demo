#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

namespace Ch03 {
    namespace Single {
        void RenderScene(void)
        {
            static GLdouble dRadius = 0.1;
            static GLdouble dAngle = 0.0;
            //    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
            if (dAngle == 0.0) {
                glClear(GL_COLOR_BUFFER_BIT);
            }
            glBegin(GL_POINTS);
            glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
            glVertex2d(dRadius * sin(dAngle), dRadius * cos(dAngle));
            glEnd();
            dRadius *= 1.01;
            dAngle += 0.1;
            if (dAngle > 30.0) {
                dRadius = 0.1;
                dAngle = 0.0;
            }
            glFlush();
        }
        
        void ChangeSize(int w, int h)
        {
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-4.0, 4.0, -3.0, 3.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        void Timer(int value)
        {
            glutTimerFunc(50, Timer, 0);
            glutPostRedisplay();
        }
        
        int main(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_RGB);
            glutInitWindowSize(800, 600);
            glutCreateWindow("OpenGL Signle Buffered");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            glutTimerFunc(50, Timer, 0);
            glutMainLoop();
            return 0;
        }
    }
}
