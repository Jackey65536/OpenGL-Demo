#include <GLTools.h>
#include <GLShaderManager.h>
#include <glut/glut.h>

namespace Demo {
    namespace Blending {
        GLBatch squareBatch;
        GLBatch greenBatch;
        GLBatch redBatch;
        GLBatch blueBatch;
        GLBatch blackBatch;
        
        GLShaderManager shaderManager;
        
        GLfloat blockSize = 0.2f;
        GLfloat vVerts[] = {
            -blockSize, -blockSize, 0.0f,
            blockSize, -blockSize, 0.0f,
            blockSize, blockSize, 0.0f,
            -blockSize, blockSize, 0.0f
        };
        
        void SetupRC()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            shaderManager.InitializeStockShaders();
            // 创建移动矩形批次
            squareBatch.Begin(GL_TRIANGLE_FAN, 4);
            squareBatch.CopyVertexData3f(vVerts);
            squareBatch.End();
            
            // 绿色矩形批次
            GLfloat vBlock[] = {
                0.25f, 0.25f, 0.0f,
                0.75f, 0.25f, 0.0f,
                0.75f, 0.75f, 0.0f,
                0.25f, 0.75f, 0.0f,
            };
            greenBatch.Begin(GL_TRIANGLE_FAN, 4);
            greenBatch.CopyVertexData3f(vBlock);
            greenBatch.End();
            
            // 红色矩形批次
            GLfloat vBlock2[] = {
                -0.75f, 0.25f, 0.0f,
                -0.25f, 0.25f, 0.0f,
                -0.25f, 0.75f, 0.0f,
                -0.75f, 0.75f, 0.0f,
            };
            redBatch.Begin(GL_TRIANGLE_FAN, 4);
            redBatch.CopyVertexData3f(vBlock2);
            redBatch.End();
            
            // 蓝色矩形批次
            GLfloat vBlock3[] = {
                -0.75f, -0.75f, 0.0f,
                -0.25f, -0.75f, 0.0f,
                -0.25f, -0.25f, 0.0f,
                -0.75f, -0.25f, 0.0f
            };
            blueBatch.Begin(GL_TRIANGLE_FAN, 4);
            blueBatch.CopyVertexData3f(vBlock3);
            blueBatch.End();
            
            // 黑色矩形批次
            GLfloat vBlock4[] = {
                0.25f, -0.75f, 0.0f,
                0.75f, -0.75f, 0.0f,
                0.75f, -0.25f, 0.0f,
                0.25f, -0.25f, 0.0f
            };
            blackBatch.Begin(GL_TRIANGLE_FAN, 4);
            blackBatch.CopyVertexData3f(vBlock4);
            blackBatch.End();
        }
        
        // 特殊按键监听
        void SpecialKeys(int key, int x, int y)
        {
            GLfloat stepSize = 0.025f;
            
            //左上角的 X 坐标和右下角的 Y 坐标
            GLfloat blockX = vVerts[0];
            GLfloat blockY = vVerts[7];
            
            //根据移动方向移动位置
            switch (key) {
                case GLUT_KEY_UP: blockY += stepSize; break;
                case GLUT_KEY_DOWN: blockY -= stepSize; break;
                case GLUT_KEY_LEFT: blockX -= stepSize; break;
                case GLUT_KEY_RIGHT: blockX += stepSize; break;
                default: break;
            }
            
            //移动边界处理
            if(blockX < -1.0f) blockX = -1.0f;
            if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;;
            if(blockY < -1.0f + blockSize * 2)  blockY = -1.0f + blockSize * 2;
            if(blockY > 1.0f) blockY = 1.0f;
            
            //矩形四个顶点位置
            vVerts[0] = blockX;
            vVerts[1] = blockY - blockSize*2;
            vVerts[3] = blockX + blockSize*2;
            vVerts[4] = blockY - blockSize*2;
            vVerts[6] = blockX + blockSize*2;
            vVerts[7] = blockY;
            vVerts[9] = blockX;
            vVerts[10] = blockY;
            
            //批次顶点数据编号
            squareBatch.CopyVertexData3f(vVerts);
            
            //触发渲染
            glutPostRedisplay();
        }
        
        void RenderScene(void)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            
            GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
            GLfloat vGreen[] = {0.0f, 1.0f, 0.0f, 1.0f};
            GLfloat vBlue[] = {0.0f, 0.0f, 1.0f, 0.6f};
            GLfloat vBlack[] = {0.0f, 0.0f, 0.0f, 1.0f};
            
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
            greenBatch.Draw();
            
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
            redBatch.Draw();
            
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlue);
            blueBatch.Draw();
            
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlack);
            blackBatch.Draw();
            
            // 开启颜色混合
            glEnable(GL_BLEND);
            // 设置颜色混合方程式
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlue);
            squareBatch.Draw();
            // 关闭颜色混合
            glDisable(GL_BLEND);
            glutSwapBuffers();
        }
        
        void ChangeSize(int w, int h)
        {
            glViewport(0, 0, w, h);
        }
        
        int main(int argc, char* argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
            glutInitWindowSize(800, 600);
            glutCreateWindow("Move Block with arrow keys to see blending");
            
            glutReshapeFunc(ChangeSize);
            glutSpecialFunc(SpecialKeys);
            glutDisplayFunc(RenderScene);
            
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

