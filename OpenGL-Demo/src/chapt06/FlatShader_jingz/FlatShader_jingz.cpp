// #include <GLTools.h>
// #include <GLMatrixStack.h>
// #include <StopWatch.h>
// #include <GLFrame.h>
// #include <GLFrustum.h>
// #include <GLGeometryTransform.h>

// #include <GLTriangleBatch.h>
// #include <math.h>


// #ifdef __APPLE__
// #include <glut/glut.h>
// #else
// #define FREEGLUT_STATIC
// #include <GL/glut.h>
// #endif

// GLFrame viewFrame;
// GLFrustum viewFrustum;
// GLMatrixStack modelViewMatrix;
// GLMatrixStack projectionMatrix;
// GLGeometryTransform transformPipeline;
// GLTriangleBatch torusBatch;


// GLint locMVP;
// GLint locColor;
// GLuint flatShader;

// void SetupRC(void)
// {
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// 	glEnable(GL_DEPTH_TEST);
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

// 	viewFrame.MoveForward(4.0f);

// 	gltMakeTorus(torusBatch, 0.80f, 0.25f, 52, 26);

// 	flatShader = gltLoadShaderPairWithAttributes("FlatShader.vp", "FlatShader.fp", 1, GLT_ATTRIBUTE_VERTEX, "vVertex");
// 	//����ָ�򣬽ű���Ҫ������Щ����
// 	locMVP = glGetUniformLocation(flatShader, "mvpMatrix");
// 	locColor = glGetUniformLocation(flatShader, "vColorValue");
// }

// void ChangeSize(int w, int h)
// {
// 	if (h <= 0)
// 	{
// 		h = 1;
// 	}

// 	glViewport(0, 0, w, h);

// 	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 100.0f);

// 	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

// 	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

// }

// void RenderScene(void)
// {
// 	static CStopWatch rotTimer;
// 	float yRot = rotTimer.GetElapsedSeconds() * 10.f;

// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

// 	modelViewMatrix.PushMatrix(viewFrame);

// 	modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);

// 	GLfloat vColor[] = { 0.1f, 0.1f, 1.0f, 1.0f };

// 	glUseProgram(flatShader);

// 	//��ֵ
// 	glUniform4fv(locColor, 1, vColor);

// 	glUniformMatrix4fv(locMVP, 1, GL_FALSE,transformPipeline.GetModelViewProjectionMatrix());

// 	torusBatch.Draw();

// 	modelViewMatrix.PopMatrix();

// 	glutSwapBuffers();

// 	glutPostRedisplay();
// }

// void ShutdownRC()
// {
// 	glDeleteProgram(flatShader);
// }


// int main(int argc, char * argv[])
// {
// 	gltSetWorkingDirectory(argv[0]);

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
// 	glutInitWindowSize(800, 600);
// 	glutCreateWindow("Simple Transformed Geometry");
// 	glutReshapeFunc(ChangeSize);
// 	glutDisplayFunc(RenderScene);

// 	GLenum err = glewInit();
// 	if (err != GLEW_OK)
// 	{
// 		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
// 		return 1;
// 	}

// 	SetupRC();

// 	glutMainLoop();

// 	ShutdownRC();

// 	return 0;
// }