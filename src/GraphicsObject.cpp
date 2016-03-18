/*
 * GraphicsObject.cpp
 *
 * Implements member functions from class GraphicsObject, see file
 * 'GraphicsObject.h'.
 */

#include "GraphicsObject.h"

/*
 * Static member declarations
 *
 * sp_list - LinkedList of instantiated GraphicsObjects
 */
LinkedList<GraphicsObject> *GraphicsObject::sp_list;

/*
 * Static initializer, initialize GraphicsObject list.
 */
void GraphicsObject::init(void) {
	sp_list = new LinkedList<GraphicsObject>();
}

/*
 * Delete the GraphicsObject list.
 */
void GraphicsObject::destroy(void) {
	delete sp_list;
}

/*
 * Call the draw() function for every object in the list.
 */
void GraphicsObject::draw_all(void) {
	foreach (GraphicsObject *obj, sp_list) {
		glPushMatrix();
		mthread_create(&obj->m_update_thread, NULL, obj, &GraphicsObject::draw);
		glPopMatrix();
	}
	foreach (GraphicsObject *obj, sp_list)
		pthread_join(obj->m_update_thread, NULL);
}

/*
 * Call the key_input() function for every object in the list.
 *
 * key - character of the pressed key
 */
void GraphicsObject::key_input_all(unsigned char key, int x, int y) {
	foreach (GraphicsObject *obj, sp_list)
		obj->key_input(key, x, y);
}

/*
 * Call the mouse_input() function for each object in the list that bounds
 * the coordinates of the mouse input.
 *
 * button - integer representing the mouse button clicked
 * state - integer representing the state of the active button
 * x - x-coordinate of the mouse position
 * y - y-coordinate of the mouse position
 */
void GraphicsObject::mouse_input_all(int button, int state, int x, int y) {
	foreach (GraphicsObject *obj, sp_list)
		obj->mouse_input(button, state, x, y);
}

/*
 * Call the resize() function for every object in the list.
 * Uses perspective resizing.
 *
 * width_ratio - ratio of far plane width to depth
 * height_ratio - ratio of far plane height to depth
 * near - near bound of the object
 * far - far bound of the object
 */
void GraphicsObject::resize_perspective(double width_ratio, double height_ratio,
		int near, int far) {
	foreach (GraphicsObject *obj, sp_list)
		obj->resize(width_ratio, height_ratio, near, far);
}

/*
 * Constructor, add the newly-created GraphicsObject to the list.
 */
GraphicsObject::GraphicsObject(void) {
	sp_list->add(this);
	m_width = m_height = m_near = m_far = 0;
	m_update_thread = 0;
}

/*
 * Virtual destructor.
 */
GraphicsObject::~GraphicsObject(void) {

}

/*
 * Draw the object to the screen.
 */
void GraphicsObject::draw(void) {

}

/*
 * Get far bound as defined by last resize.
 */
int GraphicsObject::get_far(void) {
	return m_far;
}

/*
 * Get height as defined by last resize.
 */
int GraphicsObject::get_height(void) {
	return m_height;
}

/*
 * Get near bound as defined by last resize.
 */
int GraphicsObject::get_near(void) {
	return m_near;
}

/*
 * Get width as defined by last resize.
 */
int GraphicsObject::get_width(void) {
	return m_width;
}

/*
 * Listener for key input.
 *
 * key - character of the pressed key
 */
void GraphicsObject::key_input(unsigned char key, int x, int y) {

}

/*
 * Listener for mouse_input.
 *
 * button - integer representing the mouse button clicked
 * state - integer representing the state of the active button
 * x - x-coordinate of the mouse position
 * y - y-coordinate of the mouse position
 */
void GraphicsObject::mouse_input(int button, int state, int x, int y) {

}

/*
 * Resize the object using specified dimensions.
 * Called by each child at resize.
 *
 * width - width to size object
 * height - height to size object
 * near - near bound of the object
 * far - far bound of the object
 */
void GraphicsObject::resize(int width, int height, int near, int far) {
	m_width = width;
	m_height = height;
	m_near = near;
	m_far = far;
}
