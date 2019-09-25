#include <GLTools.h>
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <math.h>
#include <glut/glut.h>

namespace Demo {
    namespace Geotest {
        // 使用照相机 和 角色帧 进行移动
        GLFrame             viewFrame;
        // 矩阵工具类，用来快速设置正/透视投影矩阵，完成坐标3D->2D的映射过程
        GLFrustum           viewFrustum;
        // 三角形的容器，将三角形以更高效的方式（索引顶点数组）进行组织，并且实际上将多边形存储在图形卡（使用定点缓冲区对象）上
        GLTriangleBatch     torusBatch;
        // 矩阵的工具类，可以加载单元矩阵、矩阵、矩阵相乘、压栈、出栈、缩放、平移、旋转
        GLMatrixStack       modelViewMatrix;
        GLMatrixStack       projectionMatrix;
        // 管线类
        GLGeometryTransform transformPipeline;
        // 着色器管理类
        GLShaderManager     shaderManager;
        
        // 是否开启正反面剔除
        int iCull = 0;
        // 是否开始深度测试
        int iDepth = 0;
        
        // 点击菜单选项
        void ProcessMenu(int value)
        {
            switch (value) {
                case 1:
                    // 开关深度测试
                    iDepth = !iDepth;
                    break;
                case 2:
                    // 开关正反面剔除
                    iCull = !iCull;
                    break;
                case 3:
                    // 开关多边形面模式
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case 4:
                    // 开关多边形线模式
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
                case 5:
                    // 开关多边形点模式
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                    break;
            }
            glutPostRedisplay();
        }
        
        void RenderScene(void)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // 判断是否开启正反面剔除
            if (iCull) {
                glEnable(GL_CULL_FACE);
            } else {
                glDisable(GL_CULL_FACE);
            }
            // 判断是否开启深度测试
            if (iDepth) {
                glEnable(GL_DEPTH_TEST);
            } else {
                glDisable(GL_DEPTH_TEST);
            }
            // 保存当前的模型视图矩阵
            modelViewMatrix.PushMatrix(viewFrame);
            
            GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
            shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
            // 画花托
            torusBatch.Draw();
            // 还原以前的模型视图矩阵
            modelViewMatrix.PopMatrix();
            
            glutSwapBuffers();
        }
        
        void SetupRC()
        {
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
            shaderManager.InitializeStockShaders();
            transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
            // 移动物体的位置，值越大物体越远，值越小物体越近
            viewFrame.MoveForward(6.0f);
            // 创建一个花托批次，参数：批次、外半径、内半径、片段数、堆叠数（多个点连线形成圆，堆叠数就是点数）
            gltMakeTorus(torusBatch, 1.0f, 0.3f, 52, 26);
            // 设置默认点的大小
            glPointSize(4.0f);
        }
        
        void SpecialKeys(int key, int x, int y)
        {
            switch (key) {
                case GLUT_KEY_UP:
                    viewFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
                    break;
                case GLUT_KEY_DOWN:
                    viewFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
                    break;
                case GLUT_KEY_LEFT:
                    viewFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
                    break;
                case GLUT_KEY_RIGHT:
                    viewFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
                    break;
                default:
                    break;
            }
            
            //触发渲染
            glutPostRedisplay();
        }
        
        void ChangeSize(int w, int h)
        {
            if (h == 0) {
                h = 1;
            }
            glViewport(0, 0, w, h);
            
            viewFrustum.SetPerspective(35.0f, GLfloat(w)/GLfloat(h), 1.0f, 500.0f);
            projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
        }
        
        int main(int argc, char* argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
            glutInitWindowSize(800, 600);
            glutCreateWindow("Geometry Test Program");
            
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            glutSpecialFunc(SpecialKeys);
            
            glutCreateMenu(ProcessMenu);
            
            glutAddMenuEntry("Toggle depth test", 1);
            glutAddMenuEntry("Toggle cull backface", 2);
            glutAddMenuEntry("Set Fill Mode", 3);
            glutAddMenuEntry("Set Line Mode", 4);
            glutAddMenuEntry("set Point Mode", 5);
            
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
                return 1;
            }
            SetupRC();
            glutMainLoop();
            return 0;
        }
        

    }
}
