//#include "GLTools.h"    // OpenGL toolkit
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//#include "math3d.h"
//#include <math.h>
//
//int nStep = 0;
//
//GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
//GLfloat lightDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
//GLfloat lightSpecular[] = {0.9f, 0.9f, 0.9f};
//GLfloat materialColor[] = {0.8f, 0.0f, 0.0f};
//GLfloat vLightPos[] = {-80.0f, 120.0f, 100.0f, 0.0f};
//GLfloat ground[3][3] = {{0.0f, -25.0f, 0.0f},
//    {10.0f, -25.0f, 0.0f},
//    {10.0f, -25.0f, -10.0f}};
//
//GLuint textures[4];
//
//void RenderScene(void)
//{
//    M3DMatrix44f mCubeTransform;
//    M3DVector4f pPlane;
//    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    // 设置着色模式
//    glShadeModel(GL_SMOOTH);
//    // 使用opengl自动单位化法向量
//    glEnable(GL_NORMALIZE);
//    // 将当前变换矩阵压入堆栈
//    glPushMatrix();
//    glDisable(GL_LIGHTING);
//    if (nStep == 5) {
//        glColor3ub(255, 255, 255);
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, textures[0]);
//        glBegin(GL_QUADS);
//        // 指定纹理坐标
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(-100.0f, -25.3f, -100.0f);
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-100.0f, -25.3f, 100.0f);
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(100.0f, -25.3f, 100.0f);
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(100.0f, -25.3f, -100.0f);
//        glEnd();
//    } else {
//        glColor3f(0.0f, 0.0f, 0.90f);
//        glBegin(GL_QUADS);
//        glVertex3f(-100.0f, -25.3f, -100.0f);
//        glVertex3f(-100.0f, -25.3f, 100.0f);
//        glVertex3f(100.0f, -25.3f, 100.0f);
//        glVertex3f(100.0f, -25.3f, -100.0f);
//        glEnd();
//    }
//    glColor3f(1.0f, 0.0f, 0.0f);
//    if (nStep > 2) {
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LEQUAL);
//        glEnable(GL_COLOR_MATERIAL);
//        
//        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
//        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
//        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
//        glEnable(GL_LIGHTING);
//        glEnable(GL_LIGHT0);
//        glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpecular);
//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
//        glMateriali(GL_FRONT, GL_SHININESS, 128);
//    }
//    glTranslatef(-10.0f, 0.0f, 10.0f);
//    switch (nStep) {
//        case 0:
//            glutWireCube(50.0f);
//            break;
//        case 1:
//            glBegin(GL_LINES);
//            glVertex3f(25.0f, 25.0f, 25.0f);
//            glVertex3f(25.0f, -25.0f, 25.0f);
//            
//            glVertex3f(25.0f,-25.0f,25.0f);
//            glVertex3f(-25.0f,-25.0f,25.0f);
//            
//            glVertex3f(-25.0f,-25.0f,25.0f);
//            glVertex3f(-25.0f,25.0f,25.0f);
//            
//            glVertex3f(-25.0f,25.0f,25.0f);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glEnd();
//            glBegin(GL_LINES);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glVertex3f(25.0f,25.0f,-25.0f);
//            
//            glVertex3f(25.0f,25.0f,-25.0f);
//            glVertex3f(-25.0f,25.0f,-25.0f);
//            
//            glVertex3f(-25.0f,25.0f,-25.0f);
//            glVertex3f(-25.0f,25.0f,25.0f);
//            
//            glVertex3f(-25.0f,25.0f,25.0f);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glEnd();
//            glBegin(GL_LINES);
//            glVertex3f(25.0f,25.0f,-25.0f);
//            glVertex3f(25.0f,-25.0f,-25.0f);
//            
//            glVertex3f(25.0f,-25.0f,-25.0f);
//            glVertex3f(25.0f,-25.0f,25.0f);
//            glEnd();
//            break;
//        case 2:
//            glutSolidCube(50.0f);
//            break;
//        case 3:
//            glutSolidCube(50.0f);
//            break;
//        case 4:
//            glGetFloatv(GL_MODELVIEW_MATRIX, mCubeTransform);
//            glutSolidCube(50.0f);
//            glPopMatrix();
//            glDisable(GL_LIGHTING);
//            glPushMatrix();
//            m3dGetPlaneEquation(pPlane, ground[0], ground[1], ground[2]);
//            m3dMakePlanarShadowMatrix(mCubeTransform, pPlane, vLightPos);
//            glMultMatrixf(mCubeTransform);
//            glTranslatef(-10.0f, 0.0f, 10.0f);
//            glColor3f(0.0f, 0.0f, 0.0f);
//            glutSolidCube(50.0f);
//            break;
//        case 5:
//            glColor3ub(255, 255, 255);
//            glGetFloatv(GL_MODELVIEW_MATRIX, mCubeTransform);
//            // Front Face (before rotation)
//            glBindTexture(GL_TEXTURE_2D, textures[1]);
//            glBegin(GL_QUADS);
//            glTexCoord2f(1.0f, 1.0f);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glTexCoord2f(1.0f, 0.0f);
//            glVertex3f(25.0f,-25.0f,25.0f);
//            glTexCoord2f(0.0f, 0.0f);
//            glVertex3f(-25.0f,-25.0f,25.0f);
//            glTexCoord2f(0.0f, 1.0f);
//            glVertex3f(-25.0f,25.0f,25.0f);
//            glEnd();
//            
//            // Top of cube
//            glBindTexture(GL_TEXTURE_2D, textures[2]);
//            glBegin(GL_QUADS);
//            // Front Face
//            glTexCoord2f(0.0f, 0.0f);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glTexCoord2f(1.0f, 0.0f);
//            glVertex3f(25.0f,25.0f,-25.0f);
//            glTexCoord2f(1.0f, 1.0f);
//            glVertex3f(-25.0f,25.0f,-25.0f);
//            glTexCoord2f(0.0f, 1.0f);
//            glVertex3f(-25.0f,25.0f,25.0f);
//            glEnd();
//            
//            // Last two segments for effect
//            glBindTexture(GL_TEXTURE_2D, textures[3]);
//            glBegin(GL_QUADS);
//            glTexCoord2f(1.0f, 1.0f);
//            glVertex3f(25.0f,25.0f,-25.0f);
//            glTexCoord2f(1.0f, 0.0f);
//            glVertex3f(25.0f,-25.0f,-25.0f);
//            glTexCoord2f(0.0f, 0.0f);
//            glVertex3f(25.0f,-25.0f,25.0f);
//            glTexCoord2f(0.0f, 1.0f);
//            glVertex3f(25.0f,25.0f,25.0f);
//            glEnd();
//            
//            glPopMatrix();
//            
//            glDisable(GL_LIGHTING);
//            glDisable(GL_TEXTURE_2D);
//            
//            glPushMatrix();
//            
//            m3dGetPlaneEquation(pPlane, ground[0], ground[1], ground[2]);
//            m3dMakePlanarShadowMatrix(mCubeTransform, pPlane, vLightPos);
//            glMultMatrixf(mCubeTransform);
//            
//            glTranslatef(-10.0f, 0.0f, 10.0f);
//            
//            glColor3f(0.0f, 0.0f, 0.0f);
//            glutSolidCube(50.0f);
//            break;
//    }
//    glPopMatrix();
//    glutSwapBuffers();
//}
//
//void SetupRC()
//{
//    GLbyte *pBytes;
//    GLint nWidth, nHeight, nComponents;
//    GLenum format;
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    // 设置当前纹理映射方式
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    // 用来生成纹理的函数。函数根据纹理参数返回n个纹理索引
//    glGenTextures(4, textures);
//    
//    const char* iamges[4] = {"floor.tga", "Block4.tga", "block5.tga", "block6.tga"};
//    for (int i = 0; i < 4; i++) {
//        pBytes = gltReadTGABits(iamges[i], &nWidth, &nHeight, &nComponents, &format);
//        glBindTexture(GL_TEXTURE_2D, textures[i]);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, format, GL_UNSIGNED_BYTE, pBytes);
//        free(pBytes);
//    }
//}
//
//void KeyPressFunc(unsigned char key, int x, int y)
//{
//    if (key == 32) {
//        nStep++;
//        if (nStep > 5) {
//            nStep = 0;
//        }
//    }
//    glutPostRedisplay();
//}
//
//void ChangeSize(int w, int h)
//{
//    GLfloat windowWidth;
//    GLfloat windowHeight;
//    if (h == 0) {
//        h = 1;
//    }
//    if (w <= h) {
//        windowHeight = 100.0f * (GLfloat)h/(GLfloat)w;
//        windowWidth = 100.0f;
//    } else {
//        windowWidth = 100.0f * (GLfloat)w/(GLfloat)h;
//        windowHeight = 100.0f;
//    }
//    glViewport(0, 0, w, h);
//    // 对接下来要做什么进行一下声明，GL_PROJECTION:投影，GL_MODEVIEW:模型视图，GL_TEXTURE:纹理
//    glMatrixMode(GL_PROJECTION);
//    // 恢复初始坐标系
//    glLoadIdentity();
//    // 创建一个正交平行的视景体。一般用于物体不会因为离屏幕远近而产生大小的变换情况。
//    glOrtho(-100.0f, windowWidth, -100.0f, windowHeight, -200.0f, 200.0f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glLightfv(GL_LIGHT0, GL_POSITION, vLightPos);
//    // 使用一个旋转矩阵乘以当前矩阵
//    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(330.0f, 0.0f, 1.0f, 0.0f);
//}
//
//int main(int argc, char* argv[])
//{
//    gltSetWorkingDirectory(argv[0]);
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("3D Effects Demo");
//    glutReshapeFunc(ChangeSize);
//    glutKeyboardFunc(KeyPressFunc);
//    glutDisplayFunc(RenderScene);
//    
//    SetupRC();
//    
//    glutMainLoop();
//    glDeleteTextures(4, textures);
//    
//    return 0;
//}
//
