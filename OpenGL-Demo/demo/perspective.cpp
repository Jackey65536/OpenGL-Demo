////
////  main.cpp
////  11-Perspective
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
//#include <math.h>
//#include <glut/glut.h>
//
//
//GLFrame viewFrame;
//GLFrustum viewFrustum;
//GLBatch tubeBatch;
//GLBatch innerBatch;
//GLMatrixStack modelViewMatix;
//GLMatrixStack projectionMatrix;
//GLGeometryTransform transformPipeline;
//GLShaderManager shaderManager;
//float fZ = 100.0f;
//float bZ = -100.0f;
//
//// 窗口渲染调用
//void RenderScene(void) {
//    // 清除缓存区
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // 压栈，物体矩阵
//    modelViewMatix.PushMatrix(viewFrame);
//
//    // 默认红色光源着色
//    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
//    tubeBatch.Draw();
//
//    // 默认灰色光源着色
//    GLfloat vGray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
//    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vGray);
//    innerBatch.Draw();
//
//    // 出栈，还原为单位矩阵
//    modelViewMatix.PopMatrix();
//
//    // 双缓存模式，后台缓存切换到前台进行显示
//    glutSwapBuffers();
//}
//
//void SetupTubeBatch() {
//    tubeBatch.Begin(GL_QUADS, 200);
//    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
//    // 后面
//    GLfloat vBack[] = {
//        // Left Pannel
//        -50.0f, 50.0f, fZ,
//        -50.0f, -50.0f, fZ,
//        -35.0f, -50.0f, fZ,
//        -35.0f, 50.0f, fZ,
//        // Right Panel
//        50.0f, 50.0f, fZ,
//        35.0f, 50.0f, fZ,
//        35.0f, -50.0f, fZ,
//        50.0f,-50.0f, fZ,
//        // Top Panel
//        -35.0f, 50.0f, fZ,
//        -35.0f, 35.0f, fZ,
//        35.0f, 35.0f, fZ,
//        35.0f, 50.0f, fZ,
//        // Bottom Panel
//        -35.0f, -35.0f, fZ,
//        -35.0f, -50.0f, fZ,
//        35.0f, -50.0f, fZ,
//        35.0f, -35.0f, fZ
//    };
//    for(int i = 0; i < 16; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
//        tubeBatch.Vertex3f(vBack[index], vBack[index+1], vBack[index+2]);
//    }
//
//    // 前面
//    GLfloat vFront[] = {
//        // Left Pannel
//        -35.0f, 50.0f, bZ,
//        -35.0f, -50.0f, bZ,
//        -50.0f, -50.0f, bZ,
//        -50.0f, 50.0f, bZ,
//        // Right Panel
//        50.0f, -50.0f, bZ,
//        35.0f, -50.0f, bZ,
//        35.0f, 50.0f, bZ,
//        50.0f, 50.0f, bZ,
//        // Top Panel
//        35.0f, 50.0f, bZ,
//        35.0f, 35.0f, bZ,
//        -35.0f, 35.0f, bZ,
//        -35.0f, 50.0f, bZ,
//        // Bottom Panel
//        35.0f, -35.0f, bZ,
//        35.0f, -50.0f, bZ,
//        -35.0f, -50.0f, bZ,
//        -35.0f, -35.0f, bZ
//    };
//    for(int i = 0; i < 16; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);
//        tubeBatch.Vertex3f(vFront[index], vFront[index+1], vFront[index+2]);
//    }
//
//    // 上面
//    GLfloat vTop[] = {
//        -50.0f, 50.0f, fZ,
//        50.0f, 50.0f, fZ,
//        50.0f, 50.0f, bZ,
//        -50.0f, 50.0f, bZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
//        tubeBatch.Vertex3f(vTop[index], vTop[index+1], vTop[index+2]);
//    }
//
//    // 下面
//    GLfloat vBottom[] = {
//        -50.0f, -50.0f, fZ,
//        -50.0f, -50.0f, bZ,
//        50.0f, -50.0f, bZ,
//        50.0f, -50.0f, fZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
//        tubeBatch.Vertex3f(vBottom[index], vBottom[index+1], vBottom[index+2]);
//    }
//
//    // 左面
//    GLfloat vLeft[] = {
//        50.0f, 50.0f, fZ,
//        50.0f, -50.0f, fZ,
//        50.0f, -50.0f, bZ,
//        50.0f, 50.0f, bZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
//        tubeBatch.Vertex3f(vLeft[index], vLeft[index+1], vLeft[index+2]);
//    }
//
//    // 右面
//    GLfloat vRight[] = {
//        -50.0f, 50.0f, fZ,
//        -50.0f, 50.0f, bZ,
//        -50.0f, -50.0f, bZ,
//        -50.0f, -50.0f, fZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
//        tubeBatch.Vertex3f(vRight[index], vRight[index+1], vRight[index+2]);
//    }
//    tubeBatch.End();
//}
//
//void SetupInnerBatch() {
//    innerBatch.Begin(GL_QUADS, 40);
//    innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
//    // 上面
//    GLfloat innerTop[] = {
//        -35.0f, 35.0f, fZ,
//        35.0f, 35.0f, fZ,
//        35.0f, 35.0f, bZ,
//        -35.0f, 35.0f, bZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        innerBatch.Normal3f(0.0f, -1.0f, 0.0f);
//        innerBatch.Vertex3f(innerTop[index], innerTop[index+1], innerTop[index+2]);
//    }
//
//    // 下面
//    GLfloat innerBottom[] = {
//        -35.0f, -35.0f, fZ,
//        -35.0f, -35.0f, bZ,
//        35.0f, -35.0f, bZ,
//        35.0f, -35.0f, fZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
//        innerBatch.Vertex3f(innerBottom[index], innerBottom[index+1], innerBottom[index+2]);
//    }
//
//    // 左面
//    GLfloat innerLeft[] = {
//        35.0f, 35.0f, fZ,
//        35.0f, -35.0f, fZ,
//        35.0f, -35.0f, bZ,
//        35.0f, 35.0f, bZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
//        innerBatch.Vertex3f(innerLeft[index], innerLeft[index+1], innerLeft[index+2]);
//    }
//
//    // 右面
//    GLfloat innerRight[] = {
//        -35.0f, 35.0f, fZ,
//        -35.0f, 35.0f, bZ,
//        -35.0f, -35.0f, bZ,
//        -35.0f, -35.0f, fZ
//    };
//    for(int i = 0; i < 4; i++) {
//        int index = i * 3;
//        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
//        innerBatch.Vertex3f(innerRight[index], innerRight[index+1], innerRight[index+2]);
//    }
//
//    innerBatch.End();
//}
//
//// 程序初始化环境
//void SetupRC() {
//    // 设置背景颜色为淡蓝色
//    glClearColor(0.0f, 0.0f, 0.75f, 1.0f);
//
//    // 开启深度测试
//    glEnable(GL_DEPTH_TEST);
//
//    // 着色器初始化
//    shaderManager.InitializeStockShaders();
//
//    // 物体向里面移动 450 距离
//    viewFrame.MoveForward(450.0f);
//
//    // 创建长方体暴露在外面的红色面
//    SetupTubeBatch();
//
//    // 创建长方体里面的灰色面
//    SetupInnerBatch();
//}
//
//void SpecialKeys(int key, int x, int y) {
//    // 按下上、下、左、右方向键，对物体进行旋转，m3dDegToRad = 角度 -> 弧度
//    switch(key) {
//        case GLUT_KEY_UP:
//            // angle=-5, x=1, y=0, z=0 表示绕x轴正方向顺时针旋转(从x轴正方向看去)
//            viewFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
//            break;
//        case GLUT_KEY_DOWN:
//            // angle=5, x=1, y=0, z=0 表示绕x轴正方向逆时针旋转(从x轴正方向看去)
//            viewFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
//            break;
//        case GLUT_KEY_LEFT:
//            // angle=-5, x=0, y=1, z=0 表示绕y轴正方向顺时针旋转(从y轴正方向看去)
//            viewFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
//            break;
//        case GLUT_KEY_RIGHT:
//            // angle=5, x=0, y=1, z=0 表示绕y轴正方向逆时针旋转(从y轴正方向看去)
//            viewFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
//            break;
//    }
//
//    // 重写渲染窗口
//    glutPostRedisplay();
//}
//
//// 窗口变换回调
//void ChangeSize(int width, int height) {
//    // 防止除数为0
//    if(height == 0)
//        height = 1;
//
//    // 设置视口
//    glViewport(0, 0, width, height);
//
//    // 设置透视投影矩阵，参数分别为：透视角，宽高比，近距，远距
//    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
//
//    // 保持透视投影矩阵
//    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//
//    // 利用变换管线，管理2个堆栈
//    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
//}
//
//// 程序入口
//int main(int argc, char* argv[]) {
//    // 针对 Mac OS 设置工作目录路径
//    gltSetWorkingDirectory(argv[0]);
//
//    // 初始化 GLUT
//    glutInit(&argc, argv);
//
//    // 初始化渲染模式
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
//
//    // 初始化窗口大小
//    glutInitWindowSize(800, 600);
//
//    // 创建窗口并命名
//    glutCreateWindow("Perspective Projection Example");
//
//    // 检测驱动程序是否初始化成功
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//
//    // 窗口大小改变回调函数设置
//    glutReshapeFunc(ChangeSize);
//
//    // 特殊按键点击回调函数设置
//    glutSpecialFunc(SpecialKeys);
//
//    // 窗口渲染回调函数设置
//    glutDisplayFunc(RenderScene);
//
//    // 程序初始化环境
//    SetupRC();
//
//    // 主消息循环
//    glutMainLoop();
//
//    return 0;
//}
//
