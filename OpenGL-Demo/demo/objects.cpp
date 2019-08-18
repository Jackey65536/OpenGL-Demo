#include <GLTools.h>
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <glut/glut.h>
#include <math.h>

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLFrame cameraFrame;
GLFrame objectFrame;
GLFrustum viewFrustum;

GLTriangleBatch sphereBatch;
GLTriangleBatch torusBatch;
GLTriangleBatch cylinderBatch;
GLTriangleBatch coneBatch;
GLTriangleBatch diskBatch;

GLGeometryTransform transformPipleline;
GLfloat vGreen[] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat vBlack[] = {0.0f, 0.0f, 0.0f, 1.0f};

int nStep = 0;

void SetupRC()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    shaderManager.InitializeStockShaders();
    glEnable(GL_DEPTH_TEST);
    // 设置变换管线，管理模型视图堆栈和投影堆栈
    transformPipleline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    // 照相机位置往后移动15
    cameraFrame.MoveForward(-15.0f);
    
    // 初始化球体的三角形批次，后面参数依次是，球半径、片段数、堆叠数
    gltMakeSphere(sphereBatch, 3.0f, 10, 20);
    
    // 初始化花托的三角形批次，后面参数依次是，外半径，内半径，片段数，堆叠数
    gltMakeTorus(torusBatch, 3.0f, 0.75f, 150, 15);
    
    // 初始化圆柱的三角形批次，后面参数依次是，底部半径，顶部半径，高度，片段数，堆叠数
    gltMakeCylinder(cylinderBatch, 2.0f, 2.0f, 3.0f, 13, 2);
    
    // 初始化圆锥三角形批次，后面参数依次是，底部半径，顶部半径，高度，片段数，堆叠数
    gltMakeCylinder(coneBatch, 2.0f, 0.0f, 3.0f, 13, 2);
    
    // 初始化圆盘的三角形批次，后面的参数依次是，内半径，外半径，片段数，堆叠数
    gltMakeDisk(diskBatch, 1.5f, 3.0f, 13, 3);
}

// 画三角批次共用方法
void DrawWireFramedBatch(GLTriangleBatch* pBatch)
{
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipleline.GetModelViewProjectionMatrix(), vGreen);
    pBatch->Draw();
    
    glPolygonOffset(-1.0f, -1.0f);
    // 开启线段的抗锯齿
    glEnable(GL_LINE_SMOOTH);
    // 开启混合颜色模式
    glEnable(GL_BLEND);
    // 设置混合方程式
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 设置多边形模式为线段
    glEnable(GL_POLYGON_OFFSET_LINE);
    // 设置多边形模式前后面为线段
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5f);
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipleline.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();
    
    // 还原渲染环境
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1.0f);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // 模型堆栈压栈，顶部是单位矩阵
    modelViewMatrix.PushMatrix();
    
    // 获取照相机位置矩阵
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    
    // 单位矩阵 x 照相机位置矩阵 = 照相机位置矩阵
    modelViewMatrix.MultMatrix(mCamera);
    
    // 获取物体位置矩阵
    M3DMatrix44f mObjectFrame;
    objectFrame.GetMatrix(mObjectFrame);
    
    // 照相机位置矩阵 x 物体位置矩阵 = 物体在照相机下的位置矩阵
    modelViewMatrix.MultMatrix(mObjectFrame);
    
    // 设置着色器为黑色
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipleline.GetModelViewProjectionMatrix(), vBlack);
    
    switch (nStep) {
        case 0: DrawWireFramedBatch(&sphereBatch); break;
        case 1: DrawWireFramedBatch(&torusBatch); break;
        case 2: DrawWireFramedBatch(&cylinderBatch); break;
        case 3: DrawWireFramedBatch(&coneBatch); break;
        case 4: DrawWireFramedBatch(&diskBatch); break;
    }
    
    // 出栈，还原栈顶为单位矩阵
    modelViewMatrix.PopMatrix();
    glutSwapBuffers();
}

// 特殊按键点击响应
void SpecialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            // 绕x轴正方向顺时针旋转
            objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
            break;
        case GLUT_KEY_DOWN:
            // 绕x轴正方向逆时针旋转
            objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
            break;
        case GLUT_KEY_LEFT:
            // 绕y轴正方向顺时针旋转
            objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
            break;
        case GLUT_KEY_RIGHT:
            // 绕y轴正方向逆时针旋转
            objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
            break;
    }
    glutPostRedisplay();
}

// 普通按键点击响应
void KeyPressFunc(unsigned char key, int x, int y)
{
    if (key == 32) {
        nStep = (nStep + 1) % 5;
    }
    // 切换窗口标题
    switch(nStep) {
        case 0: glutSetWindowTitle("Sphere"); break;
        case 1: glutSetWindowTitle("Torus"); break;
        case 2: glutSetWindowTitle("Cylinder"); break;
        case 3: glutSetWindowTitle("Cone"); break;
        case 4: glutSetWindowTitle("Disk"); break;
    }
    
    // 触发渲染
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    
    // 设置投影矩阵，参数：投影视角，宽高比，近点距离，远点距离
    viewFrustum.SetPerspective(35.0f, (GLfloat)w/(GLfloat)h, 1.0f, 500.0f);
    
    // 投影矩阵堆栈顶部载入当前奢姿的投影矩阵
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // 模型矩阵堆栈载入单位矩阵
    modelViewMatrix.LoadIdentity();
    
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sphere");
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyPressFunc);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}


























