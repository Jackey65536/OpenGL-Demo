////
////  main.cpp
////  06-Blending
////
////  Created by luhe liu on 2018/4/12.
////  Copyright © 2018年 luhe liu. All rights reserved.
////
//
//#include <GLTools.h>    // OpenGL toolkit
//#include <GLShaderManager.h>
//#include <glut/glut.h>
//
//GLBatch squareBatch;
//GLBatch greenBatch;
//GLBatch redBatch;
//GLBatch blueBatch;
//GLBatch blackBatch;
//
//GLShaderManager shaderManager;
//
//GLfloat blockSize = 0.2f;
//GLfloat vVerts[] = {
//    -blockSize, -blockSize, 0.0f,
//    blockSize, -blockSize, 0.0f,
//    blockSize,  blockSize, 0.0f,
//    -blockSize,  blockSize, 0.0f
//};
//
////程序一次性初始化
//void SetupRC() {
//    //设置窗口背景为黑色
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
//    
//    //初始化着色器管理者
//    shaderManager.InitializeStockShaders();
//    
//    //创建移动矩形批次
//    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
//    squareBatch.CopyVertexData3f(vVerts);
//    squareBatch.End();
//    
//    //绿色矩形批次
//    GLfloat vBlock[] = {
//        0.25f, 0.25f, 0.0f,
//        0.75f, 0.25f, 0.0f,
//        0.75f, 0.75f, 0.0f,
//        0.25f, 0.75f, 0.0f
//    };
//    greenBatch.Begin(GL_TRIANGLE_FAN, 4);
//    greenBatch.CopyVertexData3f(vBlock);
//    greenBatch.End();
//    
//    //红色矩形批次
//    GLfloat vBlock2[] = {
//        -0.75f, 0.25f, 0.0f,
//        -0.25f, 0.25f, 0.0f,
//        -0.25f, 0.75f, 0.0f,
//        -0.75f, 0.75f, 0.0f
//    };
//    redBatch.Begin(GL_TRIANGLE_FAN, 4);
//    redBatch.CopyVertexData3f(vBlock2);
//    redBatch.End();
//    
//    //蓝色矩形批次
//    GLfloat vBlock3[] = {
//        -0.75f, -0.75f, 0.0f,
//        -0.25f, -0.75f, 0.0f,
//        -0.25f, -0.25f, 0.0f,
//        -0.75f, -0.25f, 0.0f
//    };
//    blueBatch.Begin(GL_TRIANGLE_FAN, 4);
//    blueBatch.CopyVertexData3f(vBlock3);
//    blueBatch.End();
//    
//    //黑色矩形批次
//    GLfloat vBlock4[] = {
//        0.25f, -0.75f, 0.0f,
//        0.75f, -0.75f, 0.0f,
//        0.75f, -0.25f, 0.0f,
//        0.25f, -0.25f, 0.0f
//    };
//    blackBatch.Begin(GL_TRIANGLE_FAN, 4);
//    blackBatch.CopyVertexData3f(vBlock4);
//    blackBatch.End();
//}
//
////特殊按钮监听
//void SpecialKeys(int key, int x, int y) {
//    GLfloat stepSize = 0.025f;
//    
//    //左上角的 X 坐标和右下角的 Y 坐标
//    GLfloat blockX = vVerts[0];
//    GLfloat blockY = vVerts[7];
//    
//    //根据移动方向移动位置
//    switch (key) {
//        case GLUT_KEY_UP: blockY += stepSize; break;
//        case GLUT_KEY_DOWN: blockY -= stepSize; break;
//        case GLUT_KEY_LEFT: blockX -= stepSize; break;
//        case GLUT_KEY_RIGHT: blockX += stepSize; break;
//        default: break;
//    }
//    
//    //移动边界处理
//    if(blockX < -1.0f) blockX = -1.0f;
//    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;;
//    if(blockY < -1.0f + blockSize * 2)  blockY = -1.0f + blockSize * 2;
//    if(blockY > 1.0f) blockY = 1.0f;
//    
//    //矩形四个顶点位置
//    vVerts[0] = blockX;
//    vVerts[1] = blockY - blockSize*2;
//    vVerts[3] = blockX + blockSize*2;
//    vVerts[4] = blockY - blockSize*2;
//    vVerts[6] = blockX + blockSize*2;
//    vVerts[7] = blockY;
//    vVerts[9] = blockX;
//    vVerts[10] = blockY;
//    
//    //批次顶点数据编号
//    squareBatch.CopyVertexData3f(vVerts);
//    
//    //触发渲染
//    glutPostRedisplay();
//}
//
////渲染画面
//void RenderScene(void) {
//    //清理各个缓存区
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    
//    //定义4种颜色
//    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//    GLfloat vBlue[] = { 0.0f, 0.0f, 1.0f, 0.6f };
//    GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//    
//    //画绿色矩形
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
//    greenBatch.Draw();
//    
//    //画红色矩形
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
//    redBatch.Draw();
//    
//    //画蓝色矩形
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlue);
//    blueBatch.Draw();
//    
//    //画黑色矩形
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlack);
//    blackBatch.Draw();
//    
//    //开启颜色混合
//    glEnable(GL_BLEND);
//    //配置混合方程式
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    //画移动矩形，本身半透明蓝色
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlue);
//    squareBatch.Draw();
//    //关闭颜色混合
//    glDisable(GL_BLEND);
//    
//    //将在后台缓冲区进行渲染，然后在结束时交换到前台
//    glutSwapBuffers();
//}
//
////窗口大小改变时接受新的宽度和高度
//void ChangeSize(int w, int h) {
//    
//    //设置视图窗口位置
//    glViewport(0, 0, w, h);
//}
//
////程序入口
//int main(int argc, char* argv[]) {
//    //设置当前工作目录，针对MAC OS X
//    gltSetWorkingDirectory(argv[0]);
//    
//    //初始化GLUT库
//    glutInit(&argc, argv);
//    
//    /*初始化渲染模式，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
//     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区*/
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    
//    //初始化窗口大小
//    glutInitWindowSize(800, 600);
//    //创建窗口
//    glutCreateWindow("Move Block with Arrow Keys to see blending");
//    
//    //注册回调函数
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutSpecialFunc(SpecialKeys);
//    
//    //确保驱动程序的初始化中没有出现任何问题。
//    GLenum err = glewInit();
//    if(GLEW_OK != err) {
//        fprintf(stderr, "glew error:%s\n", glewGetErrorString(err));
//        return 1;
//    }
//    
//    //初始化设置
//    SetupRC();
//    
//    //进入调用循环
//    glutMainLoop();
//    return 0;
//}
//
