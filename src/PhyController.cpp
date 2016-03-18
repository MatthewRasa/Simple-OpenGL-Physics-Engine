/*
 * PhyController.cpp
 */
#include "PhyController.h"

/*
 * Initialize PhyObject and the menu.
 */
void PhyController::init() {
	PhyObject::init();
	menu_init();
}

/*
 * Deallocate resources, destroy PhyObject.
 */
void PhyController::destroy() {
	PhyObject::destroy();
}

/*
 * Pass the update_all call to PhyObject, used for abstracting PhyObject's
 * from the rest of the application.
 */
void PhyController::update_all() {
	PhyObject::update_all();
}

/*
 * Callback function for the menu.
 *
 * Params:
 *     opt - id for the selected option
 */
void PhyController::menu(int opt) {

}

/*
 * Initialize the menu.
 */
void PhyController::menu_init() {
	glutCreateMenu(&menu);
	glutAddMenuEntry("Option 1", 1);
	glutAddMenuEntry("Option 2", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
