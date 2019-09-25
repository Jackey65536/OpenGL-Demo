#include <GLTools.h>
#include <glut/glut.h>

namespace ch02 {
    namespace Glrect {
        void RenderScene(void)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(0.7f, 0.7f, 0.0f);
            glRectf(-25.0f, 25.0f, 25.0f, -25.0f);
            glFlush();
        }
        
        void ChangeSize(int w, int h)
        {
            GLfloat aspectRatio;
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            //    glMatrixMode(GL_PROJECTION);
            //    glLoadIdentity();
            //    aspectRatio = (GLfloat)w/(GLfloat)h;
            //    if (w <= h) {
            //        glOrtho(-100.0f, 100.0f, -100.0f/aspectRatio, 100.0/aspectRatio, 1.0f, -1.0f);
            //    } else {
            //        glOrtho(-100.0f * aspectRatio, 100.0f * aspectRatio, -100.0f, 100.0f, 1.0f, -1.0f);
            //    }
            //    glMatrixMode(GL_MODELVIEW);
            //    glLoadIdentity();
        }
        
        void SetupRC(void)
        {
            glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        }
        
        int main0(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutCreateWindow("GLRect");
            glutDisplayFunc(RenderScene);
            glutReshapeFunc(ChangeSize);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
