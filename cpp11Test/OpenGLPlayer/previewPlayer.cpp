#include "previewPlayer.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QPushButton>
#include <windowsx.h>
#include "../ui/QCommonBase.h"
#include "iostream"

#define VERTEXIN 0
#define TEXTUREIN 1

#define    SCREEN_WIDTH  GetSystemMetrics(SM_CXSCREEN)

previewPlayer::previewPlayer(QWidget* parent) 
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

previewPlayer::~previewPlayer() 
{
    Stop();
	makeCurrent();
    vbo.destroy();
    if (textureY)
    {
        textureY->destroy();
    }
    
    if (textureU)
    {
        textureU->destroy();
    }

    if (textureV)
    {
        textureV->destroy();
    }
    doneCurrent();
}

void previewPlayer::createFunButton()
{
    QReleaseButton* btnClose = new QReleaseButton(this);
    QKW_SET_FIXED_SIZE(btnClose, 32, 32);
    btnClose->move(8, 8);
    btnClose->onSetPixmap(":/AIRecord/image/preview_close.png");
    connect(btnClose, &QReleaseButton::release, [=]() {
        emit sig_close_previewWnd();
    });

    //QReleaseButton* btnMax = new QReleaseButton(this);
    //QKW_SET_FIXED_SIZE(btnMax, 32, 32);
    //btnMax->move(width() - 32 - 8, 8);
    //btnMax->onSetPixmap(":/AIRecord/image/preview_max.png");
    //connect(btnMax, &QReleaseButton::release, [=]() {
    //    if (isMaximized())
    //    {
    //        showNormal();
    //    }
    //    else
    //    {
    //        showMaximized();
    //    }
    //});
}

void previewPlayer::SetSize(int win_left, int win_top, int width, int height) 
{
    setGeometry({win_left, win_top, width, height });
}

bool previewPlayer::Show() 
{
    show();
    return true;
}

void previewPlayer::updateImage(char* buffer, int w, int h)
{
	// 检查传入的YUV图像数据是否有效
	if (buffer == nullptr || w <= 0 || h <= 0) {
		return;
	}

    image_width_ = w;
    image_height_ = h;
    // 创建用于存储YUV图像数据的缓冲区
    int frameSize = image_width_ * image_height_ * 3 / 2;
    if (!yuv_buffer_ || yuv_buffer_size_ != frameSize) {
        if (yuv_buffer_) {
            delete[] yuv_buffer_;
        }
        yuv_buffer_ = new char[frameSize];
        yuv_buffer_size_ = frameSize;
    }

    // 复制YUV图像数据到缓冲区
    memcpy(yuv_buffer_, buffer, frameSize);

	update();
}

bool previewPlayer::Play() {
    return true;
}

void previewPlayer::Stop() {
    
}

void previewPlayer::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
 
    static const GLfloat vertices[]{
        //顶点坐标
        -1.0f,-1.0f,
        -1.0f,+1.0f,
        +1.0f,+1.0f,
        +1.0f,-1.0f,
        //纹理坐标
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
    };
 
 
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,sizeof(vertices));
 
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex,this);
    const char *vsrc =
   "attribute vec4 vertexIn; \
    attribute vec2 textureIn; \
    varying vec2 textureOut;  \
    void main(void)           \
    {                         \
        gl_Position = vertexIn; \
        textureOut = textureIn; \
    }";
    vshader->compileSourceCode(vsrc);
 
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment,this);
    const char *fsrc = "varying vec2 textureOut; \
    uniform sampler2D tex_y; \
    uniform sampler2D tex_u; \
    uniform sampler2D tex_v; \
    void main(void) \
    { \
        vec3 yuv; \
        vec3 rgb; \
        yuv.x = texture2D(tex_y, textureOut).r; \
        yuv.y = texture2D(tex_u, textureOut).r - 0.5; \
        yuv.z = texture2D(tex_v, textureOut).r - 0.5; \
        rgb = mat3( 1,       1,         1, \
                    0,       -0.39465,  2.03211, \
                    1.13983, -0.58060,  0) * yuv; \
        gl_FragColor = vec4(rgb, 1); \
    }";
    fshader->compileSourceCode(fsrc);
 
    program = new QOpenGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertexIn",VERTEXIN);
    program->bindAttributeLocation("textureIn",TEXTUREIN);
    program->link();
    program->bind();
    program->enableAttributeArray(VERTEXIN);
    program->enableAttributeArray(TEXTUREIN);
    program->setAttributeBuffer(VERTEXIN,GL_FLOAT,0,2,2*sizeof(GLfloat));
    program->setAttributeBuffer(TEXTUREIN,GL_FLOAT,8*sizeof(GLfloat),2,2*sizeof(GLfloat));
 
    textureUniformY = program->uniformLocation("tex_y");
    textureUniformU = program->uniformLocation("tex_u");
    textureUniformV = program->uniformLocation("tex_v");
    textureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureU = new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureV = new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureY->create();
    textureU->create();
    textureV->create();
    idY = textureY->textureId();
    idU = textureU->textureId();
    idV = textureV->textureId();
    glClearColor(0.0,0.0,0.0,0.0);
}
 
