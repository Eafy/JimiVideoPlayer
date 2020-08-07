//
//  Monitor.h
//  IOTCCamera
//
//  Created by lizhijian<lizhijian_21@163.com> on 2017/2/28.
//  Copyright © 2017年 concox. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Monitor : UIImageView

/// 显示图片
/// @param image UIImage
- (void)displayImage:(UIImage *)image;

/// 加载RGB24画面数据
/// @param rgbData rgb24数据
/// @param width 宽
/// @param height 高
- (void)displayRgb24Data:(const u_char *)rgbData videoWidth:(NSInteger)width videoHeight:(NSInteger)height;


@end
