#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

#define GL_PI 3.1415f
#define GL_ROUNDS 3.0f

namespace Ch03 {
    namespace Lstrips {
        static GLfloat xRot = 0.0f;
        static GLfloat yRot = 0.0f;
        
        void RenderScene(void)
        {
            GLfloat x, y, z, angle;
            glClear(GL_COLOR_BUFFER_BIT);
            glPushMatrix();
            glRotatef(xRot, 1.0f, 0.0f, 0.0f);
            glRotatef(yRot, 0.0f, 1.0f, 0.0f);
            glBegin(GL_LINE_STRIP); // 一系列的连续直线
            z = -50.0f;
            for (angle = 0.0f; angle <= (2.0f*GL_PI)*GL_ROUNDS; angle += 0.1f) {
                x = 50.0f*sin(angle);
                y = 50.0f*cos(angle);
                glVertex3f(x, y, z);
                z += 0.5f;
            }
            glEnd();
            glPopMatrix();
            glutSwapBuffers();
        }
        
        void SetupRC(void)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        
        void SpecialKeys(int key, int x, int y)
        {
            switch (key) {
                case GLUT_KEY_UP:
                    xRot -= 5.0f;
                    break;
                case GLUT_KEY_DOWN:
                    xRot += 5.0f;
                    break;
                case GLUT_KEY_LEFT:
                    yRot -= 5.0f;
                    break;
                case GLUT_KEY_RIGHT:
                    yRot += 5.0f;
                    break;
            }
            if (key > 356.0f) {
                xRot = 0.0f;
                yRot = 0.0f;
            }
            if (key < -1.0f) {
                yRot = 355.0f;
            }
            // Refresh the window
            glutPostRedisplay();
        }
        
        void ChangeSize(int w, int h)
        {
            GLfloat nRange = 100.0f;
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if (w <= h) {
                glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
            } else {
                glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        int main(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutCreateWindow("Line Strips Example");
            glutReshapeFunc(ChangeSize);
            glutSpecialFunc(SpecialKeys);
            glutDisplayFunc(RenderScene);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
