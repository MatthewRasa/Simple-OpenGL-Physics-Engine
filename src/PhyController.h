/*
 * PhyController.h
 */
#ifndef PHYCONTROLLER_H_
#define PHYCONTROLLER_H_

#include "PhyObject.h"

/*
 * Class for managing interactions between physical objects.
 */
class PhyController {
public:

	/*
	 * Initialize PhyObject and the menu.
	 */
	static void init();

	/*
	 * Deallocate resources, destroy PhyObject.
	 */
	static void destroy();

	/*
	 * Pass the update_all call to PhyObject, used for abstracting PhyObject's
	 * from the rest of the application.
	 */
	static void update_all();

private:

	/*
	 * Callback function for the menu.
	 *
	 * Params:
	 *     opt - id for the selected option
	 */
	static void menu(int opt);

	/*
	 * Initialize the menu.
	 */
	static void menu_init();

};

#endif
