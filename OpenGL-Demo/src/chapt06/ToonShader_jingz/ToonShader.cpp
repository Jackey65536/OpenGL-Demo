// #include <GLTools.h>
// #include <GLMatrixStack.h>
// #include <GLGeometryTransform.h>
// #include <GLFrustum.h>
// #include <GLFrame.h>
// #include <GLTriangleBatch.h>
// #include <StopWatch.h>
//
//
// #ifdef __APPLE__
// #include <glut/glut.h>
// #else
// #define FREEGLUT_STATIC
// #include <GL/glut.h>
// #endif
//
// GLMatrixStack modelViewMatrix;
// GLMatrixStack mvpMatrix;
// GLMatrixStack projctionMatrix;
//
// GLFrustum viewFrustum;
// GLFrame viewFrame;
//
// GLGeometryTransform transformPipeLine;
// GLTriangleBatch torusBatch;
//
// GLuint toonShader;
// GLuint uiTexture;
//
// GLint locMV;
// GLint locMVP;
// GLint locNM;
// GLint locLP;
// GLint locColorTable;
//
// static  GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
//
// void ChangeSize(int w, int h)
// {
//     if (h <= 0)
//     {
//         h = 1;
//     }
//
//     glViewport(0, 0, w, h);
//     viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 100.0f);
//     projctionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//     transformPipeLine.SetMatrixStacks(modelViewMatrix, projctionMatrix);
//
// }
//
// void SetupRC(void)
// {
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//     glEnable(GL_DEPTH_TEST);
//
//     viewFrame.MoveForward(7.0f);
//
//     gltMakeTorus(torusBatch, 0.8f, 0.25f, 52, 26);
//
//     toonShader = gltLoadShaderPairWithAttributes("toonShader.vp", "toonShader.fp", 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
//
//     locMV = glGetUniformLocation(toonShader, "mvMatrix");
//     locMVP = glGetUniformLocation(toonShader, "mvpMatrix");
//     locNM = glGetUniformLocation(toonShader, "normalMatrix");
//     locLP = glGetUniformLocation(toonShader, "vLightPosition");
//     locColorTable = glGetUniformLocation(toonShader, "colorTable");
//
//     glGenTextures(1, &uiTexture);
//     glBindTexture(GL_TEXTURE_1D, uiTexture);
//
//     GLubyte textureData[4][3] = {
//         32, 0, 0,
//         64, 0, 0,
//         128, 0, 0,
//         255, 0, 0
//     };
//
//     glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
//     //todo
//
//     glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//
// }
//
// void RenderScene(void)
// {
//     static CStopWatch rotTimer;
//
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//     modelViewMatrix.PushMatrix(viewFrame);
//     {
//         modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.f, 0.0f, 1.0f, 0.0f);
//
//         glUseProgram(toonShader);
//
//         glUniformMatrix4fv(locMV, 1, GL_FALSE, transformPipeLine.GetModelViewMatrix());
//         glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeLine.GetModelViewProjectionMatrix());
//         glUniformMatrix3fv(locNM, 1, GL_FALSE, transformPipeLine.GetNormalMatrix());
//         glUniform3fv(locLP, 1, vEyeLight);
//
//         glUniform1i(locColorTable, 0);
//
//         torusBatch.Draw();
//     }
//     modelViewMatrix.PopMatrix();
//
//     glutSwapBuffers();
//
//     glutPostRedisplay();
// }
//
// void ShutdownRC(void)
// {
//
// }
//
// int main(int argc, char * argv[])
// {
//     gltSetWorkingDirectory(argv[0]);
//
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GL_DOUBLE | GL_DEPTH | GL_STENCIL);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("ToonShader Jingz");
//     glutReshapeFunc(ChangeSize);
//     glutDisplayFunc(RenderScene);
//
//     GLenum err = glewInit();
//     if (err != GLEW_OK)
//     {
//         fprintf(stderr, "GLEW ERROR:%s\n", glewGetErrorString(err));
//         return 1;
//     }
//
//     SetupRC();
//
//     glutMainLoop();
//
//     ShutdownRC();
//
//     return 0;
// }
