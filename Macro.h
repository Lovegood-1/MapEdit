/*
�궨��ͷ�ļ�
*/

#ifndef MACRO_H
#define MACRO_H


// �㡢ͨ�ð�
#include <iostream>

// һ��״̬��
 
	// ͨ�ú�
	#define NORMAL_RETURN 0
	constexpr int ERROR_POSITION = 1;
	constexpr int EMPTY_NODE_NAME = 2;
	// �ļ���
	#define FILE_NOT_FOUND 101 // �ļ�������
	#define NO_FILE_SELECTED 102 // û���ļ���ѡ�� 


	// ������
	#define ERROR_NODE_ID 0
	#define ERROR_EDGE_ID 0



// �����ڲ�������

	// ��ʼ������
	#define INIT_NODE_POS_X 0.0
	#define INIT_NODE_POS_Y 0.0
	
	// ���Ŵ�߶�
	constexpr float MAX_SCALE = 10;


// �����û����ú�

	// һ������˵��߶�
	constexpr int HIGH_MENU = 25;

	// һ������˵����
	constexpr int WIDTH_MENU = 200;

	// �Ŵ��ٶ�
	constexpr float SCALE_SPEED = 0.05;

	// �ڵ����ʾ��С
	constexpr int  NODE_RADIUS = 5;

	// ѡ��ڵ�������
	constexpr int CHOSE_POINT_RADIUS = 20;

#define USE_OPENGL

#endif // !MACRO_H
