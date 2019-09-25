#include <GLTools.h>
#include <GLShaderManager.h>
#include <glut/glut.h>

namespace Demo {
    namespace First {
        GLBatch triangleBatch;
        GLShaderManager shaderManager;
        
        // 窗口大小改变时接受新的宽度和高度
        void ChangeSize(int w, int h)
        {
            // 设置视口，(x, y, widht, height)，其中(x, y)代表窗口中视口的左下角坐标
            glViewport(0, 0, w, h);
        }
        
        // 为程序做一次性的设置
        void SetupRC()
        {
            // 设置背景颜色
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
            // 初始化着色管理器
            shaderManager.InitializeStockShaders();
            // 构建三角形顶点数组，vVerts包含3个顶点的(x, y, z)笛卡尔坐标
            GLfloat vVerts[] = {
                -0.5f, 0.0f, 0.0f,
                0.5f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f,
            };
            // 开始构建批次，GL_TRIANGLES表示三角形，后面参数是顶点数
            triangleBatch.Begin(GL_TRIANGLES, 3);
            /*
             批次增加存储属性
             CopyVertextData3f(xyz顶点数据)
             CopyNormalDataf(表面法线)
             CopyColorData4f(RGBA颜色)
             CopyTexCoorData2f(纹理坐标)
             */
            triangleBatch.CopyVertexData3f(vVerts);
            triangleBatch.End();
        }
        
        void RenderScene(void)
        {
            // 清除一个或一组特定的缓冲区
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            // 设置一组浮点数来表示红色
            GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
            // 传递到存储器着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标系在屏幕上渲染几何图形
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
            // 根据批次里的顶点数据，利用当前设置的着色器进行画图
            triangleBatch.Draw();
            /*
             当glutInitDisplayMode有传入双缓冲模式时，将在后台缓冲区进行渲染，然后在结束时交换到前台，
             为了防止观察者看到可能随着动画帧和动画帧之间闪烁的渲染过程，调用glutSwapBuffers交换前后台缓冲区
             */
            glutSwapBuffers();
        }
        
        int main(int argc, char* argv[])
        {
            // 设置当前工作目录，针对MAC OS
            gltSetWorkingDirectory(argv[0]);
            // 初始化glut库
            glutInit(&argc, argv);
            // 初始化渲染模式，双缓冲窗口、颜色模式、深度测试、模板缓冲区
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
            glutInitWindowSize(800, 600);
            glutCreateWindow("Triangle");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            // 确保驱动程序的初始化成功
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                fprintf(stderr, "glew error:%s\n", glewGetErrorString(err));
                return 1;
            }
            SetupRC();
            glutMainLoop();
            return 0;
        }
    }
}
