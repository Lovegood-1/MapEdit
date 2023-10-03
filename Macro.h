/*
宏定义头文件
*/

#ifndef MACRO_H
#define MACRO_H

// 一、状态宏
 
	// 通用宏
	#define NORMAL_RETURN 0

	// 文件宏
	#define FILE_NOT_FOUND 101

	// 其他宏
	#define ERROR_NODE_ID 0
	#define ERROR_EDGE_ID 0

// 二、内部变量宏

	// 初始化设置
	#define INIT_NODE_POS_X 0.0
	#define INIT_NODE_POS_Y 0.0


// 三、用户设置宏

	// 一级横向菜单高度
	constexpr int HIGH_MENU = 25;

#define USE_OPENGL

#endif // !MACRO_H
