 #include <GLTools.h>
 #include <GLShaderManager.h>
 #include <GLBatch.h>

 #ifdef __APPLE__
 #include <glut/glut.h>
 #else
 #define FREEGLUT_STATIC
 #include <GL/glut.h>
 #endif

namespace Ch06 {
    namespace ShadedTriangle_jingz {
        GLBatch triangleBatch;
        GLShaderManager shaderManager;
        GLint myIdentityShader;
        
        
        void ChangeSize(int w, int h)
        {
            if (h <= 0)
            {
                h = 1;
            }
            
            glViewport(0, 0, w, h);
            
        }
        
        void SetupRC(void)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            shaderManager.InitializeStockShaders();
            
            GLfloat vVerts[] = {   -0.5f, 0.0f, 0.0f,
                0.5f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f
            };
            
            GLfloat vColors[] = {   1.0f, 0.0f, 0.0f,1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
            };
            
            triangleBatch.Begin(GL_TRIANGLES,3);
            triangleBatch.CopyVertexData3f(vVerts);
            triangleBatch.CopyColorData4f(vColors);
            triangleBatch.End();
            
            myIdentityShader = gltLoadShaderPairWithAttributes("ShadedTriangle.vp", "ShadedTriangle.fp", 2
                                                               , GLT_ATTRIBUTE_VERTEX, "vVertex"
                                                               , GLT_ATTRIBUTE_COLOR, "vColor");//�ֱ������������ɫ��������Ϊ��Σ�����GLT_ATTRIBUTE_VERTEX �������ݴ���������ɫ������ɫ���ݴ���Ƭ����ɫ��
            //glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
        }
        
        void ShutdownRC(void)
        {
            glDeleteProgram(myIdentityShader);
        }
        
        void RenderScene(void)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            
            glUseProgram(myIdentityShader);
            triangleBatch.Draw();
            glutSwapBuffers();
        }
        
        
        
        int main(int argc,char * argv[])
        {
            gltSetWorkingDirectory(argv[0]);
            
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
            
            glutInitWindowSize(800, 600);
            
            glutCreateWindow("Shaded Triangle");
            glutReshapeFunc(ChangeSize);
            glutDisplayFunc(RenderScene);
            
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
                return 1;
            }
            
            SetupRC();
            
            glutMainLoop();
            
            ShutdownRC();
            
            return 0;
        }
    }
}