void previewPlayer::paintGL()
{
    //QMatrix4x4 m;
    //m.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f );//透视矩阵随距离的变化，图形跟着变化。屏幕平面中心就是视点（摄像头）,需要将图形移向屏幕里面一定距离。
    //m.ortho(-2,+2,-2,+2,-10,10);//近裁剪平面是一个矩形,矩形左下角点三维空间坐标是（left,bottom,-near）,右上角点是（right,top,-near）所以此处为负，表示z轴最大为10；
    //远裁剪平面也是一个矩形,左下角点空间坐标是（left,bottom,-far）,右上角点是（right,top,-far）所以此处为正，表示z轴最小为-10；
    //此时坐标中心还是在屏幕水平面中间，只是前后左右的距离已限制。
    glActiveTexture(GL_TEXTURE0);  //激活纹理单元GL_TEXTURE0,系统里面的
    glBindTexture(GL_TEXTURE_2D,idY); //绑定y分量纹理对象id到激活的纹理单元
    //使用内存中的数据创建真正的y分量纹理数据
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED, image_width_, image_height_,0,GL_RED,GL_UNSIGNED_BYTE, yuv_buffer_);
    //https://blog.csdn.net/xipiaoyouzi/article/details/53584798 纹理参数解析
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
    glActiveTexture(GL_TEXTURE1); //激活纹理单元GL_TEXTURE1
    glBindTexture(GL_TEXTURE_2D,idU);
    //使用内存中的数据创建真正的u分量纹理数据
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,image_width_ >> 1, image_height_ >> 1,0,GL_RED,GL_UNSIGNED_BYTE,yuv_buffer_ + image_width_ * image_height_);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
    glActiveTexture(GL_TEXTURE2); //激活纹理单元GL_TEXTURE2
    glBindTexture(GL_TEXTURE_2D,idV);
    //使用内存中的数据创建真正的v分量纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image_width_ >> 1, image_height_ >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, yuv_buffer_+image_width_*image_height_*5/4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //指定y纹理要使用新值
    glUniform1i(textureUniformY, 0);
    //指定u纹理要使用新值
    glUniform1i(textureUniformU, 1);
    //指定v纹理要使用新值
    glUniform1i(textureUniformV, 2);
    //使用顶点数组方式绘制图形
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

bool previewPlayer::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    Q_UNUSED(eventType)

    MSG* param = static_cast<MSG*>(message);

    switch (param->message)
    {
        case WM_NCHITTEST:
        {
            int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
            int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

            // 如果鼠标位于子控件上，则不进行处理
            if (childAt(nX, nY) != nullptr)
                return QWidget::nativeEvent(eventType, message, result);

            *result = HTCAPTION;
            return true;

            // 鼠标区域位于窗体边框，进行缩放
            if ((nX > 0) && (nX < m_nBorderWidth))
                *result = HTLEFT;

            if ((nX > this->width() - m_nBorderWidth) && (nX < this->width()))
                *result = HTRIGHT;

            if ((nY > 0) && (nY < m_nBorderWidth))
                *result = HTTOP;

            if ((nY > this->height() - m_nBorderWidth) && (nY < this->height()))
                *result = HTBOTTOM;

            if ((nX > 0) && (nX < m_nBorderWidth) && (nY > 0)
                && (nY < m_nBorderWidth))
                *result = HTTOPLEFT;

            if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > 0) && (nY < m_nBorderWidth))
                *result = HTTOPRIGHT;

            if ((nX > 0) && (nX < m_nBorderWidth)
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
                *result = HTBOTTOMLEFT;

            if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
                *result = HTBOTTOMRIGHT;

            return true;
        }
    }

    return QWidget::nativeEvent(eventType, message, result);
}

void previewPlayer::resizeEvent(QResizeEvent* event)
{
    
}