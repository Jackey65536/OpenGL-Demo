//
//  main.cpp
//  19-Anisotropic
//
//  Created by luhe liu on 2018/6/3.
//  Copyright © 2018年 luhe liu. All rights reserved.
//

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

namespace Demo {
    namespace Ansiotropic {
        // 着色器管理器
        GLShaderManager shaderManager;
        // 视景体
        GLFrustum viewFrustum;
        // 变换管线，以及它管理的2个矩阵堆栈
        GLGeometryTransform transformPipeline;
        GLMatrixStack modelViewMatrix;
        GLMatrixStack projectionMatrix;
        
        // 4个数据批次
        GLBatch floorBatch;
        GLBatch ceilingBatch;
        GLBatch leftWallBatch;
        GLBatch rightWallBatch;
        
        // 用于控制观察者向前和向后
        GLfloat viewZ = -65.0f;
        
        // 宏定义，地板、天花板、墙分别对应的纹理标识数组索引
#define TEXTURE_BRICK   0
#define TEXTURE_FLOOR   1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT   3
        // 纹理标识数组
        GLuint  textures[TEXTURE_COUNT];
        // 纹理文件名数组
        const char *szTextureFiles[TEXTURE_COUNT] = { "brick.tga", "floor.tga", "ceiling.tga" };
        
