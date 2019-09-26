#  第一章 3D图形和OpenGL简介
## 一、3D图形技术和术语
### 1、顶点（Vertex）、变换（Transformation）和投影（Projection）
#### 顶点：空间中的一个位置
#### 变换矩阵（Transformation Matrix）：对顶点进行数学结构处理
#### 投影矩阵（Projection Matrix）：用于将3D坐标转换成二维屏幕坐标
### 2、光栅化（Rasterization）
#### 实际绘制或填充每个顶点之间的像素形成线段就叫做光栅化
### 3、纹理贴图（Texture Mapping）
#### 一个纹理就是一副用来贴到三角形或者多边形上的图片
### 4、混合（Blending）
#### 混合时我们能够将不同的颜色混在一起
#### OpenGL 自学网站 [http://ogldev.atspace.co.uk/www/tutorial01/tutorial01.html](http://ogldev.atspace.co.uk/www/tutorial01/tutorial01.html)

## 二、坐标系统
### 1、2D笛卡尔坐标
#### 2D笛卡尔坐标：由一个x（水平方向）坐标和一个y（垂直方向）坐标构成
### 2、视口（ViewPort）
#### 裁剪区域的宽度和高度很少正好与窗口的宽度和高度（以像素为单位）相匹配。因此，坐标系统必须从逻辑笛卡尔坐标映射到物理屏幕像素坐标。视口就是窗口内部用于绘制裁剪区域的客户区域
### 3、图元（Primitives）
#### 图元是一位或二维的实体或表面，如点、直线、多边形
### 4、3D笛卡尔坐标
#### 在2D笛卡尔坐标系统上，添加一个深度分量（z轴）

## 三、投影
### 1、视景体（Viewing Volume）
#### 3D场景投影到2D图像之间的区域，视景体之外的任何物体都不会被绘制
### 2、正投影（Orthographic Projection）或平行投影
#### 实际带下相同的物体在屏幕上都具有相同的大小，不管他们是远是近。正投影的视景体是一个正方形或长方形
### 3、透视投影（Perspective Projection）
#### 在这种投影中，视景体后面的物体看上去比前面的物体更小些（近大远小），它的视景体是一个梯形，叫做平截头体（Frustum）。当靠近视景体后部的物体被投影到视景体的前部时，他们看上去就显得比较小


#  第二章 入门指南
## 一、OpenGL定义
#### OpenGL被定义为”图形硬件的一种软件接口“。从本质上说，它是一个3D图形和模型库。
### 二、工具库
#### 1、GLUT（OpenGL utility toolkit）：OpenGL的跨平台辅助函数库，freeglut已经崛起并取代了glut。
#### 2、GLEW：自动初始化所有新函数指针并保护所需类型定义、常量和枚举值得扩展加载库。
#### 3、GLTools：OpenGL作者写的一个工具箱


# 第三章 基础渲染
## 一、基础图形管线
### 1、客户机（CPU）-服务器（GPU）
#### 客户机不断地将数据块和命令块组合在一起并送入缓冲区，然后这些缓冲区会发送到服务器执行。
### 2、着色器（Shader）
#### 简化来讲，分两阶段：顶点着色器 -> 片段着色器
#### 顶点着色器处理从客户机输入的数据，应用变换，或者进行其他类型的数学运算来计算光照效果、位移、颜色值，等等。顶点着色器输出图元组合（Primitive Assembly），片段着色器会输出我们在屏幕上看到的最终颜色
> 忽略一些高大上的新着色器只考虑顶点、几何、片段着色器，管线总结为：顶点数据（Vertex）> 顶点着色器（Vertex Shader）> 图元装配（Assembly）> 几何着色器（Geometry Shader）> 光栅化（Rasterization）> 片段着色器（Fragment Shader）> 逐片段处理（Per-Fragment Operations）> 帧缓冲区（FrameBuffer）。再经过双缓冲的交换（SwapBuffer），渲染内容就显示到了屏幕上。


# 第四章 基础变换
## 一、理解变换
### 变换，是对坐标系的操作，比如：平移（glTranslatef）、旋转（glRotatef）、缩放（glScalef）
### 1、视觉坐标
#### 视觉坐标是相对于观察者的视角而言的，无论可能进行任何变换，我们都可以讲它们视为”绝对的“屏幕坐标。这样，视觉坐标就表示一个虚拟的固定坐标系，它通常作为参考坐标系使用。
### 2、视图变换
#### 指定观察者或照相机的位置，默认情况下，透视投影钟的观察点位于远点（0，0，0），并沿着z轴的负方向进行观察（向显示器内部”看进去“）。观察点相对于视觉坐标系进行移动，来提供特定的有利位置。
### 3、模型变换
#### 用于操纵模型和其中的特定对象。这些变换将对象移动到需要的位置，然后在对它们进行旋转和缩放。
### 4、投影变换
#### 投影变换将在模型视图变换之后应用到顶点上。这种投影实际上定义了视景体并创建了裁剪平面。
### 5、视口变换
#### 这是一种伪变换，只是对窗口上的最终输出进行缩放。


