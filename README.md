# JimiVideoPlayer
[![CI Status](https://img.shields.io/travis/Eafy/JimiVideoPlayer.svg?style=flat)](https://travis-ci.org/Eafy/JimiVideoPlayer)
[![Version](https://img.shields.io/cocoapods/v/JimiVideoPlayer.svg?style=flat)](https://cocoapods.org/pods/JimiVideoPlayer)
[![License](https://img.shields.io/cocoapods/l/JimiVideoPlayer.svg?style=flat)](https://cocoapods.org/pods/JimiVideoPlayer)
[![Platform](https://img.shields.io/cocoapods/p/JimiVideoPlayer.svg?style=flat)](https://cocoapods.org/pods/JimiVideoPlayer)

Jimi RTMP Video Player SDK for iOS at CocoaPods.

<!-- TOC -->

- [全局结构体](#全局结构体)
- [全局广播/通知](#全局广播通知)
    - [登录已失效](#登录已失效)
- [本地错误码](#本地错误码)
- [App环境切换、服务器节点切换相关](#app环境切换服务器节点切换相关)
    - [App国内外环境切换](#app国内外环境切换)
    - [服务器节点查询](#服务器节点查询)
    - [服务器节点切换](#服务器节点切换)
- [国内手机登录相关](#国内手机登录相关)
    - [手机登录](#手机登录)
    - [发送手机验证码](#发送手机验证码)
    - [请求图像验证码](#请求图像验证码)
    - [第三方登录](#第三方登录)
    - [第三方绑定手机](#第三方绑定手机)
    - [退出登录](#退出登录)
- [国外邮箱登录相关](#国外邮箱登录相关)
    - [邮箱方式注册账号](#邮箱方式注册账号)
    - [邮箱登录](#邮箱登录)
    - [发送邮箱验证码](#发送邮箱验证码)
    - [发送邮箱验证码](#发送邮箱验证码-1)
    - [第三方登录(国外)](#第三方登录国外)
    - [第三方绑定邮箱](#第三方绑定邮箱)
    - [退出登录(国外)](#退出登录国外)
- [用户信息相关](#用户信息相关)
    - [获取用户信息](#获取用户信息)
    - [修改用户基础信息](#修改用户基础信息)
    - [上传/更新用户头像](#上传更新用户头像)
- [设备相关](#设备相关)
    - [绑定设备](#绑定设备)
    - [删除设备](#删除设备)
    - [获取设备列表](#获取设备列表)
    - [修改设备名称](#修改设备名称)
    - [获取分享设备的链接](#获取分享设备的链接)
    - [绑定分享链接的设备](#绑定分享链接的设备)
    - [获取设备被分享的用户列表](#获取设备被分享的用户列表)
    - [获取被分享的账户下的所有已分享的设备列表](#获取被分享的账户下的所有已分享的设备列表)
    - [获取小程序信息](#获取小程序信息)
- [消息/告警列表](#消息告警列表)
- [删除消息列表](#删除消息列表)
- [错误码查询](#错误码查询)

<!-- /TOC -->


# 全局结构体
>class JMError {  
    NSInteger errCode;  //错误码  
    NSString *errMsg;  //错误码字符串  
    NSString *errServerMsg;  //服务器返回的错误码字符串  
}

- iOS 
> /// 普通请求成功的回调  
typedef void (^JMUserSuccessHandler)(void);  

> /// 普通请求失败的回调  
/// @param JMError 请求失败返回的错误信息类  
typedef void (^JMUserFailureHandler)(JMError *error);

- Android
> public interface JMUserBaseListener {
    void onSuccessHandler();
    void onFailureHandler(JMError error);
}

# 全局广播/通知
## 登录已失效
- `一旦接收到此通知/广播，所有接口均会出现失效的现象，需要重新调用登录接口`
- `此广播/通知意在可全局监听内部Token失效问题，可方便上层统一进行相应的处理`
- iOS  
  Name: `kJMUserLoginInvalidNotification`  
  Value: `JMUserLoginInvalidNotification`
- Android  
  Name: `kJMUserLoginInvalidBroadcast`  
  Value: `com.jimi.JMUserLoginInvalidBroadcast`
- 通知内容：
  `invalidType`: 0:长期未登陆失效，1:账号在其他地方登陆

# 本地错误码
- -1	没有网络  
- -2	请求超时
- -3	解析数据失败
- -4	获取不到code
- -5	访问异常，http404等错误码
- -6	获取/生成图形验证码失败
- -7	七牛云上传图片失败
- -8	参数错误
	
- -100	登录已失效
- -101	手机号码输入错误
- -102	邮箱格式错误
- -103	第三方登录方式类型错误
- -104	用户修改类型错误（参数错误）
- -105	设备编码类型错误（不是MAC/IMEI/SN）
- -106	当前接口仅国外版可用
- -107	当前接口仅国内版可用
- -108	用户信息保存失败
- -109	删除用户信息失败

# App环境切换、服务器节点切换相关
## App国内外环境切换
- 功能  
切换App是国内版还是国外版(默认国内版)

- iOS  
`- (void)switchForeignAPI:(BOOL)isForeign;`

- Android  
`public void switchForeignAPI(boolean bForeign);`
## 服务器节点查询
- 功能  
查询服务器节点列表，成功则返回服务器节点字符串数组

- iOS  
`- (void)requestAreaServerList:(void (^ __nullable)(NSArray<NSString *> * _Nullable list))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserAreaServerListListener {  
        void onSuccessHandler(List<String> list);  
        void onFailureHandler(JMError jmError);  
}  
public void requestAreaServerList(JMUserAreaServerListListener listener);

## 服务器节点切换
- 功能  
切换App访问服务器的当前节点
/// @param server 服务器节点名称 

- iOS  
`- (void)switchAreaServer:(NSString *)server success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void switchAreaServer(String server, JMUserBaseListener listener);`

# 国内手机登录相关
## 手机登录
- 功能  
使用手机验证码登录
/// @param phone 手机号码 
/// @param code 手机验证码

- iOS  
`- (void)loginByPhone:(NSString *)phone code:(NSString *)code success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`void loginByPhone(String phone, String code, JMUserBaseListener listener);`

## 发送手机验证码
- 功能  
发送手机验证码
/// @param phone 手机号码 
/// @param captchaCode 图形验证码(非必须，当天超过10次以上才需要)

- iOS  
`- (void)sendCodeByPhone:(NSString *)phone captchaCode:(NSString *)captchaCode success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void sendCodeByPhone(String phone, String captchaCode, JMUserBaseListener listener);`

## 请求图像验证码
- 功能  
请求图像验证码，当发送手机验证码过多时，需要进行图像码验证
- iOS  
`- (void)requestCaptcha:(void (^ __nullable)(UIImage _Nullable *img))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserBitmapListener {  
    void onSuccessHandler(Bitmap bitmap);  
    void onFailureHandler(JMError jmError);  
}  
public void requestCaptcha(JMUserBitmapListener listener);

## 第三方登录
- 功能  
国内环境使用第三方登录
/// @param type 使用哪种第三方登录方式
/// @param openId 第三方登录的OpenID/Key/Token 

> typedef enum : NSUInteger {  
    JM_LOGIN_THIRD_WEXIN = 1,   //微信登录  
    JM_LOGIN_THIRD_QQ,          //QQ登录  
    JM_LOGIN_THIRD_FACEBOOK,    //Facebook登录  
} JM_LOGIN_THIRD_TYPE;

- iOS  
`- (void)loginByThird:(JM_LOGIN_THIRD_TYPE)type openId:(NSString *)openId success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void loginByThird(int type, String openId, JMUserBaseListener listener);`

## 第三方绑定手机
- 功能  
国内第三方登录之后，绑定手机号  
/// @param openId 第三方登录的OpenID/Key/Token  
/// @param phone 手机号  
/// @param code 手机验证码 
- iOS  
`- (void)bindPhoneByThird:(NSString *)openId phone:(NSString *)phone code:(NSString *)code success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void bindPhoneByThird(String openId, String phone, String code, JMUserBaseListener listener);`

## 退出登录
- 功能  
退出国内登录，并清除内部用户数据  

- iOS  
`- (void)signOut:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void signOut(JMUserBaseListener listener);`

# 国外邮箱登录相关
## 邮箱方式注册账号
- 功能  
通过邮箱注册账号  
/// @param email 有效的邮箱地址  
/// @param password 账号密码  
/// @param code 邮箱验证码 
- iOS  
`- (void)registerByEmail:(NSString *)email password:(NSString *)password code:(NSString *)code success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void registerByEmail(String email, String password, String code, JMUserBaseListener listener);`

## 邮箱登录
- 功能  
使用已注册的邮箱登录  
/// @param email 有效的邮箱地址  
/// @param password 账号密码  
- iOS  
`- (void)loginByEmail:(NSString *)email password:(NSString *)password success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void loginByEmail(String email, String password, JMUserBaseListener listener);`

## 发送邮箱验证码
- 功能  
请求发送邮箱验证码  
/// @param email 有效的邮箱地址  
/// @param type 1:注册方式；2:找回密码  
- iOS  
`- (void)sendCodeByEmail:(NSString *)email type:(NSString *)type success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void sendCodeByEmail(String email, int type, JMUserBaseListener listener);`

## 发送邮箱验证码
- 功能  
请求发送邮箱验证码  
/// @param email 有效的邮箱地址  
/// @param password 新密码  
/// @param code 邮箱验证码 
- iOS  
`- (void)resetPasswordByEmail:(NSString *)email password:(NSString *)password code:(NSString *)code success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void resetPasswordByEmail(String email, String password, String code, JMUserBaseListener listener);`

## 第三方登录(国外)
- 功能  
国外环境使用第三方登录

见[第三方登录](#第三方登录)

## 第三方绑定邮箱
- 功能  
国外第三方登录之后，绑定邮箱地址  
/// @param email 邮箱地址  
/// @param email 邮箱密码  
/// @param code 邮箱验证码 
- iOS  
`- (void)bingEmailByThird:(NSString *)email password:(NSString *)password code:(NSString *)code success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void bingEmailByThird(String email, String password, String code, JMUserBaseListener listener);`

## 退出登录(国外)
- 功能  
退出国外登录，并清除内部用户数据  

见[退出登录](#退出登录)

# 用户信息相关
## 获取用户信息
- 功能  
获取用户昵称、头像等相关信息  
/// @param success 返回用户相关信息Model<JMUserInfoModel>  
/// @param failure 请求失败  

>class JMUserInfoModel {  
    String phone;  
    String email;  
    String nickName;  
    String avaterUrl;  
    int sex;  
    double weight;  
    double height;  
    String birthday;  
}

- iOS  
`- (void)requestUserInfo:(void (^ __nullable)(JMUserInfoModel * _Nonnull userInfo))success failure:(JMUserFailureHandler)failure;`
- Android  
> public interface JMUserUserInfoListener {  
    void onSuccessHandler(JMUserInfoModel userinfo);  
    void onFailureHandler(JMError jmError);  
}  
public void requestUserInfo(JMUserUserInfoListener listener);

## 修改用户基础信息
- 功能  
修改用户昵称、年龄等相关信息  
/// @param type 需要修改的类型(可组合修改多个)  
/// @param userInfo 代修改的用户信息JMUserInfoModel  
/// @param success 修改成功  
/// @param failure 请求失败  

>typedef enum : NSUInteger {  
    JM_USER_INFO_NICKNAME = 1 << 0,  
    JM_USER_INFO_AVATAR = 1 << 1,       //无效，上传头像使用modifyUserAvater接口    
    JM_USER_INFO_SEX = 1 << 2,  
    JM_USER_INFO_WEIGHT = 1 << 3,  
    JM_USER_INFO_HEIGHT = 1 << 4,  
    JM_USER_INFO_BIRTHDAY = 1 << 5,  
} JM_USER_INFO_TYPE;

- iOS  
`- (void)modifyUserInfo:(JM_USER_INFO_TYPE)type userInfo:(JMUserInfoModel *)userInfo success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void modifyUserInfo(int type, JMUserInfoModel userInfo, JMUserBaseListener listener);`

## 上传/更新用户头像
- 功能  
更新服务器头像文件
/// @param avaterImg 需要修改的头像Image 
/// @param success 修改成功  
/// @param failure 请求失败  

- iOS  
`- (void)modifyUserAvater:(UIImage *)avaterImg success:(void (^ __nullable)(NSString * __nullable url))success failure:(JMUserFailureHandler)failure;`
>public interface JMUserModifyAvaterListener {  
    void onSuccessHandler(String url);  
    void onFailureHandler(JMError jmError);  
}  
- Android  
`public void modifyUserAvater(Bitmap avaterImg, JMUserModifyAvaterListener listener);`
 
# 设备相关
## 绑定设备
- 功能  
通过IMEI、MAC、SN绑定设备  
/// @param uuid 设备IMEI/MAC/SN 
/// @param type 设备号类型  

>>typedef enum : NSUInteger {  
    JM_DEVICE_UUID_IMEI,
    JM_DEVICE_UUID_SN,
    JM_DEVICE_UUID_MAC,,  
} JM_DEVICE_UUID_TYPE;

- iOS  
`- (void)bingDevice:(NSString *)uuid type:(JM_DEVICE_UUID_TYPE)type success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void bingDevice(String uuid, int type, JMUserBaseListener listener);`

## 删除设备
- 功能  
删除设备  
/// @param device 需删除的JMDeviceModel模型

- iOS  
`- (void)deleteDevice:(JMDeviceModel *)device success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void deleteDevice(JMDeviceModel device, JMUserBaseListener listener);`

## 获取设备列表
- 功能  
获取设备列表 

>class JMDeviceModel {  
    String deviceId;    //设备ID  
    String deviceName;  //设备名称  
    String productId;   //产品ID  
    String deviceUUID;  //设备IMEI/MAC/SN  
    JMDevicesUuidType uuidType; //设备UUID所属类型  
    String iconUrl;     //设备图标  
    int appId;          //对应小程序AppID  
    String bingUser;    //绑定用户  
    boolean shareFlag;  //是否可分享  
    int appType;        //小程序类型，1：自定义小程序；2：模板小程序
    String deviceType;      //设备机型号  
    int status;         //设备状态，0：离线，1：静止，2：在线运动  
    String statusName   //设备在线状态名称，可能为空  
}

- iOS  
`- (void)requestDevicesList:(void (^ __nullable)(NSArray<JMDeviceModel *> * _Nonnull deviceList))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserDeviceListListener {  
    void onSuccessHandler(List<JMDeviceModel> list);  
    void onFailureHandler(JMError jmError);  
}  
public void requestDevicesList(JMUserDeviceListListener listener);

## 修改设备名称
- 功能  
修改已绑定的设备名称
/// @param device 设备JMDeviceModel，deviceName需要是已修改的设备名称

- iOS  
`- (void)modifyDeviceName:(JMDeviceModel *)devicesuccess:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void modifyDeviceName(JMDeviceModel device, JMUserBaseListener listener);`;

## 获取分享设备的链接
- 功能  
获取相应设备的分享链接,支持多个设备同时分享  
/// @param device 设备JMDeviceModel  

- iOS  
`- (void)shareDeviceUrl:(NSArray<JMDeviceModel *> *)deviceArray success:(void (^ __nullable)(NSString * __nullable url))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserBaseStringListener {  
    void onSuccessHandler(String str);  
    void onFailureHandler(JMError jmError);  
}  
`public void shareDeviceUrl(List<JMDeviceModel> device, JMUserBaseStringListener listener);`;

## 绑定分享链接的设备
- 功能  
通过分享的URL链接，绑定相应的设备  
/// @param url 设备分享的URL链接 

- iOS  
`- (void)bindShareDevice:(NSString *)url success(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`  
- Android  
`public void bindShareDevice(String url, JMUserBaseListener listener);`

## 获取设备被分享的用户列表
- 功能  
获取当前所有设备被分享给了哪些用户 

- iOS  
`- (void)shareUserList:(void (^ __nullable)(NSArray<NSString *> * __nullable list))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserBaseStrListListener {  
    void onSuccessHandler(List<String> list);  
    void onFailureHandler(JMError jmError);  
} 
`public void shareUserList(JMUserBaseStrListListener listener);`

## 获取被分享的账户下的所有已分享的设备列表 
- 功能  
获取被分享的账户下的所有已分享的设备列表 

- iOS  
`- (void)shareDevicesList:(NSString *)shareUserID success:(void (^ __nullable)(NSArray<JMDeviceModel *> * __nullable list))success failure:(JMUserFailureHandler)failure;`
- Android  
`public void shareDevicesList(String shareUserID, JMUserDeviceListListener listener);`

## 获取小程序信息
- 功能  
获取小程序相关信息
/// @param device 设备JMDeviceModel

>class JMSmartAppModel {  
    String version;     //小程序版本号，不再区分release还是build，谁有给谁  
    String url;     //小程序下载链接  
    String name;    //小程序名称  
    String aesKey;  //压缩包AES解密密钥  
    String deviceUUID;  //设备IMEI/MAC/SN标识  
    int uuidType;  //设备标识类型  
    int appId;      //小程序AppID  
    String productId;   //小程序产品ID
    int appType;        //小程序类型，1：自定义小程序；2：模板小程序
    string deviceType;      //设备机型号
}

- iOS  
`- (NSString *)requestSmartAppInfo:(JMDeviceModel *)device success:(void (^ __nullable)(JMSmartAppModel * _Nonnull smartAppModel))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserSmartAppInfoListener {  
    void onSuccessHandler(JMSmartAppModel smartAppInfo);  
    void onFailureHandler(JMError jmError);  
}  
public void requestSmartAppInfo(JMDeviceModel device, JMUserSmartAppInfoListener listener);

# 消息/告警列表
- 功能  
获取消息/告警列表  
/// @param pageNum 第几页  
/// @param pageSize 每页的条数  

>class JMMessagesListModel {  
    int pageNum;        //当前页  
    int pageSize;       //当前页数目  
    int totalSize;      //总数目  
    int totalPage;      //总页数  
    List<JMMessageModel *> messagesList;  
}

>class JMMessageModel {  
    String messageId;     //消息ID  
    int messageType;     //消息类型，1:,   
    long timestamp;    // 时间戳，0时区  
    String content;  //消息内容   
    String deviceUUID;  //设备IMEI/MAC/SN标识  
    int uuidType;  //设备标识类型  
}

- iOS  
`- (void)requestMessagesList:(int)pageNum pageSize:(int)pageSize success:(void (^ __nullable)(JMMessagesListModel * _Nonnull msgList))success failure:(JMUserFailureHandler)failure;`
- Android  
>public interface JMUserMessageListListener {  
    void onSuccessHandler(JMMessagesListModel msgList);  
    void onFailureHandler(JMError jmError);  
}  
public void requestMessagesList(int pageNum, int pageSize, JMUserMessageListListener listener);

# 删除消息列表
- 功能  
删除单个或多个消息  
/// @param msgList 需要删除的JMMessageModel列表  

- iOS  
`- (void)deleteMessages:(NSArray<JMMessageModel *> * _Nonnull)msgList success:(JMUserSuccessHandler)success failure:(JMUserFailureHandler)failure;`
- Android  
`public void deleteMessages(List<JMMessageModel> msgList, JMUserBaseListener listener);`

# 错误码查询
- 功能  
查询其他接口对应返回的JMError中errCode相应的错误字符串

- iOS  
`- (NSString *)queryErrorMsgWithCode:(JMError *)error;`
- Android  
`public String queryErrorMsgWithCode(JMError error);`
