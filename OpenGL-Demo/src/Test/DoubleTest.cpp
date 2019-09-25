#include "GLTools.h"
#include <glut/glut.h>
#include <math.h>

namespace Test {
    namespace DoubleTest {
        static GLfloat angle = 0.0;
        
        void display()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            
            //矩阵堆栈，可以消除上一次的变换对本次变换的影响，一系列像平移，旋转，缩放等的矩阵变换操作放在它们之间可以简化操作，不然每次改变都要重新设置矩阵模式
            glPushMatrix();
            glRotatef(angle, 0.0, 0.0, 1.0);  //旋转
            glColor3f(1.0, 0.0, 0.0);
            glRectf(-25.0, -25.0, 25.0, 25.0); //绘制矩形
            glPopMatrix();
            
            glutSwapBuffers();  //后台缓冲区交换到前台缓冲区显示
        }
        
        void init()
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            
            //设置着色模式：GL_FLAT：恒定着色，用某个顶点颜色来渲染整个图元GL_SMOOTH：光滑着色，独立的处理图元中各个顶点的颜色。
            glShadeModel(GL_FLAT);
        }
        
        void reshape(int w, int h)
        {
            glViewport(0, 0, (GLsizei)w, (GLsizei)h);  //设置视口，即显示区域
            
            //设置矩阵操作模式，简单的说就是设置状态，接下来将要进行投影矩阵的操作
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            
            //glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0); //参数设置的是视景体
            if (w <= h)//设置视景体与视口宽高比例一致，这样改变窗口大小，物体也不会变形
                glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h/(GLfloat)w, 50.0 * (GLfloat)h/(GLfloat)w, -1.0, 1.0);
            else
                glOrtho(-50.0*(GLfloat)w/(GLfloat)h, 50*(GLfloat)w/(GLfloat)h, -50, 50, -1.0, 1.0);
            
            //接下来的矩阵操作设置为模型操作,即平移，旋转，缩放等操作
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        void spinDisplay()
        {
            angle = angle + 2.0;
            if (angle > 360.0)
                angle = angle - 360.0;
            glutPostRedisplay();   //重新绘制窗口
        }
        
        void mouse(int button, int state, int x, int y)
        {
            switch (button) {
                case GLUT_LEFT_BUTTON:
                    if (state == GLUT_DOWN)
                        glutIdleFunc(spinDisplay); //消息循环处于空闲的时候响应
                    break;
                case GLUT_RIGHT_BUTTON:
                    if(state == GLUT_DOWN)
                        glutIdleFunc(NULL);
                    break;
                default:
                    break;
            }
        }
        
        
        int main(int argc,char* argv[])
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //显示模式：双缓冲，RGB模式
            glutInitWindowSize(250, 250);
            glutInitWindowPosition(100, 100);
            glutCreateWindow("double");
            init();
            glutDisplayFunc(display);
            glutReshapeFunc(reshape);  //窗口大小改变调用的回调函数
            glutMouseFunc(mouse);   //鼠标按钮回调
            glutMainLoop();
            return 0;
        }
    }
}
