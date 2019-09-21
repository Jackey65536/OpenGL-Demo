#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <glut/glut.h>

#include <math.h>
#include <stdio.h>

// 着色器
GLShaderManager shaderManager;
// 视图矩阵堆栈
GLMatrixStack modelViewMatrix;
// 投影矩阵堆栈
GLMatrixStack projectionMatrix;
// 视景体
GLFrustum viewFrustum;
// 照相机角色
GLFrame cameraFrame;
// 变换管线
GLGeometryTransform transformPipeline;
// 花托批次
GLTriangleBatch torusBatch;
// 地板批次
GLBatch floorBatch;
// 旋转小球批次
GLTriangleBatch sphereBatch;

// 随机小球群
#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];

// 定义3个纹理标识
#define TEXTURE_MARBLE      0
#define TEXTURE_MARSLIKE    1
#define TEXTURE_MOONLIKE    2
#define TEXTURE_COUNT       3

// 纹理标识数组
GLuint uiTextures[TEXTURE_COUNT];
// 纹理文件名数组
const char *szTextureFiles[TEXTURE_COUNT] = { "Marble.tga", "Marslike.tga", "MoonLike.tga" };

// 从头 TGA 文件中加载纹理数据
bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    GLbyte *pBits;
    int nWidth, nHeight, nComponents;
    GLenum eFormat;
    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
    if (pBits == NULL) {
        return false;
    }
    // 设置环绕模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    
    // 设置缩小和放大过滤器
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    // 设置纹理压缩
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // 加载纹理数据到2维纹理缓冲区
    glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);
    
    // 释放纹理数据
    free(pBits);
    
    // 判断缩小过滤器是否是 Mip 贴图缩小过滤器，是则开启 Mip 贴图功能
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);
    
    return true;
}

// 加载所有纹理数据
void LoadAllTextureData() {
    // 申请纹理数据标识
    glGenTextures(TEXTURE_COUNT, uiTextures);
    
    // 加载 Marble 纹理
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MARBLE]);
    LoadTGATexture(szTextureFiles[TEXTURE_MARBLE], GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    
    // 加载 Mars 纹理
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MARSLIKE]);
    LoadTGATexture(szTextureFiles[TEXTURE_MARSLIKE], GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    
    // 加载 Moon 纹理
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MOONLIKE]);
    LoadTGATexture(szTextureFiles[TEXTURE_MOONLIKE], GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

// 程序初始化
void SetupRC() {
    // 设置窗口背景颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // 初始化着色器
    shaderManager.InitializeStockShaders();
    
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
    // 开启背面剔除，用于地板镜像效果实现
    glEnable(GL_CULL_FACE);
    
    // 得到花托批次数据
    gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
    
    // 得到旋转小球批次数据
    gltMakeSphere(sphereBatch, 0.1f, 26, 13);
    
    // 得到地板批次数据
    GLfloat texSize = 10.0f;
    floorBatch.Begin(GL_TRIANGLE_FAN, 4, 1);
    floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    floorBatch.Vertex3f(-20.0f, -0.41f, 20.0f);
    
    floorBatch.MultiTexCoord2f(0, texSize, 0.0f);
    floorBatch.Vertex3f(20.0f, -0.41f, 20.0f);
    
    floorBatch.MultiTexCoord2f(0, texSize, texSize);
    floorBatch.Vertex3f(20.0f, -0.41f, -20.0f);
    
    floorBatch.MultiTexCoord2f(0, 0.0f, texSize);
    floorBatch.Vertex3f(-20.0f, -0.41f, -20.0f);
    floorBatch.End();
    
    // 随机小球群位置数据生成
    for(int i = 0; i < NUM_SPHERES; i++) {
        GLfloat x = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        GLfloat z = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        spheres[i].SetOrigin(x, 0.0f, z);
    }
    
    // 加载所有纹理数据
    LoadAllTextureData();
}

// 程序资源释放
void ShutdownRC(void) {
    glDeleteTextures(TEXTURE_COUNT, uiTextures);
}

// 绘制球体世界除开地板外的所有物体
void DrawSongAndDance(GLfloat yRot) {
    static GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static GLfloat vLightPos[] = { 0.0f, 3.0f, 0.0f, 1.0f };
    
    // 获取点光源位置
    M3DMatrix44f mCamera;
    M3DVector4f vLightEyePos;
    modelViewMatrix.GetMatrix(mCamera);
    m3dTransformVector4(vLightEyePos, vLightPos, mCamera);
    
    // 绘制随机小球群，这里的做法是瞬间切换当前角色位置并开始绘制小球，然后切换回原来角色位置
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MOONLIKE]);
    for(int i = 0; i < NUM_SPHERES; i++) {
        // 保存当前矩阵状态，为了能切换回原来的角色位置
        modelViewMatrix.PushMatrix();
        // 调整当前角色位置为随机生成小球的位置
        modelViewMatrix.MultMatrix(spheres[i]);
        // 绘制随机小球
        shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(),
                                     transformPipeline.GetProjectionMatrix(), vLightEyePos, vWhite, 0);
        sphereBatch.Draw();
        // 还原矩阵状态，切换为原来角色位置
        modelViewMatrix.PopMatrix();
    }
    
    // 视图矩阵进行平移
    modelViewMatrix.Translate(0.0f, 0.2f, -2.5f);
    // 保持旋转前的视图矩阵，因为如果不在旋转前保存，会导致旋转小球也会带上花托的旋转
    modelViewMatrix.PushMatrix();
    // 继续进行旋转
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    
    // 绘制中间花托圆环
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MARSLIKE]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vWhite, 0);
    torusBatch.Draw();
    
    // 恢复到旋转前的视图矩阵
    modelViewMatrix.PopMatrix();
    
    // 绘制旋转小球
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MOONLIKE]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vWhite, 0);
    sphereBatch.Draw();
}

