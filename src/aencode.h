#ifndef AENCODE_H
#define AENCODE_H

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

class AEncode
{
public:
    AEncode();
    ~AEncode();

    /**
     * @brief setPath 设置文件路径
     */
    void setPath(const char *p);

    /**
     * @brief setSize 设置视频宽高
     * @param w 宽
     * @param h 高
     */
    void setSize(int w, int h);

    /**
     * @brief setFPS 设置帧率
     */
    void setFPS(int value){
        fps = value;
    };

    /**
     * @brief setPixFormat 设置输出图像的颜色空间
     * @param format
     */
    void setPixFormat(AVPixelFormat format);

    /**
     * @brief setSwsCtx 设置转换格式
     * @param src
     * @param src_w
     * @param src_h
     */
    void setSwsCtx(AVPixelFormat src, int src_w, int src_h);

    /**
     * @brief initOutFile 为输出文件初始化
     * @return
     */
    bool initOutFile();

    /**
     * @brief initVideo 初始化视频编码器
     * @return
     */
    bool initVideo();

    /**
     * @brief startEncodec 写文件头
     * @return
     */
    bool startEncodec();

    /**
     * @brief encodecOneFrame 编码一帧
     * @param frame
     * @param index
     * @return
     */
    bool encodecOneFrame(AVFrame *frame, int index);

    /**
     * @brief endEncodec 写文件尾
     * @return
     */
    bool endEncodec();

    /**
     * @brief free 销毁资源
     */
    void free();

private:
    /**
     * @brief pFormatCtx 多媒体上下文
     */
    AVFormatContext *pFormatCtx;

    /**
     * @brief pVCodecCtx 视频编码器上下文
     */
    AVCodecContext *pVCodecCtx;

    /**
     * @brief pVCodec 视频编码器
     */
    AVCodec *pVCodec;

    /**
     * @brief fmt 输出参数
     */
    AVOutputFormat *fmt;

    /**
     * @brief pVStream 视频输出流
     */
    AVStream *pVStream;

    /**
     * @brief pVFrame 视频编码帧
     */
    AVFrame *pVFrame;

    /**
     * @brief pVPacket 视频编码帧
     */
    AVPacket *pVPacket;

    /**
     * @brief VPixFormat 图像的颜色空间
     */
    AVPixelFormat vPixFormat;

    /**
     * @brief pSwsCtx 转换格式
     */
    struct SwsContext *pSwsCtx;

    /**
     * @brief out_buffer 图像缓存区
     */
    unsigned char *out_buffer;

    /**
     * @brief path 文件路径
     */
    char path[256];

    /**
     * @brief width 宽
     */
    int width;

    /**
     * @brief height 高
     */
    int height;

    /**
     * @brief fps 帧率
     */
    int fps;

    /**
     * @brief videoindex 视频流
     */
    int videoindex;
};

#endif // AENCODE_H
