/*
 * GraphicsController.cpp
 *
 * Implements member functions from class GraphicsController, see
 * 'GraphicsController.h'.
 */
#include "GraphicsController.h"

/*
 * Static member declarations
 *
 * WINDOW_NAME - name of the OpenGL window
 * WINDOW_X - horizontal position of window
 * WINDOW_Y - vertical position of window
 * WINDOW_WIDTH - width of window
 * WINDOW_HEIGHT - height of window
 */
const char *GraphicsController::P_WINDOW_NAME = "Physics Engine";
const int GraphicsController::WINDOW_X = 100,
		  GraphicsController::WINDOW_Y = 100,
		  GraphicsController::WINDOW_WIDTH = 1366,
		  GraphicsController::WINDOW_HEIGHT = 768;

/*
 * Initialize the graphics functions, begin main graphics routine.
 */
void GraphicsController::init() {
	int argc;
	char *argv[0];
	glutInit(&argc, argv);

	glutInitContextVersion(3, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutCreateWindow(P_WINDOW_NAME); // Name of window
	glutDisplayFunc(draw_scene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key_input);
	glutMouseFunc(mouse_input);

	glewExperimental = GL_TRUE;
	glewInit();

	setup(); // Call setup before starting graphics routine
	run(0); // Run timer

	glutMainLoop();
}

/*
 * Destroy routine, destroys GraphicsObject.
 */
void GraphicsController::destroy() {
	GraphicsObject::destroy();
	PhyController::destroy();
	delete[] P_WINDOW_NAME;
}

/*
 * Drawing routine, calls draw_all() in GraphicsObject.
 */
void GraphicsController::draw_scene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GraphicsObject::draw_all();
	glFlush();
}

/*
 * Keyboard input processing routine, calls key_input_all() in GraphicsObject.
 * Pressing [ESC] exits the application.
 */
void GraphicsController::key_input(unsigned char key, int x, int y) {
	GraphicsObject::key_input_all(key, x, y);
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

/*
 * Mouse input processing routine, calls mouse_input_all() in GraphicsObject.
 */
void GraphicsController::mouse_input(int button, int state, int x, int y) {
	GraphicsObject::mouse_input_all(button, state, x, y);
}

/*
 * OpenGL window reshape routine, calls resize_all() in GraphicsObject.
 */
void GraphicsController::resize(int width, int height) {
	double ratio = WINDOW_WIDTH / WINDOW_HEIGHT,
		   theta = 5;
	int near = 5, far = 1000;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Set viewing box dimensions equal to window dimensions.
	gluPerspective(2*theta, ratio, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GraphicsObject::resize_perspective(ratio*tan(Utils::to_radians(theta)), tan(Utils::to_radians(theta)), near, far);
}

/*
 * Run the refresh timer, refresh at a rate of ~60 frames per second.
 *
 * value - required parameter for timer callback
 */
void GraphicsController::run(int value) {
	PhyController::update_all();
	glutPostRedisplay();
	glutTimerFunc(17, run, 0);
}

/*
 * Initialization routine, initializes GraphicsObject,
 * creates required objects, and clears the window.
 */
void GraphicsController::setup(void) {
	GraphicsObject::init();
	PhyController::init();
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
