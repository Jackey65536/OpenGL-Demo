//#include <GLTools.h>
//#include <GLShaderManager.h>
//#include <math3d.h>
//#include <glut/glut.h>
//
//GLBatch squareBatch;
//GLShaderManager shaderManager;
//
//GLfloat blockSize = 0.1f;
//GLfloat xPos = 0.0f;
//GLfloat yPos = 0.0f;
//
//// 矩形4个顶点坐标
//GLfloat vVerts[] = {
//    -blockSize, -blockSize, 0.0f,
//    blockSize, -blockSize, 0.0f,
//    blockSize, blockSize, 0.0f,
//    -blockSize, blockSize, 0.0f,
//};
//
//// 初始化环境
//void SetupRC()
//{
//    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//    shaderManager.InitializeStockShaders();
//    
//    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
//    squareBatch.CopyVertexData3f(vVerts);
//    squareBatch.End();
//}
//
//void SpecialKeys(int key, int x, int y)
//{
//    GLfloat stepSize = 0.025f;
//    // 4个方向位置偏移
//    if(key == GLUT_KEY_UP) yPos += stepSize;
//    if(key == GLUT_KEY_DOWN) yPos -= stepSize;
//    if(key == GLUT_KEY_LEFT) xPos -= stepSize;
//    if(key == GLUT_KEY_RIGHT) xPos += stepSize;
//    
//    // 边界判断和限制
//    if(xPos < (-1.0f + blockSize)) xPos = -1.0f + blockSize;
//    if(xPos > (1.0f - blockSize)) xPos = 1.0f - blockSize;
//    if(yPos < (-1.0f + blockSize))  yPos = -1.0f + blockSize;
//    if(yPos > (1.0f - blockSize)) yPos = 1.0f - blockSize;
//    
//    // 触发渲染
//    glutPostRedisplay();
//}
//
//void RenderScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    // 创建3个4x4矩阵，合成矩阵、平移矩阵、旋转矩阵
//    M3DMatrix44f mFinalTransform, mTranslationMatrix, mRotationMatrix;
//    // 平移(xPos, yPos, 0)的矩阵表示
//    m3dTranslationMatrix44(mTranslationMatrix, xPos, yPos, 0.0f);
//    
//    // 绕z轴旋转的矩阵，每次旋转角度为5度
//    static float zRot = 0.0f;
//    zRot += 5.0f;
//    m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(zRot), 0.0f, 0.0f, 1.0f);
//    
//    // 矩阵相乘，参数顺序很重要，先平移，后旋转
//    m3dMatrixMultiply44(mFinalTransform, mTranslationMatrix, mRotationMatrix);
//    
//    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
//    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vRed);
//    squareBatch.Draw();
//    
//    glutSwapBuffers();
//}
//
//void ChangeSize(int w, int h)
//{
//    glViewport(0, 0, w, h);
//}
//
//int main(int argc, char* argv[])
//{
//    gltSetWorkingDirectory(argv[0]);
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Move Block with Arrow Keys");
//    
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutSpecialFunc(SpecialKeys);
//    
//    SetupRC();
//    glutMainLoop();
//    return 0;
//}

