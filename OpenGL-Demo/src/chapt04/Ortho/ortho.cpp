#include <GLTools.h>
#include <glut/glut.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void ChangeSize(int w, int h)
{
    GLfloat nRange = 120.0f;
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h) {
        glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);
    } else {
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC()
{
    GLfloat whiteLight[] = {0.45f, 0.45f, 0.45f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-50.0f, 25.0f, 250.0f, 0.0f};
    
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_LIGHTING);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP: xRot -= 5.0f; break;
        case GLUT_KEY_DOWN: xRot += 5.0f; break;
        case GLUT_KEY_LEFT: yRot -= 5.0f; break;
        case GLUT_KEY_RIGHT: yRot += 5.0f; break;
    }
    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);
    glutPostRedisplay();
}

void RenderScene(void)
{
    float fZ, bZ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fZ = 100.0f;
    bZ = -100.0f;
    
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
    
        // Left Panel
        glVertex3f(-50.0f, 50.0f, fZ);
        glVertex3f(-50.0f, -50.0f, fZ);
        glVertex3f(-35.0f, -50.0f, fZ);
        glVertex3f(-35.0f,50.0f,fZ);
    
        // Right Panel
        glVertex3f(50.0f, 50.0f, fZ);
        glVertex3f(35.0f, 50.0f, fZ);
        glVertex3f(35.0f, -50.0f, fZ);
        glVertex3f(50.0f,-50.0f,fZ);
    
        // Top Panel
        glVertex3f(-35.0f, 50.0f, fZ);
        glVertex3f(-35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 50.0f,fZ);
    
        // Bottom Panel
        glVertex3f(-35.0f, -35.0f, fZ);
        glVertex3f(-35.0f, -50.0f, fZ);
        glVertex3f(35.0f, -50.0f, fZ);
        glVertex3f(35.0f, -35.0f,fZ);
    
    // Top length section ////////////////////////////
    // Normal points up Y axis
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-50.0f, 50.0f, fZ);
    glVertex3f(50.0f, 50.0f, fZ);
    glVertex3f(50.0f, 50.0f, bZ);
    glVertex3f(-50.0f,50.0f,bZ);
    
    // Bottom section
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, fZ);
    glVertex3f(-50.0f, -50.0f, bZ);
    glVertex3f(50.0f, -50.0f, bZ);
    glVertex3f(50.0f, -50.0f, fZ);
    
    // Left section
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 50.0f, fZ);
    glVertex3f(50.0f, -50.0f, fZ);
    glVertex3f(50.0f, -50.0f, bZ);
    glVertex3f(50.0f, 50.0f, bZ);
    
    // Right Section
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f, 50.0f, fZ);
    glVertex3f(-50.0f, 50.0f, bZ);
    glVertex3f(-50.0f, -50.0f, bZ);
    glVertex3f(-50.0f, -50.0f, fZ);
    glEnd();
    
    glFrontFace(GL_CW);
    
    glBegin(GL_QUADS);
    // Back section
    // Pointing straight out Z
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    // Left Panel
    glVertex3f(-50.0f, 50.0f, bZ);
    glVertex3f(-50.0f, -50.0f, bZ);
    glVertex3f(-35.0f, -50.0f, bZ);
    glVertex3f(-35.0f,50.0f,bZ);
    
    // Right Panel
    glVertex3f(50.0f, 50.0f, bZ);
    glVertex3f(35.0f, 50.0f, bZ);
    glVertex3f(35.0f, -50.0f, bZ);
    glVertex3f(50.0f,-50.0f,bZ);
    
    // Top Panel
    glVertex3f(-35.0f, 50.0f, bZ);
    glVertex3f(-35.0f, 35.0f, bZ);
    glVertex3f(35.0f, 35.0f, bZ);
    glVertex3f(35.0f, 50.0f,bZ);
    
    // Bottom Panel
    glVertex3f(-35.0f, -35.0f, bZ);
    glVertex3f(-35.0f, -50.0f, bZ);
    glVertex3f(35.0f, -50.0f, bZ);
    glVertex3f(35.0f, -35.0f,bZ);
    
    // Insides /////////////////////////////
    glColor3f(0.75f, 0.75f, 0.75f);
    
    // Normal points up Y axis
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-35.0f, 35.0f, fZ);
    glVertex3f(35.0f, 35.0f, fZ);
    glVertex3f(35.0f, 35.0f, bZ);
    glVertex3f(-35.0f,35.0f,bZ);
    
    // Bottom section
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-35.0f, -35.0f, fZ);
    glVertex3f(-35.0f, -35.0f, bZ);
    glVertex3f(35.0f, -35.0f, bZ);
    glVertex3f(35.0f, -35.0f, fZ);
    
    // Left section
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-35.0f, 35.0f, fZ);
    glVertex3f(-35.0f, 35.0f, bZ);
    glVertex3f(-35.0f, -35.0f, bZ);
    glVertex3f(-35.0f, -35.0f, fZ);
    
    // Right Section
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(35.0f, 35.0f, fZ);
    glVertex3f(35.0f, -35.0f, fZ);
    glVertex3f(35.0f, -35.0f, bZ);
    glVertex3f(35.0f, 35.0f, bZ);
    glEnd();
    
    glFrontFace(GL_CCW);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Orthographic Projection");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}


















