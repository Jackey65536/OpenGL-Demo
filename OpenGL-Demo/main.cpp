//#include "GLShaderManager.h"
//#include "GLTools.h"
//
////GLUT头文件，包含了<GL/gl.h>,<GL/glu.h>
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//#include <math.h>
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
///*-----------------test0-----------------*/
//// 简单的批次容器
//GLBatch triangleBatch;
//// 定义一个着色器管理器
//GLShaderManager shaderManager;
//
//GLfloat vVerts[] = {
//    -0.5f,  0.0f,   0.0f,
//    0.5f,   0.0f,   0.0f,
//    0.0f,  0.5f,   0.0f,
//};
//
//void ChangeSize(int w,int h) {
//    //窗口大小改变时接受新的宽度和高度，其中0,0代表窗口中视口的左下角坐标，w，h代表宽高
//    glViewport(0, 0, w, h);
//}
//
////为程序作一次性的设置
//void SetupRC()
//{
//    //设置背影颜色，这个函数不会立即清除背景，而是设置在以后颜色缓冲区被清除时使用的颜色
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    //初始化着色管理器
//    shaderManager.InitializeStockShaders();
//    //设置三角形，其中数组vVert包含所有3个顶点的x,y,笛卡尔坐标对。
//
//    //批次处理
//    triangleBatch.Begin(GL_TRIANGLES, 3);
//    triangleBatch.CopyVertexData3f(vVerts);
//    triangleBatch.End();
//}
//
////开始渲染
//void RenderScene(void)
//{
//    //清除一个或一组特定的缓冲区
//    /*
//     GL_COLOR_BUFFER_BIT:颜色缓冲区
//     GL_DEPTH_BUFFER_BIT:深度缓冲区
//     GL_STENCIL_BUFFER_BIT:模板缓冲区
//     */
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
//    //设置一组浮点数来表示红色
//    GLfloat vRed[] = {0.5f, 0.5f, 0.0f, 1.0f};
//    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
//    /*
//     GLT_SHADER_IDENTITY:所有片段都应用同一种颜色
//     GLT_SHADER_FLAT:将统一着色器进行了扩展，允许为几何图形变换指定一个4x4变换矩阵。典型情况下这是一种左乘模型视图矩阵和投影矩阵，经常被称作”模型视图投影矩阵“
//     GLT_SHADER_SHADED:这种着色器唯一的Uniformj值就是在几何图形中应用的变换矩阵。颜色值将被平滑的插入顶点之间（称为平滑着色）
//     GLT_SHADER_DEFAULT_LIGHT:默认光源着色器。这种着色器使对象产生阴影和光照的效果
//     GLT_SHADER_POINT_LIGHT_DIFF:点光源着色器。
//     GLT_SHADER_TEXTURE_DEPLACE:纹理替换矩阵。
//     GLT_SHADER_TEXTURE_MODULATE:纹理调整着色器。
//     GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF:纹理光源着色器。
//     */
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
//    //将几何图形提交到着色器
//    triangleBatch.Draw();
//    //将在后台缓冲区进行渲染，然后在结束时交换到前台
//    glutSwapBuffers();
//}
//
//void SpecialKeys(int key, int x, int y)
//{
//    GLfloat stepSize = 0.25f;
//    GLfloat blockSize = 0.25f;
//    GLfloat blockX = vVerts[0];
//    GLfloat blockY = vVerts[7];
//    switch (key) {
//        case GLUT_KEY_UP:
//            blockY += stepSize;
//            break;
//        case GLUT_KEY_DOWN:
//            blockY -= stepSize;
//            break;
//        case GLUT_KEY_LEFT:
//            blockX -= stepSize;
//            break;
//        case GLUT_KEY_RIGHT:
//            blockX += stepSize;
//            break;
//    }
//    if (blockY < -1.0f) {
//        blockX = -1.0f;
//    }
//    if (blockX > (1.0f - blockSize * 2)) {
//        blockX = 1.0f - blockSize * 2;
//    }
//    if (blockY < -1.0f + blockSize * 2) {
//        blockY = -1.0f + blockSize * 2;
//    }
//    if (blockY > 1.0f) {
//        blockY = 1.0f;
//    }
//    vVerts[0] = blockX;
//    vVerts[1] = blockY - blockSize*2;
//
//    vVerts[3] = blockX + blockSize*2;
//    vVerts[4] = blockY - blockSize*2;
//
//    vVerts[6] = blockX + blockSize*2;
//    vVerts[7] = blockY;
//
//    //    vVerts[9] = blockX;0
//    //    vVerts[10] = blockY;
//
//    triangleBatch.CopyVertexData3f(vVerts);
//    // 告诉glut需要更新窗口内容
//    glutPostRedisplay();
//}
//
//int main(int argc,char* argv[]) {
//    //设置当前工作目录，针对MAC OS X
//    gltSetWorkingDirectory(argv[0]);
//    //初始化GLUT库
//    glutInit(&argc, argv);
//    /*初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
//     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区*/
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
//    //GLUT窗口大小，标题窗口
//    glutInitWindowSize(800,600);
//    glutCreateWindow("Triangle");
//    /*
//     GLUT内部运行一个本地消息循环，拦截适当的消息，然后调用我们为不同d时间注册的回调函数。与使用真正的系统特定框架相比有一定的局限性，
//     但是大大简化了组织并运行一个程序的过程，并且支持一个演示框架的最低限度的事件。在这里，我们必须为窗口改变大小设置一个回调函数，
//     以便能够设置视图点，还要注册一个函数以包含OpenGL渲染代码。
//     */
//    //注册回调函数
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutSpecialFunc(SpecialKeys);
//    //初始化GLEW库，重新调用GLEW库初始化OpenGL驱动程序中所有丢失的入口点，以确保OpenGL API对我们来说完全可用。
//    GLenum err = glewInit();
//    //确定驱动程序初始化过程中没有出现任何问题
//    if(GLEW_OK != err) {
//        fprintf(stderr,"glew error:%s\n",glewGetErrorString(err));
//        return 1;
//    }
//    //RC：Rendering Context
//    SetupRC();
//    // 这个函数负责处理所有操作系统特定的消息、按键动作等，直到我们关闭程序为止。
//    glutMainLoop();
//
//    return 0;
//}
//
///*-----------------test1-----------------*/
//void myDisplay(void) {
//    // GL_COLOR_BUFFER_BIT：表示清除颜色，glClear函数还可以清除其他的东西
//    glClear(GL_COLOR_BUFFER_BIT);
//    // 画一个矩形，四个参数分包表示了位于对角线上的两个点的横、纵坐标
//    //    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
//
//    /*
//     GL_POINTS：每个顶点在屏幕上都是一个单独的点
//     GL_LINES：每一对顶点定义了一个线段
//     GL_LINE_STRIP：一个从第一个顶点一次经过每个后续顶点而绘制的线条
//     GL_LINE_LOOP：和GL_LINE_STRIP相同，但是最后一个顶点和第一个顶点也连接起来了
//     GL_TRIANGLES：每3个顶点定义了一个新的三角形
//     GL_TRIANGLE_STRIP：共用一个条带（strip）上的顶点的一组三角形
//     GL_TRIANGLE_FAN：以一个圆点为中心呈扇形排列，共用相邻顶点的一组三角形
//     */
//    glBegin(GL_LINE_LOOP);
//    glVertex2f(-0.5f, -0.5f);
//    glVertex2f(0.5f, -0.5f);
//    glVertex2f(0.5f, 0.5f);
//    glVertex2f(-0.5f, 0.5f);
//    glEnd();
//
//    // 保证前面的OpenGL命令立即执行，而不是让他们在缓冲区里等待
//    glFlush();
//}
//
//const int n = 15;
//const GLfloat R = 0.5f;
//const GLfloat Pi = 3.1415926536f;
//void myDisplay0(void) {
//    int i;
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINE_LOOP);
//    for (i = 0; i < n; i++) {
//        glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
//    }
//    glEnd();
//    glFlush();
//}
//
//void myDisplay1(void) {
//    GLfloat a = 1/(2-2*cos(72*Pi/180));
//    GLfloat bx = a*cos(18*Pi/180);
//    GLfloat by = a*sin(18*Pi/180);
//    GLfloat cy = -a*cos(18*Pi/180);
//    GLfloat PointA[2] = {0, a};
//    GLfloat PointB[2] = {bx, by};
//    GLfloat PointC[2] = {0.5, cy};
//    GLfloat PointD[2] = {-0.5, cy};
//    GLfloat PointE[2] = {-bx, by};
//
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINE_LOOP);
//
//    glVertex2fv(PointA);
//    glVertex2fv(PointC);
//    glVertex2fv(PointE);
//    glVertex2fv(PointB);
//    glVertex2fv(PointD);
//
//    glEnd();
//    glFlush();
//}
//
//void myDisplay2(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINE_LOOP);
//
//    for(int i = 0; i < n; i++) {
//        if (i%2 == 0) {
//            GLfloat point[2] = {R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i)};
//            glVertex2fv(point);
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        if (i % 2 == 1) {
//            GLfloat point[2] = {R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i)};
//            glVertex2fv(point);
//        }
//    }
//
//    glEnd();
//    glFlush();
//}
//
//const GLfloat factor = 0.1f;
//void myDisplay3(void) {
//    GLfloat x;
//
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINES);
//    glVertex2f(-1.0f, 0.0f);
//    glVertex2f(1.0f, 0.0f);
//    glVertex2f(0.0f, -1.0f);
//    glVertex2f(0.0f, 1.0f);
//    glEnd();
//
//    glBegin(GL_LINE_STRIP);
//    for (x= -1.0f/factor; x < 1.0f/factor; x+=0.01f) {
//        glVertex2f(x*factor, sin(x)*factor);
//    }
//    glEnd();
//    glFlush();
//}
//
//void myDisplay4(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINES);
//    glVertex2f(-1.0f, 0.0f);
//    glVertex2f(1.0f, 0.0f);
//    glVertex2f(0.0f, -1.0f);
//    glVertex2f(0.0f, 1.0f);
//    glEnd();
//
//    glBegin(GL_LINE_STRIP);
//    for(GLfloat i = -1.0f/factor; i < 1.0f/factor; i+=0.01f) {
//        glVertex2f(cos(i)*factor, sin(i)*factor);
//    }
//    glEnd();
//    glFlush();
//}
//
//void myDisplay5(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    // 指定点的大小
//    glPointSize(5.0f);
//    glBegin(GL_POINTS);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.5f, 0.5f);
//    glEnd();
//    glFlush();
//}
//
//void myDisplay6(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    // 指定直线的宽度
//    glLineWidth(5.0f);
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.5f, 0.5f);
//    glEnd();
//    glFlush();
//}
//
//void myDisplay7(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    // 启动虚线模式 对应着glDisable
//    glEnable(GL_LINE_STIPPLE);
//    // 设置虚线样式
//    glLineStipple(2, 0xAAAA);
//    glLineWidth(10.0f);
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.5f, 0.5f);
//    glEnd();
//    glFlush();
//}
//
//void myDisplay8(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式
//    glPolygonMode(GL_BACK, GL_LINE); // 设置反面为线性模式
//    glFrontFace(GL_CCW); // 设置逆时针方向为正面
//
//    glBegin(GL_POLYGON); // 按逆时针绘制一个正方形，在左下方
//    glVertex2f(-0.5f, -0.5f);
//    glVertex2f(0.0f, -0.5f);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(-0.5f, 0.0f);
//    glEnd();
//
//    glBegin(GL_POLYGON); // 按顺时针绘制一个正方形，在右上方
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.0f, 0.5f);
//    glVertex2f(0.5f, 0.5f);
//    glVertex2f(0.5f, 0.0f);
//    glEnd();
//
//    glFlush();
//}
//
//void myDisplay9(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    // 启动镂空模式，glDisable：关闭
//    glEnable(GL_POLYGON_STIPPLE);
//    static GLubyte mask[128] =
//    {
//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60, 0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20, 0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20, 0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22, 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC, 0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30, 0x07, 0xE1, 0x87, 0xE0, 0x03, 0x3F, 0xFC, 0xC0, 0x03, 0x31, 0x8C, 0xC0, 0x03, 0x3F, 0xFC, 0xC0, 0x06, 0x64, 0x26, 0x60, 0x0C, 0xCC, 0x33, 0x30, 0x18, 0xCC, 0x33, 0x18, 0x10, 0xC4, 0x23, 0x08, 0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0C, 0x08, 0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
//    };
//    // 设置镂空样式
//    glPolygonStipple(mask);
//    glRectf(-0.5f, -0.5f, 0.0f, 0.0f); // 在左下方绘制一个有镂空效果的正方形
//    glDisable(GL_POLYGON_STIPPLE);
//    glRectf(0.0f, 0.0f, 0.5f, 0.5f); // 在右上方绘制一个没有镂空效果的正方形
//    glFlush();
//}
//
//void myDisplay10(void) {
//    static GLubyte mask[128];
//    FILE *fp;
//    fp = fopen("mask.bmp", "rb");
//    if (!fp) {
//        exit(0);
//    }
//    if (fseek(fp, -(int)sizeof(mask), SEEK_END)) {
//        exit(0);
//    }
//    if (!fread(mask, sizeof(mask), 1, fp)) {
//        exit(0);
//    }
//    fclose(fp);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glEnable(GL_POLYGON_STIPPLE);
//    glPolygonStipple(mask);
//    glRectf(-0.5f, -0.5f, 0.0f, 0.0f);
//    glDisable(GL_POLYGON_STIPPLE);
//    glRectf(0.0f, 0.0f, 0.5f, 0.5f);
//    glFlush();
//}
//
//void myDisplay11(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    // glColor3f(0.0f, 1.0f, 1.0f);
//    glColor3ub(0, 255, 255);
//    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
//    glFlush();
//}
//
//void myDisplay12(void) {
//    // 指定清除屏幕用的颜色
//    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glFlush();
//}
//
//void myDisplay13(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_TRIANGLE_FAN);
//    //    glShadeModel(GL_SMOOTH);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    int n = 8;
//    for(int i = 0; i < n; i++) {
//        glColor3f(i&0x04, i&0x02, i&0x01);
//        glVertex2f(cos(i*Pi/n*2), sin(i*Pi/n*2));
//    }
//    glEnd();
//    glFlush();
//}
//
//double calFrequency() {
//    static int count;
//    static double save;
//    static clock_t last, current;
//    double timegap;
//
//    ++count;
//    if(count <= 50) {
//        return save;
//    }
//    count = 0;
//    last = current;
//    current = clock();
//    timegap = (current-last)/(double)CLOCKS_PER_SEC;
//    save = 50.0/timegap;
//    return save;
//}
//
//static int day = 300;
//void myDisplay14(void) {
//    double FPS = calFrequency();
//    //    printf("FPS = %f\n", FPS);
//    glEnable(GL_DEPTH_TEST);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(75, 1, 1, 400000000);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
//
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glutSolidSphere(69600000, 20, 20);
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(150000000, 0.0f, 0.0f);
//    glutSolidSphere(15945000, 20, 20);
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glRotatef(day/30.0*360.0-day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(38000000, 0.0f, 0.0f);
//    glutSolidSphere(4345000, 20, 20);
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//void myIdle(void) {
//    // 在空闲时间调用，作用是把日期往后移动一天并重新绘制，达到动画效果
//    ++day;
//    if(day >= 360) {
//        day = 0;
//    }
//    myDisplay14();
//}
//
///**
// glut：OpenGL utility toolkit(用来隐藏平台相关细节）
// 以glut开头的函数都是glut工具包所提供的函数
// 以gl开头的函数都是OpenGL的标准函数
// */
//int main2(int argc,char* argv[]) {
//    gltSetWorkingDirectory(argv[0]);
//
//    // 对GLUT进行初始化，这个函数必须在其他GLUT使用之前调用一次
//    glutInit(&argc, argv);
//
//    /** 设置显示方式
//     GLUT_RGB：使用RGB颜色，
//     GLUT_INDEX：使用索引颜色，
//     GLUT_SINGLE：使用单缓冲，
//     GLUT_DOUBLE：使用双缓冲
//     */
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//    // 设置窗口在屏幕中的位置
//    glutInitWindowPosition(100, 100);
//    // 设置窗口的大小
//    glutInitWindowSize(400, 400);
//    // 设置标题
//    glutCreateWindow("第一个OpenGL程序");
//    // 设置一个函数，当需要进行画图时，这个函数就会被调用
//    glutDisplayFunc(&myDisplay14);
//    glutIdleFunc(&myIdle);
//    // 进行一个消息循环
//    glutMainLoop();
//
//    return 0;
//}
//
///*
// GLboolean GLbyte GLubtye GLchar GLshort GLushort GLhalf GLint GLuint GLsizei GLenum GLfloat GLclampf GLbitfield GLdouble GLclampd Glint64 Gluint64 GLsizeiptr GLintptr GLsync
// */
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
