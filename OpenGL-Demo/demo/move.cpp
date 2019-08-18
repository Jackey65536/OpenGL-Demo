//#include <GLShaderManager.h>
//#include <GLTools.h>
//#include <glut/glut.h>
//
//GLBatch squareBatch;
//GLShaderManager shaderManager;
//
//GLfloat blockSize = 0.2f;
//GLfloat vVerts[] = {
//    -blockSize, -blockSize, 0.0f, // 左下角
//    blockSize, -blockSize, 0.0f, // 右下角
//    blockSize, blockSize, 0.0f, // 右上角
//    -blockSize, blockSize, 0.0f, // 左上角
//};
//
//int specialKey = GLUT_KEY_RIGHT;
//
//void BounceFunction(int key)
//{
//    // 每次按键的矩形移动距离
//    GLfloat stepSize = 0.025f;
//    // 左下角坐标的(x, y)
//    GLfloat blockX = vVerts[0];
//    GLfloat blockY = vVerts[1];
//    
//    // 判断键盘点击的是哪个按钮，计算下一个点的位置
//    if (key == GLUT_KEY_UP) { blockY += stepSize; }
//    if (key == GLUT_KEY_DOWN) { blockY -= stepSize; }
//    if (key == GLUT_KEY_LEFT) { blockX -= stepSize; }
//    if (key == GLUT_KEY_RIGHT) { blockX += stepSize; }
//    
//    // 边界检测，让矩形没法超出边界
//    if (blockX < -1.0f) { blockX = -1.0f; }
//    if (blockX > (1.0f - blockSize * 2)) { blockX = 1.0f - blockSize * 2; }
//    if(blockY < -1.0f) blockY = -1.0f;
//    if(blockY > (1.0f - blockSize * 2)) blockY = 1.0f - blockSize * 2;
//    
//    // 左下角
//    vVerts[0] = blockX;
//    vVerts[1] = blockY;
//    // 右下角
//    vVerts[3] = blockX + blockSize * 2;
//    vVerts[4] = blockY;
//    // 右上角
//    vVerts[6] = blockX + blockSize * 2;
//    vVerts[7] = blockY + blockSize * 2;
//    // 左上角
//    vVerts[9] = blockX;
//    vVerts[10] = blockY + blockSize * 2;
//    
//    // 更新批次里的数据
//    squareBatch.CopyVertexData3f(vVerts);
//}
//
//void SpecialKeys(int key, int x, int y)
//{
//    specialKey = key;
//}
//
//// 窗口渲染
//void RenderScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
//    squareBatch.Draw();
//    // 交换前后台缓冲区
//    glutSwapBuffers();
//    // 计算下一个矩形位置
//    BounceFunction(specialKey);
//    // 触发重画事件 -> RenderScene
//    glutPostRedisplay();
//}
//
//void SetupRC()
//{
//    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//    shaderManager.InitializeStockShaders();
//    
//    // 批次初始化
//    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
//    squareBatch.CopyVertexData3f(vVerts);
//    squareBatch.End();
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
//    glutCreateWindow("Move Demo");
//    glutDisplayFunc(RenderScene);
//    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);
//    
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    
//    SetupRC();
//    glutMainLoop();
//    return 0;
//}

