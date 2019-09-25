// #include <GLTools.h>
// #include <GLMatrixStack.h>
// #include <GLFrame.h>
// #include <GLFrustum.h>
// #include <GLGeometryTransform.h>
// #include <GLShaderManager.h>
// #include <StopWatch.h>

// #ifdef __APPLE__
// #include <glut/glut.h>
// #else
// #define FREEGLUT_STATIC
// #include <GL/glut.h>
// #endif

// GLFrame viewFrame;
// GLFrustum viewFrustum;
// GLMatrixStack projctionMatrix;
// GLMatrixStack modelViewMatrix;
// GLMatrixStack mvpMatrix;
// GLGeometryTransform transfromPipeLine;

// GLShaderManager shaderManager;
// GLTriangleBatch torusBatch;

// GLuint ADSDissolveShader;
// GLuint uiTexture;
// GLint locMV;
// GLint locMVP;
// GLint locNM;
// GLint locLightPosition;

// GLint locAmbient;
// GLint locDiffuse;
// GLint locSpec;
// GLint locCloudTex;
// GLint locDissolveFactor;

// void ChangeSize(int w, int h)
// {
// 	if (h <= 0)
// 	{
// 		h = 1;
// 	}

// 	glViewport(0, 0, w, h);
// 	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 100.0f);
// 	projctionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
// 	transfromPipeLine.SetMatrixStacks(modelViewMatrix, projctionMatrix);

// }

// bool LoadTGATexture(const char * szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
// {
// 	GLbyte * pBytes;
// 	GLint nWidth, nHeight, nComponets;
// 	GLenum eFormat;

// 	pBytes = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponets, &eFormat);
// 	if (pBytes == NULL)
// 	{
// 		return false;
// 	}
	
// 	/* ���԰ٶȰٿƣ������ҵĲ��ֻ��Ҫʹ�ðٶȾ�����������

// 	ͼ�������ͼ��ռ�ӳ�䵽֡����ͼ��ռ�(ӳ����Ҫ���¹�������ͼ��,�����ͻ����Ӧ�õ�������ϵ�ͼ��ʧ��),��ʱ�Ϳ���glTexParmeteri()������ȷ����ΰ���������ӳ�������.
// 	���ֲ�������˵������:
// ����glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
// ����GL_TEXTURE_2D: ����2D����.
// ����GL_TEXTURE_WRAP_S: S�����ϵ���ͼģʽ. 
// ����GL_CLAMP: ����������������0.0,1.0�ķ�Χ֮��.��������˻������.�������,ֻ�ǻ��Ե�������.
// ����glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
// ��������ͬ��,ֻ������T����
// ����glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// ����������������
// ����GL_TEXTURE_MAG_FILTER: �Ŵ����   ���������Ŵ�ʱʹ�õĹ��˺���
// ����GL_LINEAR: ���Թ���, ʹ�þ��뵱ǰ��Ⱦ�������������4�����ؼ�Ȩƽ��ֵ.
// ����glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
// ����GL_TEXTURE_MIN_FILTER: ��С���� ����������Сʱʹ�õĹ��˺���
// ����GL_LINEAR_MIPMAP_NEAREST: ʹ��GL_NEAREST����ӽ���ǰ����εĽ����ȵ������㼶��ͼ���в���,Ȼ����������ֵ�������Բ�ֵ.
// 	*/
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);


// 	/*
// 	//http://www.cnblogs.com/sunnyjones/articles/798237.html

// 	�@�������ǌ����� glDrawPixels ������, ���Ч�ʿ��], ����,

// 	OpenGL �A�O, ��o glDrawPixels �ĈD�n�Y��, ����ÿһ�� row �Ĵ�С ( �� byte ���� ), Ҳ�ǿ��Խo 4 ������.

// 	���O��ĈD�n�� 150x150, ÿһ�� row �Ĵ�С�͕��� 150 * 3 = 450 , 450 ���ܱ� 4 ������. ���Ҫ���а����Q�ɿ��Ա� 4 ����, һ�������, ������ÿһ�� row ��� 2 bytes �]��;���Y�� (�@�����E�҂��� padding ), ��� 450 �͕�׃�� 452, 452 �Ϳ��Ա� 4 ������.

