#include <GLTools.h>
#include <glut/glut.h>

namespace Ch02 {
    namespace Simple {
        void RenderScene(void)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
        }
        
        void ChangeSize(int w, int h)
        {
            printf("w = %d, h = %d\n", w, h);
        }
        
        void SetupRC()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        }
        
        int main(int argc, char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
            glutCreateWindow("Simple");
            glutDisplayFunc(RenderScene);
            glutReshapeFunc(ChangeSize);
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
