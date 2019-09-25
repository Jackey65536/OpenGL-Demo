 #include <GLTools.h>
 #include <GLMatrixStack.h>
 #include <GLFrame.h>
 #include <GLFrustum.h>
 #include <GLGeometryTransform.h>
 #include <GLShaderManager.h>
 #include <StopWatch.h>

 #ifdef __APPLE__
 #include <glut/glut.h>
 #else
 #define FREEGLUT_STATIC
 #include <GL/glut.h>
 #endif

namespace Ch06 {
    namespace Littexture_jingz {
        GLFrame viewFrame;
        GLFrustum viewFrustum;
        GLMatrixStack projectionMatrix;
        GLMatrixStack mvpMatrix;
        GLMatrixStack mvMatrix;
        GLGeometryTransform transformPipeLine;
        GLShaderManager shaderManager;
        
        GLTriangleBatch sphereBatch;
        
        GLuint ADSTextureShader;
        GLuint textureID;
        
        GLint locAC;
        GLint locDC;
        GLint locSC;
        GLint locLP;
        GLint locMVP;
        GLint locMV;
        GLint locNM;
        GLint locTexture;
        
        bool LoadTGATexture(const char * szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
        {
            GLbyte * pBits;
            
            int nWidth, nHeight, nComponent;
            
            GLenum eFormat;
            
            pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponent, &eFormat);
            
            if (pBits == NULL)
            {
                return false;
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            
            glTexImage2D(GL_TEXTURE_2D, 0, nComponent, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);
            
            free(pBits);
            
            if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || magFilter == GL_LINEAR_MIPMAP_LINEAR || magFilter == GL_LINEAR_MIPMAP_NEAREST)
            {
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            
            return true;
        }
        
        void SetupRC(void)
        {
            //�Ȼ��Ʊ���
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            glEnable(GL_DEPTH_TEST);
            
            glEnable(GL_CULL_FACE);
            
            shaderManager.InitializeStockShaders();
            
            viewFrame.MoveForward(4.0f);
            
            gltMakeSphere(sphereBatch, 1.0f, 26, 13);
            //������ͷ�������������������ɫ���У��������ֱ�Ϊ��vVertex��vNormal
            ADSTextureShader = shaderManager.LoadShaderPairWithAttributes("LitTexture.vp", "LitTexture.fp", 3, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal", GLT_ATTRIBUTE_TEXTURE0, "vTexture0");//����ָ���Ͻ׶�Ҫ����atrributer������������صĲ���û����Ӧ
            
            locAC = glGetUniformLocation(ADSTextureShader, "ambientColor");
            locDC = glGetUniformLocation(ADSTextureShader, "diffuseColor");
            locSC = glGetUniformLocation(ADSTextureShader, "specularColor");
            locLP = glGetUniformLocation(ADSTextureShader, "vLightPosition");
            locMVP = glGetUniformLocation(ADSTextureShader, "mvpMatrix");
            locMV = glGetUniformLocation(ADSTextureShader, "mvMatrix");
            locNM = glGetUniformLocation(ADSTextureShader, "normalMatrix");
            locTexture = glGetUniformLocation(ADSTextureShader, "colorMap");
            
            glGenTextures(1, &textureID);
            
            glBindTexture(GL_TEXTURE_2D, textureID);
            
            LoadTGATexture("CoolTexture.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
            
        }
        
        void ChangeSize(int w, int h)
        {
            if (h <= 0)
            {
                h = 1;
            }
            
            glViewport(0, 0, w, h);
            viewFrustum.SetPerspective(35, float(w) / float(h), 1.0f, 100.0f);
            projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
            transformPipeLine.SetMatrixStacks(mvMatrix, projectionMatrix);
            
        }
        
        void RenderScene(void)
        {
            static CStopWatch rotTimer;
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            mvMatrix.PushMatrix(viewFrame);
            {
                mvMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
                
                GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
                
                GLfloat vDiffuseColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
                
                GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                
                GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
                
                glBindTexture(GL_TEXTURE_2D, textureID);
                glUseProgram(ADSTextureShader);
                
                glUniform4fv(locAC, 1, vAmbientColor);
                glUniform4fv(locDC, 1, vDiffuseColor);
                glUniform4fv(locSC, 1, vSpecularColor);
                glUniform3fv(locLP, 1, vEyeLight);
                
                glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeLine.GetModelViewProjectionMatrix());
                glUniformMatrix4fv(locMV, 1, GL_FALSE, transformPipeLine.GetModelViewMatrix());
                glUniformMatrix3fv(locNM, 1, GL_FALSE, transformPipeLine.GetNormalMatrix());
                
                glUniform1i(locTexture, 0);
                
                sphereBatch.Draw();
            }
            
            mvMatrix.PopMatrix();
            
            glutSwapBuffers();
            
            glutPostRedisplay();
        }
        
        void ShutdownRC(void)
        {
            glDeleteProgram(ADSTextureShader);
            glDeleteTextures(1, &textureID);
        }
        
        int main(int argc, char * argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
            glutInitWindowSize(800, 600);
            glutCreateWindow("ADSLitTureture Jingz");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            
            
            GLenum err = glewInit();
            
            if (err != GLEW_OK)
            {
                fprintf(stderr, "GLEW ERROR:%s\n", glewGetErrorString(err));
                return 1;
            }
            
            
            SetupRC();
            
            glutMainLoop();
            
            ShutdownRC();
            
            return 0;
        }
    }
}
