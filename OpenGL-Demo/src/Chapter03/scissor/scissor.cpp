#include <GLTools.h>
#include <glut/glut.h>

namespace Ch03 {
    namespace Scissor {
        void RenderScene(void)
        {
            glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
            glScissor(100, 100, 600, 400);
            glEnable(GL_SCISSOR_TEST);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
            glScissor(200, 200, 400, 200);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glDisable(GL_SCISSOR_TEST);
            
            glutSwapBuffers();
        }
        
        void ChangeSize(int w, int h)
        {
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            //定义了一个二维图像投影矩阵,left,right指明平面的左边和右边的垂直坐标, bottom,top指明平面底部和顶部的水平坐标。
            gluOrtho2D(-4.0, 4.0, -3.0, 3.0);
            
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        int main(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutCreateWindow("");
            glutDisplayFunc(RenderScene);
            glutReshapeFunc(ChangeSize);
            glutMainLoop();
            return 0;
        }
    }
}
