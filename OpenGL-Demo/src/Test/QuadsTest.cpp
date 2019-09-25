// GlutQuadsDemo.cpp : 定义控制台应用程序的入口点。
//
#include <GLTools.h>
#include <glut/glut.h>
#include <math.h>

//圆周率宏
#define GL_PI 3.1415f

namespace Test {
    namespace QuadsTest {
        //获取屏幕的宽度
        GLint SCREEN_WIDTH=0;
        GLint SCREEN_HEIGHT=0;
        //设置程序的窗口大小
        GLint windowWidth=400;
        GLint windowHeight=300;
        //绕x轴旋转角度
        GLfloat xRotAngle=0.0f;
        //绕y轴旋转角度
        GLfloat yRotAngle=0.0f;
        
        //是否打开不显示背面功能
        GLint cullFace=0;
        //是否打开深度测试功能
        GLint depthTest=0;
        //背面是采用线条描外框还是使用单色填充
        GLint outLine=0;
        //菜单回调函数
        void processMenu(int value){
            switch(value){
                case 1:
                    depthTest=!depthTest;
                    break;
                case 2:
                    cullFace=!cullFace;
                case 3:
                    outLine=!outLine;
                    break;
                default:
                    break;
            }
            //重新绘制
            glutPostRedisplay();
        }
        //显示回调函数
        void renderScreen(void){
            GLfloat x,y,z,angle;
            //把整个窗口清理为当前清理颜色：黑色
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            //将当前Matrix状态入栈
            glPushMatrix();
            //坐标系绕x轴旋转xRotAngle
            glRotatef(xRotAngle,1.0f,0.0f,0.0f);
            //坐标系绕y轴旋转yRotAngle
            glRotatef(yRotAngle,0.0f,1.0f,0.0f);
            if(depthTest)
                glEnable(GL_DEPTH_TEST);//打开深度测试功能
            else
                glDisable(GL_DEPTH_TEST);//关闭深度测试功能
            if(cullFace)
                glEnable(GL_CULL_FACE);//打开不显示背面功能
            else
                glDisable(GL_CULL_FACE);//关闭不显示背面功能
            if(outLine)
                glPolygonMode(GL_BACK,GL_LINE);//多边形背部使用线条描框
            else
                glPolygonMode(GL_BACK,GL_FILL);//多边形背部使用单色填充
            x=0.0f;
            y=0.0f;
            z=0.0f;
            //进行平滑处理
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH,GL_NICEST);
            //绘制坐标系
            glColor3f(1.0f,1.0f,1.0f);
            glBegin(GL_LINES);
            glVertex3f(-80.0f,0.0f,0.0f);
            glVertex3f(80.0f,0.0f,0.0f);
            glVertex3f(0.0f,-80.0f,0.0f);
            glVertex3f(0.0f,80.0f,0.0f);
            glVertex3f(0.0f,0.0f,-80.0f);
            glVertex3f(0.0f,0.0f,80.0f);
            glEnd();
            
            glPushMatrix();
            glTranslatef(80.0f,0.0f,0.0f);
            glRotatef(90.0f,0.0f,1.0f,0.0f);
            glutWireCone(3,6,10,10);
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(0.0f,80.0f,0.0f);
            glRotatef(-90.0f,1.0f,0.0f,0.0f);
            glutWireCone(3,6,10,10);
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(0.0f,0.0f,80.0f);
            glRotatef(90.0f,0.0f,0.0f,1.0f);
            glutWireCone(3,6,10,10);
            glPopMatrix();
            
            //开始绘制两个四边形
            glBegin(GL_QUADS);
            //红色绘制第一个四边形
            glColor3f(1.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(25.0f,0.0f,0.0f);
            glVertex3f(30.0f,30.0f,0.0f);
            glVertex3f(0.0f,25.0f,0.0f);
            
            //红色绘制第二个四边形
            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(-25.0f,0.0f,0.0f);
            glVertex3f(-30.0f,-30.0f,0.0f);
            glVertex3f(0.0f,-25.0f,0.0f);
            //结束绘四边形
            glEnd();
            
            //恢复压入栈的Matrix
            glPopMatrix();
            //交换两个缓冲区的指针
            glutSwapBuffers();
        }
        //设置Redering State
        void setupRederingState(void){
            //设置清理颜色为黑色
            glClearColor(0.0f,0.0,0.0,1.0f);
            //设置绘画颜色为绿色
            glColor3f(0.0f,1.0f,0.0f);
        }
        //窗口大小变化回调函数
        void changSize(GLint w,GLint h){
            //横宽比率
            GLfloat ratio;
            //设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
            GLfloat coordinatesize=100.0f;
            //窗口宽高为零直接返回
            if((w==0)||(h==0))
                return;
            //设置视口和窗口大小一致
            glViewport(0,0,w,h);
            //对投影矩阵应用随后的矩阵操作
            glMatrixMode(GL_PROJECTION);
            //重置当前指定的矩阵为单位矩阵
            glLoadIdentity();
            ratio=(GLfloat)w/(GLfloat)h;
            //正交投影
            if(w<h)
                glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
            else
                glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
            //对模型视图矩阵堆栈应用随后的矩阵操作
            glMatrixMode(GL_MODELVIEW);
            //重置当前指定的矩阵为单位矩阵
            glLoadIdentity();
        }
        
        //按键输入处理回调函数
        void specialKey(int key,int x,int y){
            
            if(key==GLUT_KEY_UP){
                xRotAngle-=5.0f;
            }
            else if(key==GLUT_KEY_DOWN){
                xRotAngle+=5.0f;
            }
            else if(key==GLUT_KEY_LEFT){
                yRotAngle-=5.0f;
            }
            else if(key==GLUT_KEY_RIGHT){
                yRotAngle+=5.0f;
            }
            //重新绘制
            glutPostRedisplay();
        }
        
        int main(int argc, char* argv[])
        {
            //初始化glut
            glutInit(&argc,argv);
            //使用双缓冲区模式
            glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
            //获取系统的宽像素
            SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
            //获取系统的高像素
            SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
            //创建窗口，窗口名字为OpenGL TriAngle Demo
            glutCreateWindow("OpenGL Quads Demo");
            //菜单回调函数
            glutCreateMenu(processMenu);
            //添加菜单
            glutAddMenuEntry("Toggle depth test",1);
            glutAddMenuEntry("Toggle cull face",2);
            glutAddMenuEntry("Toggle back outline",3);
            //将菜单榜定到鼠标右键上
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            //设置窗口大小
            glutReshapeWindow(windowWidth,windowHeight);
            //窗口居中显示
            glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
            //窗口大小变化时的处理函数
            glutReshapeFunc(changSize);
            //设置显示回调函数
            glutDisplayFunc(renderScreen);
            //设置按键输入处理回调函数
            glutSpecialFunc(specialKey);
            //设置全局渲染参数
            setupRederingState();
            glutMainLoop();
            return 0;
        }
    }
}