// 	����, ÿ row ��С, ��Ҫ�Ƕ��ٵı���, �mȻ�A�O���� 4, ����, ���ǿ��԰����ĳ� 1, 2, 4, 8, ��������һ����, ������O�� 1, �@�N��Ϳ��Բ��ù� padding �Ć��}�� ( ���ʲ�N����Ҳ���Ա� 1 ����ѽ ), ����, ��ɢ�ĽY��, ���ǳ�ʽ run-time �r��һ�c�c.

// 	��õ�����, ��ԓֱ��ʹ�� �� �ɱ� 4 �����ĈD.

// 	*/
// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
// 	glTexImage2D(GL_TEXTURE_2D, 0, nComponets, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);

// 	free(pBytes);

// 	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST)
// 	{
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 	}

// 	return true;
// }

// void SetupRC(void)
// {
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	glEnable(GL_DEPTH_TEST);

// 	shaderManager.InitializeStockShaders();

// 	viewFrame.MoveForward(4.0f);

// 	gltMakeTorus(torusBatch, 0.8f, 0.25f, 52, 26);

// 	ADSDissolveShader = shaderManager.LoadShaderPairWithAttributes("Dissolve.vp", "Dissolve.fp", 3, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal", GLT_ATTRIBUTE_TEXTURE0, "vTexCoords0");

// 	//vp
// 	locMV = glGetUniformLocation(ADSDissolveShader, "mvMatrix");
// 	locMVP = glGetUniformLocation(ADSDissolveShader, "mvpMatrix");
// 	locNM = glGetUniformLocation(ADSDissolveShader, "normalMatrix");
// 	locLightPosition = glGetUniformLocation(ADSDissolveShader, "vLightPosition");


// 	//fp
// 	locAmbient = glGetUniformLocation(ADSDissolveShader, "ambientColor");
// 	locDiffuse = glGetUniformLocation(ADSDissolveShader, "diffuseColor");
// 	locSpec = glGetUniformLocation(ADSDissolveShader, "specularColor");
// 	locCloudTex = glGetUniformLocation(ADSDissolveShader, "cloudTexture");
// 	locDissolveFactor = glGetUniformLocation(ADSDissolveShader, "dissolveFactor");


// 	glGenTextures(1, &uiTexture);
// 	glBindTexture(GL_TEXTURE_2D, uiTexture); // 
// 	LoadTGATexture("Clouds.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

// }

// void RenderScene(void)
// {
// 	static CStopWatch rotTimer;
// 	static GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
// 	static GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
// 	static GLfloat vDiffuseColor[] = { 0.1f, 1.0f, 0.1f, 1.0f };
// 	static GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 	modelViewMatrix.PushMatrix(viewFrame);
// 	{
// 		modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f,0.0f,1.0f,0.0f);
// 		glUseProgram(ADSDissolveShader);
// 		//vp
// 		glUniformMatrix4fv(locMV, 1, GL_FALSE, transfromPipeLine.GetModelViewMatrix());
// 		glUniformMatrix4fv(locMVP, 1, GL_FALSE, transfromPipeLine.GetModelViewProjectionMatrix());
// 		glUniformMatrix3fv(locNM, 1, GL_FALSE, transfromPipeLine.GetNormalMatrix());
// 		glUniform3fv(locLightPosition, 1, vEyeLight);

// 		//fp
// 		glUniform4fv(locAmbient, 1, vAmbientColor);
// 		glUniform4fv(locDiffuse, 1, vDiffuseColor);
// 		glUniform4fv(locSpec, 1, vSpecularColor);
// 		glUniform1i(locCloudTex, 0);// ����

// 		float fFactor = fmod(rotTimer.GetElapsedSeconds(), 10.0f);
// 		fFactor /= 10.0f;
		
// 		glUniform1f(locDissolveFactor, fFactor);

// 		torusBatch.Draw();
// 	}
// 	modelViewMatrix.PopMatrix();

// 	glutSwapBuffers();

// 	glutPostRedisplay();

// }

// void ShutdownRC(void)
// {
// 	glDeleteTextures(1, &uiTexture);
// 	glDeleteProgram(ADSDissolveShader);
// }

// int main(int argc, char * argv[])
// {
// 	gltSetWorkingDirectory(argv[0]);

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
// 	glutInitWindowSize(800, 600);
// 	glutCreateWindow("Dissolve Jingz");
// 	glutReshapeFunc(ChangeSize);
// 	glutDisplayFunc(RenderScene);

// 	GLenum err = glewInit();
// 	if (GLEW_OK != err) {
// 		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
// 		return 1;
// 	}

// 	SetupRC();
// 	glutMainLoop();
// 	ShutdownRC();
// 	return 0;
// }