        // 点击右键菜单选项回调
        void ProcessMenu(int value) {
            // 循环遍历所有纹理数据
            for(GLint iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++) {
                // 绑定当前纹理为该索引对应的纹理数据
                glBindTexture(GL_TEXTURE_2D, textures[iLoop]);
                
                // 设置该纹理数据的缩小过滤器
                switch(value) {
                    case 0: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); break;
                    case 1: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); break;
                    case 2: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); break;
                    case 3: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); break;
                    case 4: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); break;
                    case 5: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); break;
                    case 6:
                        // 设置各向异性
                        GLfloat fLargest;
                        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
                        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
                        break;
                    case 7:
                        // 设置各向同性
                        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
                        break;
                }
            }
            // 触发渲染
            glutPostRedisplay();
        }
        
        // 加载所有的纹理数据
        void LoadAllTextureData() {
            GLbyte *pBytes;
            GLint iWidth, iHeight, iComponents;
            GLenum eFormat;
            GLint iLoop;
            // 申请要加载的纹理数据数量
            glGenTextures(TEXTURE_COUNT, textures);
            // 循环遍历所有纹理文件
            for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++) {
                // 绑定当前纹理为该索引对应的纹理数据
                glBindTexture(GL_TEXTURE_2D, textures[iLoop]);
                
                // 从 TGA 文件中读取纹理数据
                pBytes = gltReadTGABits(szTextureFiles[iLoop], &iWidth, &iHeight, &iComponents, &eFormat);
                
                // 设置纹理数据缩小、放大过滤器
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                
                // 设置纹理数据（s, t）环绕模式
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                
                // 加载纹理数据到2维纹理缓冲区
                glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
                
                // 2维纹理缓冲区开启 Mip 贴图
                glGenerateMipmap(GL_TEXTURE_2D);
                
                // 释放纹理数据
                free(pBytes);
            }
        }
        
        // 初始化地板数据
        void SetupFloorBatch() {
            GLfloat z;
            floorBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
            for(z = 60.0f; z >= 0.0f; z -=10.0f) {
                floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
                floorBatch.Vertex3f(-10.0f, -10.0f, z);
                
                floorBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
                floorBatch.Vertex3f(10.0f, -10.0f, z);
                
                floorBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
                floorBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);
                
                floorBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
                floorBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);
            }
            floorBatch.End();
        }
        
        // 初始化天花板数据
        void SetupCeilingBatch() {
            GLfloat z;
            ceilingBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
            for(z = 60.0f; z >= 0.0f; z -=10.0f) {
                ceilingBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
                ceilingBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);
                
                ceilingBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
                ceilingBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);
                
                ceilingBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
                ceilingBatch.Vertex3f(-10.0f, 10.0f, z);
                
                ceilingBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
                ceilingBatch.Vertex3f(10.0f, 10.0f, z);
            }
            ceilingBatch.End();
        }
        
        // 初始化左右墙数据
        void SetupWallBatch() {
            // 左墙
            GLfloat z;
            leftWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
            for(z = 60.0f; z >= 0.0f; z -=10.0f) {
                leftWallBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
                leftWallBatch.Vertex3f(-10.0f, -10.0f, z);
                
                leftWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
                leftWallBatch.Vertex3f(-10.0f, 10.0f, z);
                
                leftWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
                leftWallBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);
                
                leftWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
                leftWallBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);
            }
            leftWallBatch.End();
            
            // 右墙
            rightWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
            for(z = 60.0f; z >= 0.0f; z -=10.0f) {
                rightWallBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
                rightWallBatch.Vertex3f(10.0f, -10.0f, z);
                
                rightWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
                rightWallBatch.Vertex3f(10.0f, 10.0f, z);
                
                rightWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
                rightWallBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);
                
                rightWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
                rightWallBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);
            }
            rightWallBatch.End();
        }
        
        // 程序初始化渲染环境
        void SetupRC() {
            // 设置窗口背景为黑色
            glClearColor(0.0f, 0.0f, 0.0f,1.0f);
            
            // 初始化着色器
            shaderManager.InitializeStockShaders();
            
            // 加载所有纹理数据
            LoadAllTextureData();
            
            // 初始化地板
            SetupFloorBatch();
            // 初始化天花板
            SetupCeilingBatch();
            // 初始化墙
            SetupWallBatch();
        }
        
        // 程序释放资源
        void ShutdownRC(void) {
            // 删除所有的纹理数据
            glDeleteTextures(TEXTURE_COUNT, textures);
        }
        
        // 特殊按键点击回调
        void SpecialKeys(int key, int x, int y) {
            // 上按键前进
            if(key == GLUT_KEY_UP)
                viewZ += 0.5f;
            // 下按键后退
            if(key == GLUT_KEY_DOWN)
                viewZ -= 0.5f;
            
            // 触发渲染
            glutPostRedisplay();
        }
        
        // 窗口渲染回调方法
        void RenderScene(void) {
            // 清除缓冲区内容
            glClear(GL_COLOR_BUFFER_BIT);
            
            // 压入单位矩阵
            modelViewMatrix.PushMatrix();
            // 模型视图向Z轴平移
            modelViewMatrix.Translate(0.0f, 0.0f, viewZ);
            
            // 采用纹理替换着色器进行绘制
            shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);
            
            // 绑定当前纹理为地板纹理，进行地板绘制
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]);
            floorBatch.Draw();
            
            // 绑定当前纹理为天花板，进行天花板绘制
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_CEILING]);
            ceilingBatch.Draw();
            
            // 绑定当前纹理为左右墙纹理，进行左右墙绘制
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
            leftWallBatch.Draw();
            rightWallBatch.Draw();
            
            // 出栈，恢复原来环境
            modelViewMatrix.PopMatrix();
            
            // 因为是双缓冲区模式，后台缓冲区替换到前台缓存区进行显示
            glutSwapBuffers();
        }
        
        // 窗口大小变化回调方法
        void ChangeSize(int width, int height) {
            // 防止除数为0
            if(height == 0)
                height = 1;
            
            // 设置视口
            glViewport(0, 0, width, height);
            // 计算窗口宽高比
            GLfloat fAspect = (GLfloat)width / (GLfloat)height;
            // 设置投影矩阵
            viewFrustum.SetPerspective(80.0f, fAspect, 1.0, 120.0);
            // 投影矩阵堆栈保持投影矩阵
            projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
            // 设置变换管线的投影矩阵堆栈和模型视图矩阵堆栈
            transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
            
        }
        
        // 程序入口
        int main(int argc, char *argv[]) {
            // 设置 Mac OS 工作目录路径
            gltSetWorkingDirectory(argv[0]);
            
            // GLUT 初始化
            glutInit(&argc, argv);
            
            // 设置 GLUT 渲染模式
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            
            // 创建窗口
            glutInitWindowSize(800, 600);
            glutCreateWindow("Tunnel");
            
            // 绑定事件回调
            glutReshapeFunc(ChangeSize);
            glutSpecialFunc(SpecialKeys);
            glutDisplayFunc(RenderScene);
            
            // 创建右键菜单
            glutCreateMenu(ProcessMenu);
            // 添加右键菜单选项
            glutAddMenuEntry("GL_NEAREST",0);
            glutAddMenuEntry("GL_LINEAR",1);
            glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST",2);
            glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
            glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
            glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);
            glutAddMenuEntry("Anisotropic Filter", 6);
            glutAddMenuEntry("Anisotropic Off", 7);
            // 设置右键菜单弹出
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            // GLEW 驱动程序初始化
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
                return 1;
            }
            
            // 程序初始化渲染环境
            SetupRC();
            
            // 运行循环
            glutMainLoop();
            
            // 程序释放资源
            ShutdownRC();
            
            return 0;
        }
    }
}
