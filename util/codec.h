#ifndef CODEC_H
#define CODEC_H
 
#include <QObject>
#include <QString>


//ffmpeg_concat_mp4_to_mp4 / ffmpeg_concat_flv_to_mp4 /  ffmpeg_concat_mp4_to_mp4
//    北上广依然相信爱情第8集.mp4.txt==>>
//        file '.\北上广依然相信爱情第8集[00].mp4'
//        file '.\北上广依然相信爱情第8集[01].mp4'
//        file '.\北上广依然相信爱情第8集[02].mp4'
//        file '.\北上广依然相信爱情第8集[03].mp4'
//        file '.\北上广依然相信爱情第8集[04].mp4'
//        file '.\北上广依然相信爱情第8集[05].mp4'
//        file '.\北上广依然相信爱情第8集[06].mp4'
//        file '.\北上广依然相信爱情第8集[07].mp4'

//    ffmpeg -loglevel quiet -f concat -safe -1 -y -i ".\\北上广依然相信爱情第8集.mp4.txt" -c copy -bsf:a aac_adtstoasc ".\\北上广依然相信爱情第8集.mp4"

//ffmpeg_convert_ts_to_mkv:
//    ffmpeg  -loglevel quiet -y -i file  output

//ffmpeg_concat_av:
//    ffmpeg -loglevel quiet -i file1 -i file2 -c:v copy   [-c:a  'aac'（mp4）/'-c:a', 'vorbis'（webm）]  -strict experimental   output
//ffmpeg_concat_mp4_to_mpg:
//    ffmpeg -loglevel quiet -f concat -safe -1 -y -i ".\\北上广依然相信爱情第8集.mp4.txt" -c copy  output
//ffmpeg_concat_ts_to_mkv:
//    ffmpeg -loglevel quiet -isync -y -i concat: file1|file2|file3|   -f matroska -c copy  output

//ffmpeg_download_stream    (出错，不同步)
//      ffmpeg -y -re        -i "http://localhost/test/Yunflv/url.php?ctype=phone&url=http://v.youku.com/v_show/id_XMTcxNDQ2MzkyNA==.html" -c copy -bsf:a aac_adtstoasc         a.mp4
//      ffmpeg -y -threads 1 -i "http://localhost/test/Yunflv/url.php?ctype=phone&url=http://v.youku.com/v_show/id_XMTcxNDQ2MzkyNA==.html" -c copy -bsf:a aac_adtstoasc -f f4v  "C:\Users\Administrator\Desktop\Video.flv"




class Codec: public QObject
{
    Q_OBJECT

public:
    Codec();
    ~Codec();

    void setFileInfo(QString srcpath, QString filename);
    QString concat(); //to mp4
    QString getLastErr();

    bool removeTmp();


private slots:
    void on_read();
    void  onFinished(int v);

private:
    QString mDestPath;
    QString mSrcPath;
    QString mFileName;
    QString mLastErr;

    QStringList mSegList;   //分段视频的文件列表
    QString mIdxFilePath; //索引文件(.txt)路径

};

#endif // CODEC_H
