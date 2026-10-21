#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
public:
	CInput();
	//bool Key(文字)
	//戻り値
	//true：文字のキーが押されている
	//false:文字のキーが押されていない
	bool Key(char key);
	//マウスの位置を取得する
	void MouseGetPosition(double* x, double* y);
	//マウスカーソルの表示 /非表示
	void MouseShowCursor(bool isShow);
	//ウィンドウのポインタを設定する
	static void Window(GLFWwindow* pwindow);

private:
	// ウィンドウのポインタ
	static GLFWwindow* spWindow;
};