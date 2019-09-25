#include <GLTools.h>
#include <glut/glut.h>
#include <GLFrame.h>
#include <math3d.h>
#include <math.h>

#define NUM_SPHERES 50

namespace Ch04 {
    namespace SphereWorld {
        GLFrame spheres[NUM_SPHERES];
        GLFrame frameCamera;
        
        void SetupRC()
        {
            // 设置背景颜色为浅蓝色
            glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
            // 用线段来画图形
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
            // 随机放置球体
            for (int iSphere = 0; iSphere < NUM_SPHERES; iSphere++) {
                float x = (rand() % 400 - 200) * 0.1f;
                float z = (rand() % 400 - 200) * 0.1f;
                // 设置图形原点位置
                spheres[iSphere].SetOrigin(x, 0.0f, z);
            }
        }
        
        void DrawGround(void)
        {
            GLfloat fExtent = 20.0f;
            GLfloat fStep = 1.0f;
            GLfloat y = -0.4f;
            
            glBegin(GL_LINES);
            for (GLint iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
                glVertex3f(iLine, y, fExtent);
                glVertex3f(iLine, y, -fExtent);
                
                glVertex3f(fExtent, y, iLine);
                glVertex3f(-fExtent, y, iLine);
            }
            glEnd();
        }
        
        void gltDrawTorus(GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor)
        {
            M3DVector3f vNormal;
            double majorStep = 2.0f*M3D_PI / numMajor;
            double minorStep = 2.0f*M3D_PI / numMinor;
            int i, j;
            
            for (i=0; i<numMajor; ++i)
            {
                double a0 = i * majorStep;
                double a1 = a0 + majorStep;
                GLfloat x0 = (GLfloat) cos(a0);
                GLfloat y0 = (GLfloat) sin(a0);
                GLfloat x1 = (GLfloat) cos(a1);
                GLfloat y1 = (GLfloat) sin(a1);
                
                glBegin(GL_TRIANGLE_STRIP);
                for (j=0; j<=numMinor; ++j)
                {
                    double b = j * minorStep;
                    GLfloat c = (GLfloat) cos(b);
                    GLfloat r = minorRadius * c + majorRadius;
                    GLfloat z = minorRadius * (GLfloat) sin(b);
                    
                    // First point
                    glTexCoord2f((float)(i)/(float)(numMajor), (float)(j)/(float)(numMinor));
                    vNormal[0] = x0*c;
                    vNormal[1] = y0*c;
                    vNormal[2] = z/minorRadius;
                    m3dNormalizeVector3(vNormal);
                    glNormal3fv(vNormal);
                    glVertex3f(x0*r, y0*r, z);
                    
                    glTexCoord2f((float)(i+1)/(float)(numMajor), (float)(j)/(float)(numMinor));
                    vNormal[0] = x1*c;
                    vNormal[1] = y1*c;
                    vNormal[2] = z/minorRadius;
                    m3dNormalizeVector3(vNormal);
                    glNormal3fv(vNormal);
                    glVertex3f(x1*r, y1*r, z);
                }
                glEnd();
            }
        }
        
        void RenderScene(void)
        {
            static GLfloat yRot = 0.0f;
            yRot += 0.5f;
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glPushMatrix();
            frameCamera.ApplyCameraTransform();
            
            // 绘制背景
            DrawGround();
            
            for (int i = 0; i < NUM_SPHERES; i++) {
                glPushMatrix();
                spheres[i].ApplyActorTransform();
                glutSolidSphere(0.1f, 13, 26);
                glPopMatrix();
            }
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, -2.5f);
            
            glPushMatrix();
            glRotatef(-yRot*2.0f, 0.0f, 1.0f, 0.0f);
            glTranslatef(1.0f, 0.0f, 0.0f);
            glutSolidSphere(0.1f, 13, 26);
            glPopMatrix();
            
            glRotatef(yRot, 0.0f, 1.0f, 0.0f);
            gltDrawTorus(0.35, 0.15, 40, 20);
            //    glutSolidTorus(0.15, 0.35, 20, 40);
            //    glutWireTorus(0.15, 0.35, 40, 20);
            glPopMatrix();
            glPopMatrix();
            
            glutSwapBuffers();
        }
        
        // 移动照相机参考帧来对方向键做出响应
        void SpecialKeys(int key, int x, int y)
        {
            switch (key) {
                case GLUT_KEY_UP: frameCamera.MoveForward(0.1f); break;
                case GLUT_KEY_DOWN: frameCamera.MoveForward(-0.1f); break;
                case GLUT_KEY_LEFT: frameCamera.RotateLocalY(0.1f); break;
                case GLUT_KEY_RIGHT: frameCamera.RotateLocalY(-0.1f); break;
            }
            glutPostRedisplay();
        }
        
        void TimerFunction(int value)
        {
            glutPostRedisplay();
            glutTimerFunc(3, TimerFunction, 1);
        }
        
        void ChangeSize(int w, int h)
        {
            GLfloat fAspect;
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            
            fAspect = (GLfloat)w/(GLfloat)h;
            gluPerspective(35.0f, fAspect, 1.0f, 50.0f);
            
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        
        int main(int argc, char* argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutInitWindowSize(800, 600);
            glutCreateWindow("OpenGL SphereWorld Demo");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            glutSpecialFunc(SpecialKeys);
            SetupRC();
            glutTimerFunc(33, TimerFunction, 1);
            glutMainLoop();
            return 0;
        }
    }
}
