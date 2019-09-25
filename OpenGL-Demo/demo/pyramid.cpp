#include <GLTools.h>
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <glut/glut.h>

#include <math.h>

namespace Demo {
    namespace Pyramid {
        // 着色器
        GLShaderManager shaderManager;
        // 模型视图矩阵堆栈
        GLMatrixStack modelViewMatrix;
        // 投影矩阵堆栈
        GLMatrixStack projectionMatrix;
        // 照相机角色帧
        GLFrame cameraFrame;
        // 物体角色帧
        GLFrame objectFrame;
        // 视景体
        GLFrustum viewFrustum;
        // 金字塔批次
        GLBatch pyramidBatch;
        // 纹理唯一标识
        GLuint textureID;
        // 变换管线
        GLGeometryTransform transformPipeline;
        // 光源位置
        GLfloat vLightPos[] = {1.0f, 1.0f, 0.0f};
        // 白色
        GLfloat vWhite[] = {1.0f, 1.0f, 1.0f, 1.0f};
        
        // 添加一个金字塔三角形，传入3个顶点坐标以及对应的纹理坐标
        void MakePyramidTriangle(M3DVector3f vertex1, M3DVector2f texcoord1,
                                 M3DVector3f vertex2, M3DVector2f texcoord2,
                                 M3DVector3f vertex3, M3DVector2f texcoord3)
        {
            // 获取法向量
            M3DVector3f normal;
            m3dFindNormal(normal, vertex1, vertex2, vertex3);
            
            // 向批次中添加一个表面法线
            pyramidBatch.Normal3fv(normal);
            // 添加一个纹理坐标
            // 注意这里使用 MultiTexCoord2f，不要使用 MultiTexCoord2fv
            pyramidBatch.MultiTexCoord2f(0, texcoord1[0], texcoord1[1]);
            // 添加顶点位置
            pyramidBatch.Vertex3fv(vertex1); // 顶部
            
            pyramidBatch.Normal3fv(normal);
            pyramidBatch.MultiTexCoord2f(0, texcoord2[0], texcoord2[1]);
            pyramidBatch.Vertex3fv(vertex2); // 左前角
            
            pyramidBatch.Normal3fv(normal);
            pyramidBatch.MultiTexCoord2f(0, texcoord3[0], texcoord3[1]);
            pyramidBatch.Vertex3fv(vertex3); // 右前角
        }
        
        // 获取金字塔批次数据
        void MakePyramid()
        {
            // 顶点坐标和纹理坐标
            M3DVector3f vApex = {0.0f, 1.0f, 0.0f};
            M3DVector3f vFrontLeft = {-1.0f, -1.0f, 1.0f};
            M3DVector3f vFrontRight = {1.0f, -1.0f, 1.0f};
            M3DVector3f vBackLeft = {-1.0f, -1.0f, -1.0f};
            M3DVector3f vBackRight = {1.0f, -1.0f, -1.0f};
            M3DVector2f vTex00 = {0.0f, 0.0f};
            M3DVector2f vTex01 = {0.0f, 1.0f};
            M3DVector2f vTex10 = {1.0f, 0.0f};
            M3DVector2f vTex11 = {1.0f, 1.0f};
            M3DVector2f vApexTex = {0.5f, 1.0f};
            
            pyramidBatch.Begin(GL_TRIANGLES, 18, 1);
            MakePyramidTriangle(vBackLeft, vTex00, vBackRight, vTex10, vFrontRight, vTex11);
            MakePyramidTriangle(vBackLeft, vTex00, vFrontRight, vTex11, vFrontLeft, vTex01);
            MakePyramidTriangle(vApex, vApexTex, vFrontLeft, vTex00, vFrontRight, vTex10);
            MakePyramidTriangle(vApex, vApexTex, vBackLeft, vTex10, vFrontLeft, vTex00);
            MakePyramidTriangle(vApex, vApexTex, vFrontRight, vTex10, vBackRight, vTex00);
            MakePyramidTriangle(vApex, vApexTex, vBackRight, vTex00, vBackLeft, vTex10);
            
            pyramidBatch.End();
        }
        
