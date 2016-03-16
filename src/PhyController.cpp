/*
 * PhyController.cpp
 *
 *
 */

#include "PhyController.h"

void PhyController::init() {
	PhyObject::init();
	menu_init();
}

void PhyController::destroy() {

}

void PhyController::update_all() {
	PhyObject::update_all();
}

void PhyController::menu_init() {
	glutCreateMenu(&menu);
	glutAddMenuEntry("Option 1", 1);
	glutAddMenuEntry("Option 2", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void PhyController::menu(int opt) {

}

