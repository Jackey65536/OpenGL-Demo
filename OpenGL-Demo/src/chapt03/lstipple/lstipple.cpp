#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

#define GL_PI 3.1415f
#define GL_ROUND 3.0f

namespace Ch03 {
    namespace Lstipple {
        static GLfloat xRot = 0.0f;
        static GLfloat yRot = 0.0f;
        
        void RenderScene(void)
        {
            GLfloat y;
            GLint factor = 3;
            GLushort pattern = 0x5555;
            
            glClear(GL_COLOR_BUFFER_BIT);
            
            glPushMatrix();
            glRotatef(xRot, 1.0f, 0.0f, 0.0f);
            glRotatef(yRot, 0.0f, 1.0f, 0.0f);
            
            for (y = -90.0f; y < 90.0f; y+=20.0f) {
                glLineStipple(factor, pattern);
                
                glBegin(GL_LINES);
                glVertex2f(-80.0f, y);
                glVertex2f(80.0f, y);
                glEnd();
                
                factor++;
            }
            
            glPopMatrix();
            // Flush drawing commands
            glutSwapBuffers();
        }
        
        void SetupRC(void)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glEnable(GL_LINE_STIPPLE);
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
                xRot = 355.0f;
                yRot = 355.0f;
            }
            // 标记当前窗口需要重新绘制
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
            glutCreateWindow("Stippled Line Example");
            glutReshapeFunc(ChangeSize);
            glutSpecialFunc(SpecialKeys);
            glutDisplayFunc(RenderScene);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
