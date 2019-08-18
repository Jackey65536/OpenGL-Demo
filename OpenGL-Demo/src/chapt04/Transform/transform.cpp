/*
 #include "GLTools.h"
 #include <glut/glut.h>
 #include "math3d.h"
 #include <math.h>
 
 // 定义一个圆环面
 void DrawTorus(M3DMatrix44f mTransform)
 {
 GLfloat majorRadius = 0.35f; // 内环半径+环半径
 GLfloat minorRadius = 0.15f; // 环半径
 GLint numMajor = 40; // 圆圈的顶点数
 GLint numMinor = 20; // 圆圈数量
 M3DVector3f objectVertex;
 M3DVector3f transformedVertex;
 double majorStep = M3D_2PI / numMajor;
 double minorStep = M3D_2PI / numMinor;
 for (int i = 0; i < numMajor; ++i) {
 double a0 = i * majorStep;
 double a1 = (i + 1) * majorStep;
 GLfloat x0 = (GLfloat)cos(a0);
 GLfloat y0 = (GLfloat)sin(a0);
 GLfloat x1 = (GLfloat)cos(a1);
 GLfloat y1 = (GLfloat)sin(a1);
 
 glBegin(GL_TRIANGLE_STRIP);
 //        glBegin(GL_LINES);
 for (int j = 0; j <= numMinor; ++j) {
 double b = j * minorStep;
 GLfloat c = (GLfloat)cos(b);
 GLfloat r = minorRadius * c + majorRadius;
 GLfloat z = minorRadius * (GLfloat)sin(b);
 
 objectVertex[0] = x0 * r;
 objectVertex[1] = y0 * r;
 objectVertex[2] = z;
 // 执行顶点变换操作
 // transformedVertex：变换后的顶点坐标，包含3个元素的一维数组
 // objectVertex：原始顶点坐标，包含3个元素的一维数组
 // mTransform：变换矩阵
 m3dTransformVector3(transformedVertex, objectVertex, mTransform);
 glVertex3fv(transformedVertex);
 
 objectVertex[0] = x1 * r;
 objectVertex[1] = y1 * r;
 objectVertex[2] = z;
 m3dTransformVector3(transformedVertex, objectVertex, mTransform);
 glVertex3fv(transformedVertex);
 }
 glEnd();
 }
 }
 
 void RenderScene(void)
 {
 // 创建一个包含16个元素的一维数组
 M3DMatrix44f transformationMatrx;
 
 static GLfloat yRot = 0.0f;
 yRot += 0.5f;
 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
 // 创建一个绕y轴旋转的矩阵
 m3dRotationMatrix44(transformationMatrx, m3dDegToRad(yRot), 0.0f, 1.0f, 0.0f);
 // 指定位移向量，变换矩阵的第四列
 transformationMatrx[12] = 0.0f;
 transformationMatrx[13] = 0.0f;
 transformationMatrx[14] = -2.5f;
 
 // 画一个圆环面，根据创建的旋转矩阵，变换圆环面上的各个顶点
 DrawTorus(transformationMatrx);
 glutSwapBuffers();
 }
 
 void SetupRc()
 {
 glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
 //    glColor3f(0.6f, 0.0f, 0.0f);
 //以线框的方式画所有物体
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 }
 
 void TimerFunction(int value)
 {
 glutPostRedisplay();
 // 每33ms调用一次RenderScene
 glutTimerFunc(33, TimerFunction, 1);
 }
 
 void ChangeSize(int w, int h)
 {
 GLfloat fAspect;
 if (h == 0) {
 h = 1;
 }
 glViewport(0, 0, w, h);
 fAspect = (GLfloat)w / (GLfloat)h;
 
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 
 gluPerspective(35.0f, fAspect, 1.0f, 50.0f);
 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 }
 
 int main(int argc, char* argv[])
 {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutCreateWindow("Manual Transformations Demo");
 glutReshapeFunc(ChangeSize);
 glutDisplayFunc(RenderScene);
 glutTimerFunc(33, TimerFunction, 1);
 SetupRc();
 glutMainLoop();
 return 0;
 }

 */
