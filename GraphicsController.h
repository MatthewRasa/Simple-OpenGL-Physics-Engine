/*
 * GraphicsController.h
 *
 * Header file for GraphicsController.cpp, defines class GraphicsController.
 */
#ifndef GRAPHICS_CONTROLLER_H_
#define GRAPHICS_CONTROLLER_H_

#include "GraphicsObject.h"

/*
 * Main controller class for handling graphical operations.
 *
 * OpenGL requisites are set up here, and the static GraphicsObject methods are
 * called (draw_all, key_input_all, resize_all).
 */
class GraphicsController {
public:

	/*
	 * P_WINDOW_NAME - name of the OpenGL window
	 * WINDOW_X - horizontal position of window
	 * WINDOW_Y - vertical position of window
	 * WINDOW_WIDTH - width of window
	 * WINDOW_HEIGHT - height of window
	 */
	static const char *P_WINDOW_NAME;
	static const int WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT;

	/*
	 * Initialize the graphics functions, begin main graphics routine.
	 */
	static void init();

	/*
	 * Destroy routine, destroys GraphicsObject.
	 */
	static void destroy();

private:

	/*
	 * Drawing routine, calls draw_all() in GraphicsObject.
	 */
	static void draw_scene();

	/*
	 * Keyboard input processing routine, calls key_input_all() in GraphicsObject.
	 * Pressing [ESC] exits the application.
	 */
	static void key_input(unsigned char key, int x, int y);

	/*
	 * Mouse input processing routine, calls mouse_input_all() in GraphicsObject.
	 */
	static void mouse_input(int button, int state, int x, int y);

	/*
	 * OpenGL window reshape routine, calls resize_all() in GraphicsObject.
	 */
	static void resize(int width, int height);

	/*
	 * Run the refresh timer, refresh at a rate of ~60 frames per second.
	 *
	 * value - required parameter for timer callback
	 */
	static void run(int value);

	/*
	 * Initialization routine, initializes GraphicsObject and clears the window.
	 */
	static void setup(void);

};

#endif
