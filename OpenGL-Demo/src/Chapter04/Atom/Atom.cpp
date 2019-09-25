#include <GLTools.h>
#include <glut/glut.h>

namespace Ch04 {
    namespace Atom {
        static GLfloat xRot = 0.0f;
        static GLfloat yRot = 0.0f;
        
        void RenderScene(void)
        {
            static GLfloat fElect1 = 0.0f;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            
            // 沿着z轴，向里平移整个场景
            glTranslatef(0.0f, 0.0f, -100.0f);
            glColor3ub(255, 0, 0);
            // 渲染一个球体，参数：球半径、经线数、纬线数
            glutSolidSphere(10.0f, 15, 15);
            glColor3ub(255, 255, 0);
            // 保存场景状态
            glPushMatrix();
            glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
            glTranslatef(90.0f, 0.0f, 0.0f);
            glutSolidSphere(6.0f, 15, 15);
            
            glPopMatrix();
            
            glPushMatrix();
            glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
            glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
            glTranslatef(-70.0f, 0.0f, 0.0f);
            glutSolidSphere(6.0f, 15, 15);
            glPopMatrix();
            
            glPushMatrix();
            glRotatef(360.0f-45.0f, 0.0f, 0.0f, 1.0f);
            glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
            glutSolidSphere(6.0f, 15, 15);
            glPopMatrix();
            
            fElect1 += 10.0f;
            if (fElect1 > 360.0f) {
                fElect1 = 0.0f;
            }
            glutSwapBuffers();
        }
        
        void SetupRC()
        {
            glEnable(GL_DEPTH_TEST);
            glFrontFace(GL_CCW);
            glEnable(GL_CULL_FACE);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        void SpecialKeys(int key, int x, int y)
        {
            if (key == GLUT_KEY_UP) { xRot -= 5.0f; }
            if (key == GLUT_KEY_DOWN) { xRot += 5.0f; }
            if (key == GLUT_KEY_LEFT) { yRot -= 5.0f; }
            if (key == GLUT_KEY_RIGHT) { yRot += 5.0f; }
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
        
        void TimerFunc(int value)
        {
            glutPostRedisplay();
            glutTimerFunc(100, TimerFunc, 1);
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
                glOrtho(-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0f, nRange*2.0f);
            } else {
                glOrtho(-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0f, nRange*2.0f);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        int main(int argc, char* argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            glutInit(&argc, argv);
            glutInitWindowSize(800, 600);
            glutCreateWindow("OpenGL Atom");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            glutTimerFunc(500, TimerFunc, 1);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
