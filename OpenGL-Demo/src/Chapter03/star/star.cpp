#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

#define GL_PI 3.1415f

#define MODE_SOLID 0
#define MODE_LINE 1
#define MODE_POINT 2

namespace Ch03 {
    namespace Star {
        static GLfloat xRot = 0.0f;
        static GLfloat yRot = 0.0f;
        
        int iMode = MODE_SOLID;
        GLboolean bEdgeFlag = GL_TRUE;
        
        void ProcessMenu(int value)
        {
            switch (value) {
                case 1:
                    iMode = MODE_SOLID;
                    break;
                case 2:
                    iMode = MODE_LINE;
                    break;
                case 3:
                    iMode = MODE_POINT;
                    break;
                case 4:
                    bEdgeFlag = GL_TRUE;
                    break;
                case 5:
                default:
                    bEdgeFlag = GL_FALSE;
                    break;
            }
            glutPostRedisplay();
        }
        
        void RenderScene()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            if (iMode == MODE_LINE) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            if (iMode == MODE_POINT) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            }
            if (iMode == MODE_SOLID) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            glPushMatrix();
            glRotatef(xRot, 1.0f, 0.0f, 0.0f);
            glRotatef(yRot, 0.0f, 1.0f, 0.0f);
            
            glBegin(GL_TRIANGLES);
            
            glEdgeFlag(bEdgeFlag);
            glVertex2f(-20.0f, 0.0f);
            glEdgeFlag(GL_TRUE);
            glVertex2f(20.0f, 0.0f);
            glVertex2f(0.0f, 40.0f);
            
            glVertex2f(-20.0f, 0.0f);
            glVertex2f(-60.0f, -20.0f);
            glEdgeFlag(bEdgeFlag);
            glVertex2f(-20.0f, -40.0f);
            glEdgeFlag(GL_TRUE);
            
            glVertex2f(-20.0f, -40.0f);
            glVertex2f(0.0f, -80.0f);
            glEdgeFlag(bEdgeFlag);
            glVertex2f(20.0f, -40.0f);
            glEdgeFlag(GL_TRUE);
            
            glVertex2f(20.0f, -40.0f);
            glVertex2f(60.0f, -20.0f);
            glEdgeFlag(bEdgeFlag);
            glVertex2f(20.0f, 0.0f);
            glEdgeFlag(GL_TRUE);
            
            glEdgeFlag(bEdgeFlag);
            glVertex2f(-20.0f, 0.0f);
            glVertex2f(-20.0f, -40.0f);
            glVertex2f(20.0f, 0.0f);
            
            glVertex2f(-20.0f, -40.0f);
            glVertex2f(20.0f, -40.0f);
            glVertex2f(20.0f, 0.0f);
            glEdgeFlag(GL_TRUE);
            
            glEnd();
            
            glPopMatrix();
            
            glutSwapBuffers();
        }
        
        void SetupRC()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        
        void SpecialKeys(int key, int x, int y)
        {
            printf("key = %d\n", key);
            if (key == GLUT_KEY_UP) {
                xRot -= 5.0f;
            }
            if (key == GLUT_KEY_DOWN) {
                xRot += 5.0f;
            }
            if (key == GLUT_KEY_LEFT) {
                yRot -= 5.0f;
            }
            if (key == GLUT_KEY_RIGHT) {
                yRot += 5.0f;
            }
            if (key > 356.0f) {
                xRot = 0.0f;
                yRot = 0.0f;
            }
            if (key < -1.0f) {
                xRot = 355.0f;
                yRot = 355.0f;
            }
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
        
        int main0(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutCreateWindow("Solid and Outlined Str");
            
            int nModeMenu = glutCreateMenu(ProcessMenu);
            glutAddMenuEntry("Solid", 1);
            glutAddMenuEntry("Outline", 2);
            glutAddMenuEntry("Points", 3);
            
            int nEdgeMenu = glutCreateMenu(ProcessMenu);
            glutAddMenuEntry("On", 4);
            glutAddMenuEntry("Off", 5);
            
            int nMainMenu = glutCreateMenu(ProcessMenu);
            glutAddSubMenu("Mode", nModeMenu);
            glutAddSubMenu("Edges", nEdgeMenu);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            glutReshapeFunc(ChangeSize);
            glutSpecialFunc(SpecialKeys);
            glutDisplayFunc(RenderScene);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