        /*
         从文件中读取纹理数据
         szFileName: 文件名
         minFilter: 纹理缩小是的过滤器
         magFilter: 纹理放大时的过滤器
         wrapMode: 纹理填充模式
         */
        bool LoadTGATexture(const char* szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
        {
            GLbyte *pBits;
            GLint nWidth, nHeight, nComponent;
            GLenum eFormat;
            
            // 根据文件名从磁盘中读取纹理数据
            pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponent, &eFormat);
            if (pBits == NULL) {
                return false;
            }
            
            // 设置纹理数据的填充方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
            
            // 设置纹理缩小放大时使用的过滤器
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            
            // 精密打包纹理数据（主要是字节对齐）
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            
            // 加载纹理数据到二维纹理层
            glTexImage2D(GL_TEXTURE_2D, 0, nComponent, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);
            
            // 释放二进制缓存数据
            free(pBits);
            
            // 判断下缩小过滤器是否是 Mip 贴图过滤器，是的话，启用 Mip 贴图
            if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
                minFilter == GL_LINEAR_MIPMAP_NEAREST ||
                minFilter == GL_NEAREST_MIPMAP_LINEAR ||
                minFilter == GL_NEAREST_MIPMAP_NEAREST) {
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            
            return true;
        }
        
        // 程序初始化
        void SetupRC()
        {
            // 设置背景颜色为灰色
            glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
            // 初始化着色器
            shaderManager.InitializeStockShaders();
            // 开启深度测试
            glEnable(GL_DEPTH_TEST);
            // 照相机移动位置，保证物体完全显示
            cameraFrame.MoveForward(-7.0f);
            
            // 获取纹理标识
            glGenTextures(1, &textureID);
            // 绑定当前二维纹理的纹理为 textureID 标识代表的纹理
            glBindTexture(GL_TEXTURE_2D, textureID);
            // 从 TGA 文件中加载纹理数据
            LoadTGATexture("stone.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
            
            // 获取金字塔批次数据
            MakePyramid();
        }
        
        // 资源销毁
        void ShutdownRC(void)
        {
            // 销毁纹理资源
            glDeleteTextures(1, &textureID);
        }
        
        // 窗口渲染回调方法
        void RenderScene(void)
        {
            // 清空缓冲区
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            // 压栈，保留原始矩阵
            modelViewMatrix.PushMatrix();
            // 获取照相机矩阵，并合并到模型视图矩阵
            M3DMatrix44f mCamera;
            cameraFrame.GetCameraMatrix(mCamera);
            modelViewMatrix.MultMatrix(mCamera);
            
            // 获取物体的集合变换矩阵，并合并到模型视图矩阵
            M3DMatrix44f mObjectFrame;
            objectFrame.GetMatrix(mObjectFrame);
            modelViewMatrix.MultMatrix(mObjectFrame);
            
            // 绑定当前二维纹理的纹理为 textureID 标识代表的纹理
            glBindTexture(GL_TEXTURE, textureID);
            
            // 点光源着色器绘制金字塔
            shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
                                         transformPipeline.GetModelViewMatrix(),
                                         transformPipeline.GetProjectionMatrix(),
                                         vLightPos, vWhite, 0);
            pyramidBatch.Draw();
            
            // 还原矩阵
            modelViewMatrix.PopMatrix();
            
            glutSwapBuffers();
        }
        
        // 特殊按键点击回调
        void SpecialKeys(int key, int x, int y)
        {
            // 物体的上下左右旋转
            switch (key) {
                case GLUT_KEY_UP:
                    objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
                    break;
                case GLUT_KEY_DOWN:
                    objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
                    break;
                case GLUT_KEY_LEFT:
                    objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
                    break;
                case GLUT_KEY_RIGHT:
                    objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
                    break;
            }
            // 触发渲染
            glutPostRedisplay();
        }
        
        // 窗口变换回调
        void ChangeSize(int w, int h)
        {
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            // 设置透视投影
            viewFrustum.SetPerspective(35.0f, (float)w/h, 1.0f, 100.0f);
            projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
            
            // 设置变换管线的矩阵堆栈
            transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
        }
        
        int main(int argc, char* argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            // glut 初始化
            glutInit(&argc, argv);
            // 设置渲染模式
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
            // 初始化窗口大小
            glutInitWindowSize(600, 600);
            // 创建窗口，并命名
            glutCreateWindow("Pyramid");
            
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
                return 1;
            }
            // 设置窗口变化回调函数
            glutReshapeFunc(ChangeSize);
            // 设置窗口渲染回调函数
            glutDisplayFunc(RenderScene);
            // 设置特殊按键回调函数
            glutSpecialFunc(SpecialKeys);
            // 初始化环境
            SetupRC();
            glutMainLoop();
            // 资源销毁
            ShutdownRC();
            
            return 0;
        }

    }
}
