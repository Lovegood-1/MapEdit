/*
宏定义头文件
*/

#ifndef MACRO_H
#define MACRO_H


// 零、通用包
#include <iostream>

// 一、状态宏
 
	// 通用宏
	#define NORMAL_RETURN 0
	constexpr int ERROR_POSITION = 1;
	constexpr int EMPTY_NODE_NAME = 2;
	// 文件宏
	#define FILE_NOT_FOUND 101 // 文件不存在
	#define NO_FILE_SELECTED 102 // 没有文件被选择 


	// 其他宏
	#define ERROR_NODE_ID 0
	#define ERROR_EDGE_ID 0



// 二、内部变量宏

	// 初始化设置
	#define INIT_NODE_POS_X 0.0
	#define INIT_NODE_POS_Y 0.0
	
	// 最大放大尺度
	constexpr float MAX_SCALE = 10;


// 三、用户设置宏

	// 一级横向菜单高度
	constexpr int HIGH_MENU = 25;

	// 一级纵向菜单宽度
	constexpr int WIDTH_MENU = 200;

	// 放大速度
	constexpr float SCALE_SPEED = 0.05;

	// 节点的显示大小
	constexpr int  NODE_RADIUS = 5;

	// 选择节点灵敏度
	constexpr int CHOSE_POINT_RADIUS = 20;

#define USE_OPENGL

#endif // !MACRO_H
