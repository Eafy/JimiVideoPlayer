//
//  JMVideoStreamPlayer+Ext.h
//  JimiVideoPlayer
//
//  Created by lzj<lizhijian_21@163.com> on 2019/11/5.
//  Copyright © 2019 lzj<lizhijian_21@163.com>. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "JMVideoStreamPlayer.h"

NS_ASSUME_NONNULL_BEGIN

@interface JMVideoStreamPlayer (Ext)

/// TrackSolid平台登录
/// @param account TrackSolid账号
/// @param pwd 密码
/// @param handler 登录回调
- (void)login:(NSString *)account pwd:(NSString *)pwd handler:(void (^ __nullable)(BOOL success, NSDictionary *revDic))handler;

/// TrackSolid发送DVR-ON指令
/// @param imei 设备IMEI
/// @param handler 命令结果回调
- (void)sendDvrOnToDevice:(NSString *)imei handler:(void (^ __nullable)(BOOL success, NSDictionary *revDic))handler;

@end

NS_ASSUME_NONNULL_END