#  第五章 基础纹理
## 一、原始图像数据
### 1、像素包装
#### 改变或者恢复像素的存储方式
    void glPixelStorei(GLenum pname, GLint param); 
    void glPixelStoref(GLenum pname, GLfloat param);
### 2、像素图
#### 将颜色缓冲区的内容作为像素图直接读取
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
### 3、包装的像素格式
#### UNSIGNED_BYTE_3_3_2、UNSIGNED_BYTE_2_3_3_REV
### 4、保存像素
    GLint gltGrabScreenTGA(const char *szFileName)
### 5、读取像素
    GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat, GLbyte *pData)

## 二、载入纹理
### 在几何图形中应用纹理贴图时，第一个必要步骤就是讲纹理载入内存。一旦被载入，这些纹理就会成为当前纹理状态的一部分。
### 1、从磁盘文件读取纹理数据
    void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, void *data); 
#### 相应的还有 glTexImage2D，glTexImage3D
### 2、从颜色缓冲区加载纹理数据（一维和二维）
    void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border); 
#### 相应的还有 glCopyTexImage2D
### 3、更新纹理
    void glTexSubImage1D(GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, const GLvoid *data); 
#### 相应的还有 glTexSubImage2D、glTexSubImage3D
    void glCopyTexSubImage1D(Glenum target, GLint level, GLint xOffset, GLint x, GLint y, GLsizei width); 
#### 相应的还有 glCopyTexSubImage2D、glCopyTexSubImage3D
### 4、管理纹理对象
    void glGenTextures(GLsizei n, GLuint *textures);
    void glBindTexture(GLenum target, GLuint texture);
    void glDeleteTextures(GLsizei n, GLuint *textures);
    GLboolean glIsTexture(GLuint texture);

## 三、纹理应用
### 1、纹理坐标
#### 坐标 (s, t, r, q)，与定点坐标x、y、z、w相类似
### 2、纹理参数
    void glTexParameterf(GLenum target, GLenum pname, GLfloat param); // 设置纹理贴图参数
    void glTexParameteri(GLenum target, GLenum pname, GLint param);
    void glTexParameterfv(GLenum target, GLenum pname, GLfloat *param);
    void glTexParameteriv(GLenum target, GLenum pname, GLint *param);
#### 根据一个拉伸或收缩的纹理贴图计算颜色片段的过程称为纹理过滤（Texture Filtering）
#### 过滤器：GL_TEXTURE_MAG_FILTER、GL_TEXTURE_MIN_FLITER
#### 过滤方法：GL_NEAREST、GL_LINEAR

## 四、Mip 贴图
#### Mip贴图的原理是在加载纹理时加载本纹理图像在不同压缩尺度下的多幅纹理图像，从原始的纹理开始，依次降低纹理的宽高为上一个纹理的一半，直到最后纹理的面积为1*1为止。加载的一系列纹理图像类似于图像金字塔，在渲染上，OpenGL自动根据对象模型的状态加载不同等级的纹理对象。
### 1、Mip 贴图过滤
#### GL_FILTER_MIPMAP_SELECTOR，其中，FILTER 指定了被选择的 Mip 层将要使用的纹理过滤器，SELECTOR 则指定了如何选择 Mip 层。
### 2、生成 Mip 层
    void glGenerateMipmap(GLenum target);

## 五、各向异性过滤（Anisotropic texture filtering）
### 如果我们在进行纹理过滤时考虑了观察角度，那么这种过滤方法就称为各向异性过滤。
#### 1、确认支持各向异性过滤 GL_EXT_texture_filter_anisotropic
#### 2、查询支持的各向异性过滤的最大数量 
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &fLargest);
#### 3、设置想要应用的各向异性过滤的数量 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

## 六、纹理压缩
### 1、加载压缩纹理
    void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLint border, GLsizei imageSize, void *data);
#### 相应的还有 glCompressedTexImage2D、glCompressedTexImage3D

# 第六章 非存储着色器
## 一、OpenGL 着色语言（GLSL）
### GLSL 运行在图形硬件中
### 1、变量和数据类型
#### 整数（int、uint）、浮点数（float）、布尔值（bool）、向量类型、矩阵类型
### 2、存储限定符
#### <none> 只是普通的本地变量，外部不可见，外部不可访问
#### const 一个c编译时常量，或者说是一个对函数来说为只读的参数
#### in 一个从以前的阶段传递过来的变量
#### in centroid 一个从以前的阶段传递过来的变量，使用质心插值
#### out 传递到下一个处理阶段或者在一个函数中指定一个返回值
#### out centroid 传递到下一个处理阶段，使用质心插值
#### inout 一个读/写变量，只能用于局部函数参数
#### uniform 一个从客户端代码传递过来的变量，在顶点之间不做改变
#### 除非正在对一个多重采样缓冲区进行渲染，否则 centroid 限定符不会起任何作用。
### 3、GLSL 代码格式
    #version version_number
    in type in_variable_name;
    in type in_variable_name;
    out type out_variable_name;
    uniform type uniform_name;
    int main()
    {
        // 处理输入并进行一些图形操作
        ...
        // 输出处理过的结果到输出变量
        out_variable_name = weird_stuff_we_processed;
    }