// 窗口渲染回调
void RenderScene(void) {
    
    // 获取2次渲染之间的时间间隔
    static CStopWatch rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    static GLfloat vFloorColor[] = { 1.0f, 1.0f, 1.0f, 0.75f };
    
    // 清空缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 压入照相机矩阵
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);
    
    // 绘制地板镜像，Y 轴反转实现镜像效果
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Scale(1.0f, -1.0f, 1.0f);
    modelViewMatrix.Translate(0.0f, 0.8f, 0.0f);
    glFrontFace(GL_CW);
    DrawSongAndDance(yRot);
    glFrontFace(GL_CCW);
    modelViewMatrix.PopMatrix();
    
    // 开启颜色混合，使地板镜像和地板融合一体
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, uiTextures[TEXTURE_MARBLE]);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor, 0);
    floorBatch.Draw();
    glDisable(GL_BLEND);
    
    // 绘制地板上面的球体世界
    DrawSongAndDance(yRot);
    
    // 出栈，恢复成原始矩阵
    modelViewMatrix.PopMatrix();
    
    // 因为是双缓冲区模式，后台缓冲区替换到前台缓存区进行显示
    glutSwapBuffers();
    
    // 自动触发渲染，达到动画效果
    glutPostRedisplay();
}

// 特殊按键点击回调
void SpecialKeys(int key, int x, int y) {
    float linear = 0.1f;
    float angular = float(m3dDegToRad(5.0f));
    
    // 控制角色向前后移动
    if(key == GLUT_KEY_UP)
        cameraFrame.MoveForward(linear);
    
    if(key == GLUT_KEY_DOWN)
        cameraFrame.MoveForward(-linear);
    
    // 控制角色向左右旋转
    if(key == GLUT_KEY_LEFT)
        cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

// 窗口变换回调
void ChangeSize(int width, int height) {
    
    // 防止除数为0
    if(height == 0)
        height = 1;
    
    // 设置视口
    glViewport(0, 0, width, height);
    
    // 设置透视投影
    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 100.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // 设置变换管线的矩阵堆栈
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

// 程序入口
int main(int argc, char* argv[]) {
    // 设置 Mac OS 工作目录路径
    gltSetWorkingDirectory(argv[0]);
    
    // GLUT初始化
    glutInit(&argc, argv);
    
    // 设置渲染模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    // 初始化窗口大小
    glutInitWindowSize(600, 600);
    
    // 创建窗口并命名
    glutCreateWindow("OpenGL SphereWorld");
    
    // 判断驱动程序是否初始化完毕
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    // 窗口变化回调函数设置
    glutReshapeFunc(ChangeSize);
    
    // 窗口渲染回调函数设置
    glutDisplayFunc(RenderScene);
    
    // 特殊按键回调函数设置
    glutSpecialFunc(SpecialKeys);
    
    // 初始化环境
    SetupRC();
    
    // 主消息循环
    glutMainLoop();
    
    // 程序资源释放
    ShutdownRC();
    
    return 0;
}
