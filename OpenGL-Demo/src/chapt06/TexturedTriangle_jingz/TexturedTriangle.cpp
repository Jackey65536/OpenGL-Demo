// #include <GLTools.h>

// #include <GLShaderManager.h>

// #ifdef __APLE__
// #include <glut/glut.h>
// #else
// #define FREEGLUT_STATIC
// #include <GL/glut.h>
// #endif

// GLBatch triangleBatch;
// GLShaderManager shaderManger;


// GLuint myIdentityShader;
// GLuint textureID;

// GLint locColorMap;

// void ChangeSize(int w, int h)
// {
// 	glViewport(0, 0, w, h);
// }

// bool LoadTGATexture(const char * szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
// {
// 	GLbyte * pBits;

// 	int nWidth, nHeight, nComponent;

// 	GLenum eFormat;

// 	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponent, &eFormat);

// 	if (pBits == NULL)
// 	{
// 		return false;
// 	}

// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);

// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// 	glTexImage2D(GL_TEXTURE_2D, 0, nComponent, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

// 	free(pBits);

// 	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || magFilter == GL_LINEAR_MIPMAP_LINEAR || magFilter == GL_LINEAR_MIPMAP_NEAREST)
// 	{
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 	}

// 	return true;
// }

// void SetupRC(void)
// {
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	shaderManger.InitializeStockShaders();

// 	GLfloat vVerts[] = {
// 		-0.5f, 0.0f, 0.0f,
// 		0.5f, 0.0f, 0.0f,
// 		0.0f, 0.5f, 0.0f
// 	};

// 	GLfloat vTexCoords[] = {
// 		0.0f, 0.0f,
// 		1.0f, 0.0f,
// 		0.5f, 1.0f
// 	};
// 	triangleBatch.Begin(GL_TRIANGLES,3,1);
// 	triangleBatch.CopyVertexData3f(vVerts);
// 	triangleBatch.CopyTexCoordData2f(vTexCoords, 0);
// 	triangleBatch.End();

// 	myIdentityShader = shaderManger.LoadShaderPairWithAttributes("TexturedIdentity.vp", "TexturedIdentity.fp", 2, GLT_ATTRIBUTE_TEXTURE0, "vTexCoords", GLT_ATTRIBUTE_VERTEX, "vVertex");
	
// 	glGenTextures(1, &textureID);

// 	glBindTexture(GL_TEXTURE_2D, textureID);

// 	LoadTGATexture("stone.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

// 	locColorMap = glGetUniformLocation(myIdentityShader, "colorMap");
	
	
// }

// void RenderScene(void)
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
// 	glUseProgram(myIdentityShader);
// 	glUniform1i(locColorMap, 0);
// 	triangleBatch.Draw();
// 	glutSwapBuffers();
// }

// void ShutdownRC(void)
// {
// 	glDeleteProgram(myIdentityShader);
// 	glDeleteTextures(1,&textureID);
// }


// int main(int argc, char* argv[])
// {
// 	gltSetWorkingDirectory(argv[0]);

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
// 	glutInitWindowSize(800, 600);
// 	glutCreateWindow("Textured Triangle");
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