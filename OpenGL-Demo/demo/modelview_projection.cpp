////
////  main.cpp
////  12-ModelViewProjection
////
////  Created by luhe liu on 2018/4/18.
////  Copyright © 2018年 luhe liu. All rights reserved.
////
//
//#include <GLTools.h>    // OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLGeometryTransform.h>
//#include <GLBatch.h>
//#include <StopWatch.h>
//#include <math.h>
//#include <glut/glut.h>
//
//// 视景体
//GLFrustum viewFrustum;
//
//// 着色器
//GLShaderManager shaderManager;
//
//// 花托批次
//GLTriangleBatch torusBatch;
//
//// 窗口变化回调
//void ChangeSize(int width, int height) {
//    // 防止除数为0
//    if(height == 0)
//        height = 1;
//    
//    // 设置视口
//    glViewport(0, 0, width, height);
//    
//    // 设置投影方式是透视投影
//    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
//}
//
//// 窗口渲染回调
//void RenderScene(void) {
//    // 定义一个测试运行时间
//    static CStopWatch rotTimer;
//    // 获取到上一个时间点到当前的时间间隔(单位是每秒刻度数，即  1/60s)
//    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
//    
//    // 清空缓冲区
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    // 定义矩阵
//    M3DMatrix44f mTranslate, mRotate, mModelview, mModelViewProjection;
//    
//    // 向z轴平移的矩阵变换
//    m3dTranslationMatrix44(mTranslate, 0.0f, 0.0f, -2.5f);
//    
//    // 绕y轴旋转的矩阵变换
//    m3dRotationMatrix44(mRotate, m3dDegToRad(yRot), 0.0f, 1.0f, 0.0f);
//    
//    // 两种变换相加。矩阵变换的合并矩阵
//    m3dMatrixMultiply44(mModelview, mTranslate, mRotate);
//    
//    // 投影矩阵 + 视图变换矩阵 = 最终物体位置坐标
//    m3dMatrixMultiply44(mModelViewProjection, viewFrustum.GetProjectionMatrix(), mModelview);
//    
//    // 绘制花托
//    GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//    shaderManager.UseStockShader(GLT_SHADER_FLAT, mModelViewProjection, vBlack);
//    torusBatch.Draw();
//    
//    // 因为是双缓冲区模式，后台缓冲区替换到前台缓存区进行显示
//    glutSwapBuffers();
//    
//    // 自动触发下次渲染回调，达到动画的效果
//    glutPostRedisplay();
//}
//
//// 程序初始化
//void SetupRC() {
//    // 设置背景颜色为黑色
//    glClearColor(0.8f, 0.8f, 0.8f, 1.0f );
//    
//    // 开启深度测试
//    glEnable(GL_DEPTH_TEST);
//    
//    // 初始化着色器
//    shaderManager.InitializeStockShaders();
//    
//    // 得到花托批次数据
//    gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
//    
//    // 设置多边形模式为前后面线段模式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//}
//
//// 程序入口
//int main(int argc, char* argv[]) {
//    // 设置 Mac OS 工作目录路径
//    gltSetWorkingDirectory(argv[0]);
//    
//    // GLUT初始化
//    glutInit(&argc, argv);
//    
//    // 设置渲染模式
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    
//    // 初始化窗口大小
//    glutInitWindowSize(600, 600);
//    
//    // 创建窗口并命名
//    glutCreateWindow("ModelViewProjection");
//    
//    // 判断驱动程序是否初始化完毕
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    
//    // 窗口变化回调函数设置
//    glutReshapeFunc(ChangeSize);
//    
//    // 窗口渲染回调函数设置
//    glutDisplayFunc(RenderScene);
//    
//    // 初始化环境
//    SetupRC();
//    
//    // 主消息循环
//    glutMainLoop();
//    
//    return 0;
//}
//
