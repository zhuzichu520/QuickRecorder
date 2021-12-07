#ifndef GDIGRAB_H
#define GDIGRAB_H

#include "src/aencode.h"
#include <QString>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavdevice/avdevice.h>
#include <libavutil/opt.h>
}

class Gdigrab
{
public:
    Gdigrab(const QString &path,int x,int y,int width,int height);
    ~Gdigrab();

    /**
     * @brief open 打开
     * @return
     */
    bool open();

    /**
     * @brief read 读取
     * @return
     */
    bool read();

    /**
     * @brief setOptions
     * @param x
     * @param y
     * @param width
     * @param height
     */
    void setOptions(int x,int y,int width,int height);

    /**
     * @brief getFPS 获取帧率
     * @return
     */
    int getFPS(){
        return fps.num;
    };

    /**
     * @brief getFrame 获取图像
     * @return
     */
    AVFrame* getFrame(){
        return pFrameRGB;
    };

    /**
     * @brief stop 停止编码并关闭文件
     */
    void stop();
private:

    /**
     * @brief options 参数
     */
    AVDictionary *options;

    /**
     * @brief pFormatCtx 文件内容信息 这里指屏幕
     */
    AVFormatContext *pFormatCtx;

    /**
     * @brief pCodecCtx 解码器上下文
     */
    AVCodecContext *pCodecCtx;

    /**
     * @brief pCodec 解码器
     */
    AVCodec *pCodec;

    /**
     * @brief pFrame 解码出来的图像
     */
    AVFrame *pFrame;

    /**
     * @brief pFrameRGB 转换成RGB的图像
     */
    AVFrame *pFrameRGB;

    /**
     * @brief packet 图像解码前的包
     */
    AVPacket *packet;

    /**
     * @brief fps
     */
    AVRational fps;

    /**
     * @brief out_buffer 图像缓存区
     */
    unsigned char *out_buffer;

    /**
     * @brief pSwsContext 转换格式
     */
    struct SwsContext *pSwsContext;

    /**
     * @brief videoindex 视频流索引
     */
    int videoindex;

    /**
     * @brief E 编码器
     */
    AEncode E;
};

#endif // GDIGRAB_H
