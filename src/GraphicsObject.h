/*
 * GraphicsObject.h
 *
 * Header file for GraphicsObject.cpp, defines class GraphicsObject.
 */
#ifndef GRAPHICS_OBJECT_H_
#define GRAPHICS_OBJECT_H_

// OpenGL, glew, and freeglut headers
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#include "util/LinkedList.h"
#include "util/mthread.h"
#include "util/Utils.h"
#include <iostream>

using namespace std;

/*
 * Represents an object that can be drawn to the screen using OpenGL.
 *
 * This class is intended to be used as a parent class; objects should not be
 * instantiated from this class directly.
 * All instantiated GraphicsObject derivatives are stored statically in this
 * class, and actions are performed on all objects through the static methods.
 */
class GraphicsObject {
public:

	/*
	 * Static initializer, initialize GraphicsObject list.
	 */
	static void init(void);

	/*
	 * Delete the GraphicsObject list.
	 */
	static void destroy(void);

	/*
	 * Call the draw() function for every object in the list.
	 */
	static void draw_all(void);

	/*
	 * Call the key_input() function for every object in the list.
	 *
	 * key - character of the pressed key
	 */
	static void key_input_all(unsigned char key, int x, int y);

	/*
	 * Call the mouse_input() function for each object in the list that bounds
	 * the coordinates of the mouse input.
	 *
	 * button - integer representing the mouse button clicked
	 * state - integer representing the state of the active button
	 * x - x-coordinate of the mouse position
	 * y - y-coordinate of the mouse position
	 */
	static void mouse_input_all(int button, int state, int x, int y);

	/*
	 * Call the resize() function for every object in the list.
	 * Uses perspective resizing.
	 *
	 * width_ratio - ratio of far plane width to depth
	 * height_ratio - ratio of far plane height to depth
	 * near - near bound of the object
	 * far - far bound of the object
	 */
	static void resize_perspective(double width_ratio, double height_ratio, int near, int far);

	/*
	 * Constructor, add the newly-created GraphicsObject to the list.
	 */
	GraphicsObject(void);

	/*
	 * Virtual destructor.
	 */
	virtual ~GraphicsObject(void);

	/*
	 * Draw object to the screen.
	 */
	virtual void draw(void);

	/*
	 * Get far bound as defined by last resize.
	 */
	virtual int get_far(void);

	/*
	 * Get height as defined by last resize.
	 */
	virtual int get_height(void);

	/*
	 * Get near bound as defined by last resize.
	 */
	virtual int get_near(void);

	/*
	 * Get width as defined by last resize.
	 */
	virtual int get_width(void);

	/*
	 * Listener for key input.
	 *
	 * key - character of the pressed key
	 */
	virtual void key_input(unsigned char key, int x, int y);

	/*
	 * Listener for mouse_input.
	 *
	 * button - integer representing the mouse button clicked
	 * state - integer representing the state of the active button
	 * x - x-coordinate of the mouse position
	 * y - y-coordinate of the mouse position
	 */
	virtual void mouse_input(int button, int state, int x, int y);

	/*
	 * Resize the object using specified dimensions.
	 * Called by each child at resize.
	 *
	 * width - width to size object
	 * height - height to size object
	 * near - near bound of the object
	 * far - far bound of the object
	 */
	virtual void resize(int width, int height, int near, int far);

	/*
	 * Resize the object using specified ratios, used for perspective projection.
	 * The ratios are a factor of the specified dimension over the far bound, so that
	 * the actual width and height at any value of z can be calculated like so:
	 *
	 *     width = width_ratio*(z_value)
	 *     height = height_ratio*(z_value)
	 *
	 *     Where (near <= z_value <= far)
	 *
	 * width_ratio - ratio of far plane width to depth
	 * height_ratio - ratio of far plane height to depth
	 * near - near bound of the object
	 * far - far bound of the object
	 */
	virtual void resize(double width_ratio, double height_ratio, int near, int far);

protected:

	/*
	 * m_update_thread - thread used for asynchronously updating object
	 * m_width - width of the object
	 * m_height - height of the object
	 * m_near - near bound of the object
	 * m_far - far bound of the object
	 */
	pthread_t m_update_thread;
	int m_width, m_height, m_near, m_far;

private:

	/*
	 * sp_list - LinkedList of instantiated GraphicsObjects
	 */
	static LinkedList<GraphicsObject> *sp_list;

};

#endif
