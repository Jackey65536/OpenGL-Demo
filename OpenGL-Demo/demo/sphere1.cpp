//
//  main.cpp
//  13-SphereWorld-Lv1
//
//  Created by luhe liu on 2018/4/18.
//  Copyright © 2018年 luhe liu. All rights reserved.
//

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <math.h>
#include <stdio.h>
#include <glut/glut.h>

namespace Demo {
    namespace Sphere1 {
        // 着色器
        GLShaderManager shaderManager;
        // 视图矩阵堆栈
        GLMatrixStack modelViewMatrix;
        // 投影矩阵堆栈
        GLMatrixStack projectionMatrix;
        // 视景体
        GLFrustum viewFrustum;
        // 变换管线
        GLGeometryTransform transformPipeline;
        // 花托批次
        GLTriangleBatch torusBatch;
        // 地板批次
        GLBatch floorBatch;
        // 地板颜色，绿色
        GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
        // 花托线颜色，红色
        GLfloat vTorusColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        // 程序初始化
        void SetupRC() {
            
            // 设置窗口背景颜色为黑色
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            // 初始化着色器
            shaderManager.InitializeStockShaders();
            
            // 开启深度测试
            glEnable(GL_DEPTH_TEST);
            
            // 设置多边形模式为前后面线段模式
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
            // 得到花托批次数据
            gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
            
            // 得到方格地板批次数据
            floorBatch.Begin(GL_LINES, 324);
            for(GLfloat x = -20.0; x <= 20.0f; x+= 0.5) {
                floorBatch.Vertex3f(x, -0.55f, 20.0f);
                floorBatch.Vertex3f(x, -0.55f, -20.0f);
                floorBatch.Vertex3f(20.0f, -0.55f, x);
                floorBatch.Vertex3f(-20.0f, -0.55f, x);
            }
            floorBatch.End();
        }
        
        // 窗口渲染回调
        void RenderScene(void) {
            
            // 获取2次渲染之间的时间间隔
            static CStopWatch    rotTimer;
            float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
            
            // 清空缓冲区
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            // 压栈，保持原始矩阵
            modelViewMatrix.PushMatrix();
            
            // 绘制地板
            shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
            floorBatch.Draw();
            
            // 视图矩阵进行平移、旋转后进行绘制花托
            modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
            modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
            shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vTorusColor);
            torusBatch.Draw();
            
            // 出栈，恢复原始矩阵
            modelViewMatrix.PopMatrix();
            
            // 因为是双缓冲区模式，后台缓冲区替换到前台缓存区进行显示
            glutSwapBuffers();
            
            // 自动触发渲染，达到动画效果
            glutPostRedisplay();
        }
        
        // 窗口变换回调
        void ChangeSize(int width, int height) {
            
            // 防止除数为0
            if(height == 0)
                height = 1;
            
            // 设置视口
            glViewport(0, 0, width, height);
            
            // 设置透视投影
            viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 100.0f);
            projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
            
            // 设置变换管线的矩阵堆栈
            transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
        }
        
        // 程序入口
        int main(int argc, char* argv[]) {
            // 设置 Mac OS 工作目录路径
            gltSetWorkingDirectory(argv[0]);
            
            // GLUT初始化
            glutInit(&argc, argv);
            
            // 设置渲染模式
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
            
            // 初始化窗口大小
            glutInitWindowSize(600, 600);
            
            // 创建窗口并命名
            glutCreateWindow("OpenGL SphereWorld");
            
            // 判断驱动程序是否初始化完毕
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
                return 1;
            }
            
            // 窗口变化回调函数设置
            glutReshapeFunc(ChangeSize);
            
            // 窗口渲染回调函数设置
            glutDisplayFunc(RenderScene);
            
            // 初始化环境
            SetupRC();
            
            // 主消息循环
            glutMainLoop();
            
            return 0;
        }
        
        

    }
}
