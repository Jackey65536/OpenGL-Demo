/*
 #include <GLTools.h>
 #include <glut/glut.h>
 #include <math.h>
 
 #define GL_PI 3.1415f
 
 static GLfloat xRot = 0.0f;
 static GLfloat yRot = 0.0f;
 
 int iCull = 0;
 int iOutline = 0;
 int iDepth = 0;
 
 void ProcessMenu(int value)
 {
 switch (value) {
 case 1:
 iDepth = !iDepth;
 break;
 case 2:
 iCull = !iCull;
 break;
 case 3:
 iOutline = !iOutline;
 break;
 }
 // 标记当前窗口需要重新绘制
 glutPostRedisplay();
 }
 
 void RenderScene(void)
 {
 GLfloat x, y, angle;
 int iPivot = 1;
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 if (iCull) {
 glEnable(GL_CULL_FACE);
 } else {
 glDisable(GL_CULL_FACE);
 }
 if (iDepth) {
 glEnable(GL_DEPTH_TEST);
 } else {
 glDisable(GL_DEPTH_TEST);
 }
 if (iOutline) {
 // 背面用线显示
 glPolygonMode(GL_BACK, GL_LINE);
 } else {
 // 背面填充显示
 glPolygonMode(GL_BACK, GL_FILL);
 }
 // Save matrix state and do the rotation
 glPushMatrix();
 glRotatef(xRot, 1.0f, 0.0f, 0.0f);
 glRotatef(yRot, 0.0f, 1.0f, 0.0f);
 // 以一个圆点为中心呈扇形排列，共用相邻顶点的一组三角形
 glBegin(GL_TRIANGLE_FAN);
 
 //z轴上移形成锥形顶点
 glVertex3f(0.0f, 0.0f, 75.0f);
 for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
 x = 50.0f * sin(angle);
 y = 50.0f * cos(angle);
 if (iPivot%2 == 0) {
 glColor3f(0.0f, 1.0f, 0.0f);
 } else {
 glColor3f(1.0f, 0.0f, 0.0f);
 }
 iPivot++;
 glVertex2f(x, y);
 }
 glEnd();
 
 // 底部三角形扇区
 glBegin(GL_TRIANGLE_FAN);
 glVertex3f(0.0f, 0.0f, 0.0f);
 for (angle = 0.0f; angle < 2.0f*GL_PI; angle += (GL_PI/8.0f)) {
 x = 50.0f * sin(angle);
 y = 50.0f * cos(angle);
 
 //        x = 50.0f * cos(angle);
 //        y = 50.0f * sin(angle);
 
 if (iPivot%2 == 0) {
 glColor3f(0.0f, 1.0f, 0.0f);
 } else {
 glColor3f(1.0f, 0.0f, 0.0f);
 }
 iPivot++;
 glVertex2f(x, y);
 }
 glEnd();
 glPopMatrix();
 glutSwapBuffers();
 }
 
 void SetupRC()
 {
 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 glColor3f(0.0f, 1.0f, 0.0f);
 // 设置颜色着色模型
 glShadeModel(GL_FLAT);
 // 设置顶点顺序顺时针方向的表面为正面
 glFrontFace(GL_CW);
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
 // Refresh the window
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
 // 建立剪裁音量（左，右，下，上，近，远)
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
 glutCreateWindow("Triangle Culling Example");
 
 glutCreateMenu(ProcessMenu);
 glutAddMenuEntry("Toggle depth test", 1);
 glutAddMenuEntry("Toggle cull backface", 2);
 glutAddMenuEntry("Toggle outline back", 3);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 glutReshapeFunc(ChangeSize);
 glutSpecialFunc(SpecialKeys);
 glutDisplayFunc(RenderScene);
 SetupRC();
 glutMainLoop();
 return 0;
 }

 */
