#include <GLTools.h>    // OpenGL toolkit
#include <GLFrustum.h>
#include <glut/glut.h>

namespace Demo {
    namespace Smoother {
        GLShaderManager shaderManager;
        GLFrustum viewFrustum;
        GLBatch smallStarBatch;
        GLBatch mediumStarBatch;
        GLBatch largeStarBatch;
        GLBatch mountainRangeBatch;
        GLBatch moonBatch;
        
        //常量宏
#define SMALL_STARS     100
#define MEDIUM_STARS     40
#define LARGE_STARS      15
        
#define SCREEN_X        800
#define SCREEN_Y        600
        
        //点击菜单选项触发的回调方法
        void ProcessMenu(int value) {
            switch(value) {
                case 1:
                    //开启抗锯齿处理，必须先开启颜色混合模式
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable(GL_BLEND);
                    //点抗锯齿
                    glEnable(GL_POINT_SMOOTH);
                    // glHint函数允许我们指定关心渲染速度还是输出质量
                    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
                    //线抗锯齿
                    glEnable(GL_LINE_SMOOTH);
                    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
                    //多边形抗锯齿
                    glEnable(GL_POLYGON_SMOOTH);
                    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
                    break;
                case 2:
                    //关闭抗锯齿处理
                    glDisable(GL_BLEND);
                    glDisable(GL_LINE_SMOOTH);
                    glDisable(GL_POINT_SMOOTH);
                    glDisable(GL_POLYGON_SMOOTH);
                    break;
                default:
                    break;
            }
            
            //触发渲染
            glutPostRedisplay();
        }
        
        //渲染画面
        void RenderScene(void) {
            //清除缓存区
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            //设置着色器为单位黑色
            GLfloat vWhite [] = { 1.0f, 1.0f, 1.0f, 1.0f };
            shaderManager.UseStockShader(GLT_SHADER_FLAT, viewFrustum.GetProjectionMatrix(), vWhite);
            
            //画小点
            glPointSize(1.0f);
            smallStarBatch.Draw();
            
            //画大点
            glPointSize(4.0f);
            mediumStarBatch.Draw();
            
            //画超大点
            glPointSize(8.0f);
            largeStarBatch.Draw();
            
            //画月亮
            moonBatch.Draw();
            
            //画山的轮廓
            glLineWidth(3.5);
            mountainRangeBatch.Draw();
            
            //将在后台缓冲区进行渲染，然后在结束时交换到前台
            glutSwapBuffers();
        }
        
        //初始化小点批次
        void SetupSmallStarBatch() {
            M3DVector3f vVerts[SMALL_STARS];
            for(int i = 0; i < SMALL_STARS; i++) {
                vVerts[i][0] = (GLfloat)(rand() % SCREEN_X);
                vVerts[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)) + 100.0f;
                vVerts[i][2] = 0.0f;
            }
            smallStarBatch.Begin(GL_POINTS, SMALL_STARS);
            smallStarBatch.CopyVertexData3f(vVerts);
            smallStarBatch.End();
        }
        
        //初始化大点批次
        void SetupMeiumStarBatch() {
            M3DVector3f vVerts[MEDIUM_STARS];
            for(int i = 0; i < MEDIUM_STARS; i++) {
                vVerts[i][0] = (GLfloat)(rand() % SCREEN_X);
                vVerts[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)) + 100.0f;
                vVerts[i][2] = 0.0f;
            }
            
            mediumStarBatch.Begin(GL_POINTS, MEDIUM_STARS);
            mediumStarBatch.CopyVertexData3f(vVerts);
            mediumStarBatch.End();
        }
        
        //初始化超大点批次
        void SetupLargeStarBatch() {
            M3DVector3f vVerts[LARGE_STARS];
            for(int i = 0; i < LARGE_STARS; i++) {
                vVerts[i][0] = (GLfloat)(rand() % SCREEN_X);
                vVerts[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)) + 100.0f;
                vVerts[i][2] = 0.0f;
            }
            
            largeStarBatch.Begin(GL_POINTS, LARGE_STARS);
            largeStarBatch.CopyVertexData3f(vVerts);
            largeStarBatch.End();
        }
        
        //初始化山轮廓批次
        void SetupMountainRangeBatch() {
            M3DVector3f vMountains[12] = {
                0.0f, 25.0f, 0.0f,
                50.0f, 100.0f, 0.0f,
                100.0f, 25.0f, 0.0f,
                225.0f, 125.0f, 0.0f,
                300.0f, 50.0f, 0.0f,
                375.0f, 100.0f, 0.0f,
                460.0f, 25.0f, 0.0f,
                525.0f, 100.0f, 0.0f,
                600.0f, 20.0f, 0.0f,
                675.0f, 70.0f, 0.0f,
                750.0f, 25.0f, 0.0f,
                800.0f, 90.0f, 0.0f
            };
            
            mountainRangeBatch.Begin(GL_LINE_STRIP, 12);
            mountainRangeBatch.CopyVertexData3f(vMountains);
            mountainRangeBatch.End();
        }
        
        //初始化月亮批次
        void SetupMoonBatch() {
            GLfloat x = 700.0f;
            GLfloat y = 500.0f;
            GLfloat r = 50.0f;
            M3DVector3f vVerts[SMALL_STARS];
            int nVerts = 0;
            vVerts[nVerts][0] = x;
            vVerts[nVerts][1] = y;
            vVerts[nVerts][2] = 0.0f;
            for(GLfloat angle = 0; angle < M3D_2PI; angle += 0.2f) {
                nVerts++;
                vVerts[nVerts][0] = x + float(cos(angle)) * r;
                vVerts[nVerts][1] = y + float(sin(angle)) * r;
                vVerts[nVerts][2] = 0.0f;
            }
            nVerts++;
            vVerts[nVerts][0] = x + r;;
            vVerts[nVerts][1] = y;
            vVerts[nVerts][2] = 0.0f;
            
            moonBatch.Begin(GL_TRIANGLE_FAN, 34);
            moonBatch.CopyVertexData3f(vVerts);
            moonBatch.End();
        }
        
        //程序化一次性初始化
        void SetupRC() {
            //设置背景色为黑色
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
            
            //初始化着色器
            shaderManager.InitializeStockShaders();
            
            //初始化各个图元批次
            SetupSmallStarBatch();
            SetupMeiumStarBatch();
            SetupLargeStarBatch();
            SetupMountainRangeBatch();
            SetupMoonBatch();
        }
        
        //窗口大小改变时接受新的宽度和高度
        void ChangeSize(int w, int h) {
            glViewport(0, 0, w, h);
            
            //正投影
            viewFrustum.SetOrthographic(0.0f, SCREEN_X, 0.0f, SCREEN_Y, -1.0f, 1.0f);
        }
        
        //程序入口
        int main(int argc, char* argv[]) {
            //设置当前工作目录，针对MAC OS X
            gltSetWorkingDirectory(argv[0]);
            
            //GLUT初始化
            glutInit(&argc, argv);
            
            /*初始化渲染模式，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
             双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区*/
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            
            //创建窗口大小、标题
            glutInitWindowSize(800, 600);
            glutCreateWindow("Smoothing Out The Jaggies");
            
            //创建菜单并绑定回调函数，添加选项，确定右键触发
            glutCreateMenu(ProcessMenu);
            glutAddMenuEntry("Antialiased Rendering",1);
            glutAddMenuEntry("Normal Rendering",2);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            //注册回调函数
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            
            //判断驱动是否正常
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
                return 1;
            }
            
            //初始化
            SetupRC();
            
            //运行循环
            glutMainLoop();
            return 0;
        }
        
        

    }
}
