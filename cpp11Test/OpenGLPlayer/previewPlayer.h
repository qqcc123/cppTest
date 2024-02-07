#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMouseEvent>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class previewPlayer :  public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	previewPlayer(QWidget* parent = nullptr);

	~previewPlayer();

    bool Show();

    bool Play();

    void Stop();

    void SetSize(int win_left, int win_top, int width, int height);

	void updateImage(char* buffer, int w, int h);

	void initializeGL() Q_DECL_OVERRIDE;

    void createFunButton();

    bool nativeEvent(const QByteArray& eventType, void* message, long* result);

    void resizeEvent(QResizeEvent* event);

signals:
    void sig_close_previewWnd();

private:
    void paintGL() Q_DECL_OVERRIDE;

private:
	QOpenGLShaderProgram *program;

    QOpenGLBuffer vbo;

    GLuint textureUniformY,textureUniformU,textureUniformV; //opengl中y、u、v分量位置

    QOpenGLTexture *textureY = nullptr,*textureU = nullptr,*textureV = nullptr;

    GLuint idY,idU,idV; //自己创建的纹理对象ID，创建错误返回0

    char* yuv_buffer_ = nullptr; // 存储YUV图像数据的缓冲区

    int yuv_buffer_size_ = 0;     // 缓冲区大小

    int image_width_ = 0;

    int image_height_ = 0;

    int m_nBorderWidth = 5;
};

