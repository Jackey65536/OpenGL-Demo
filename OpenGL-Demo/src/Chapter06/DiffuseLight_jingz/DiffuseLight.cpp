 #include <GLTools.h>
 #include <GLMatrixStack.h>
 #include <GLGeometryTransform.h>
 #include <GLFrame.h>
 #include <GLFrustum.h>
 #include <GLShaderManager.h>
 #include <StopWatch.h>
 #include <math.h>

 #ifdef __APPLE__
 #include <glut/glut.h>
 #else
 #define FREEGLUT_STATIC
 #include <GL/glut.h>
 #endif

namespace Ch06 {
    namespace DiffuseLight_jingz {
        GLFrame viewFrame;
        GLFrustum viewFrustum;
        GLMatrixStack modelViewMatrix;
        GLMatrixStack projectionMatrix;
        GLGeometryTransform transformPipeline;
        
        GLShaderManager shaderManager;
        
        GLuint diffuseLightShader;
        GLTriangleBatch sphereBatch;
        
        GLint locColor;
        GLint locLight;
        GLint locMVP;
        GLint locMV;
        GLint locNM;
        
        
        void SetupRC(void)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            
            shaderManager.InitializeStockShaders();
            
            viewFrame.MoveForward(4.0f);
            
            gltMakeSphere(sphereBatch,1.0f,26,13);
            
            diffuseLightShader = gltLoadShaderPairWithAttributes("DiffuseLight.vp", "DiffuseLight.fp", 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
            
            locColor = glGetUniformLocation(diffuseLightShader, "diffuseColor");
            locLight = glGetUniformLocation(diffuseLightShader, "vLightPosition");
            locMVP = glGetUniformLocation(diffuseLightShader, "mvpMatrix");
            locMV = glGetUniformLocation(diffuseLightShader, "mvMatrix");
            locNM = glGetUniformLocation(diffuseLightShader, "normalMatrix");
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
            
            transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
        }
        
        void ShutdownRC(void)
        {
            glDeleteProgram(diffuseLightShader);
        }
        
        void RenderScene(void)
        {
            static CStopWatch rotTimer;
            
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            
            modelViewMatrix.PushMatrix(viewFrame);
            
            modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 60.0f, 0.0f, 1.0f, 0.0f);
            
            GLfloat vDiffuseColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
            
            GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
            
            glUseProgram(diffuseLightShader);
            
            glUniform4fv(locColor, 1, vDiffuseColor);
            glUniform3fv(locLight, 1, vEyeLight);
            
            glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
            glUniformMatrix4fv(locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
            glUniformMatrix3fv(locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
            
            sphereBatch.Draw();
            
            modelViewMatrix.PopMatrix();
            
            glutSwapBuffers();
            
            glutPostRedisplay();
        }
        
        int main(int argc, char * argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
            glutInitWindowSize(800, 600);
            glutCreateWindow("DiffuseLight Jingz");
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
