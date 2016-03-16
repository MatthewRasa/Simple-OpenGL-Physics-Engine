/*
 * Force.cpp
 */
#include "Force.h"

/*
 * Create a new force.
 *
 * p_name - name of the force
 * p_acc - acceleration vector of the force
 */
Force::Force(char *p_name, double *p_acc) {
	mp_name = p_name;
	mp_acc = p_acc;
}

/*
 * Deallocate resources.
 */
Force::~Force() {
	delete[] mp_name;
	delete[] mp_acc;
}

