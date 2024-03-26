# QPlayer2

Qplayer2是一款跨平台的播放器SDK,除了基础的播放器能力外，更致力于各种应用场景的对接。

### 支持的平台

 Platform | Build Status
 -------- | ------------
 Android | https://github.com/pili-engineering/QPlayer2-Android 
 IOS | https://github.com/pili-engineering/QPlayer2-IOS
 Windows | Last Version: 1.4.1
 HarmonyOS NEXT| 敬请期待
 Mac | 敬请期待 
 Linux | 敬请期待 
### qplayer2-core 功能列表

| 能力                  | 亮点                                                         | 备注                             |
| --------------------- | ------------------------------------------------------------ | -------------------------------- |
| 媒体资源组成形式      | 一个媒体资源支持多url，比如一个音频url和一个视频url组成一个媒体资源,提升拉流速度和解封装速度 |                                  |
| 播放协议及视频类型    | http/https/srt/rtmp flv/m3u8/mp4/flac/wav(PCM_S24LE)/rtsp         | 新增协议和视频类型请联系技术支持 |
| 解码                  | 软解/硬解/自动解码                                           |                                  |
| 色盲模式              | 能在业务场景中更好的服务视觉有障碍的客户                     |                                  |
| 倍速                  | 变速不变调                                                   |                                  |
| 清晰度切换            | 通用清晰度切换方案，无缝切换，即使媒体资源gop不对齐          |                                  |
| seek                  | 支持精准/关键帧 seek 两种方式                                |                                  |
| 指定起播位置          | 从指定位置开始播放                                           |                                  |
| 起播方式              | 起播播放/起播暂停 设置起播暂停时，起播后首帧渲染出来就停止画面 |                                  |
| SEI数据回调           | 所有解码方式都支持                                           |                                  |
| 纯音频播放/纯视频播放 | 播放只有单音频流或者只有单视频流的视频                       |                                  |
| APM埋点上报           | 用于整体大盘的性能监测                                       |                                  |
| 截图                  | 自动转换成jpeg格式，可以展示在UI上，也可存放到相册           |                                  |
| 静音播放              | 针对视频的静音，不影响系统声音                               |                                  |
| 音视频数据上抛              | 适用于业务层需要获取当前播放的音视频数据的场景（比如推流等）                              |                                  |
| 本地重构时间轴              | 以真是的流逝时间为准，避免某些视频时间轴错乱导致播放过程中异常                              |                                  |
| DRM  | 支持HLS 私有加密/通用加密 2种方式，支持 MP4 CENC-AES-CTR 加密，支持七牛私有 MP4 加密方式                          |                                  |




### Windows

##### 引入依赖

```groovy
1. 链接器 -> 常规 -> 附加库目录 中添加 qplayer2-core.dll 所在路径
2. 链接器 -> 输入 -> 附加依赖项 中添加 qplayer2-core.dll
3.复制对应平台的qplayer2-core 的 dll 和 manifest 到输出目录
   //复制所有 dll 文件
   copy /Y "$(ProjectDir)dependency\qplayer-core\x86_64\lib\*.dll" "$(ProjectDir)out\$(Platform)\$(Configuration)\bin\" 
   //复制 manifest 文件
   copy /Y "$(ProjectDir)dependency\qplayer-core\x86_64\lib\*.manifest" "$(ProjectDir)out\$(Platform)\$(Configuration)\bin\" 
4.下载 json 的第三方依赖，执行下面的命令
   qplayer2-dependency.bat
```



##### 鉴权

| 权限  | 说明         | 鉴权失败结果                                                 |
| ----- | ------------ | ------------------------------------------------------------ |
| Base  | 基础播放能力 | 播放器进入error状态                                          |
| SEI   | SEI数据回调  | 开启sei 回调，且视频有sei数据。能正常播放视频，SEI数据不回调，同时抛出鉴权失败错误码 |
| SRT   | srt协议视频  | 播放srt链接 播放器进入error状态                              |
| BLIND | 色盲滤镜     | 开启色盲滤镜，视频正常播放，滤镜不生效。                     |

如需使用该套sdk到其他工程中，请联系我们的技术支持开通帐号和权限。




##### API文档

请查阅document目录下的api文档

##### 接入文档

https://developer.qiniu.com/pili/12642/qplayer2-windows

##### Demo介绍

1. demo 工程内的 视频播放 是基于 qplayer2-core 来实现的

2. demo 下载：https://sdk-release.qnsdk.com/qplayer2_windows_demo_v1.4.1.zip

3. demo 需要执行 release 版本，暂不支持 debug
   

#### 技术支持与交流

产品及服务咨询：400-808-9176

问题反馈：如有问题请提交issue
