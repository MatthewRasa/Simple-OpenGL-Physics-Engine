/*
 * Force.cpp
 */
#include "Force.h"

/*
 * DIM - number of dimensions used for the force vectors
 */
const int Force::DIM = 3;

/*
 * Create a new force with no magnitude.
 *
 * p_name - name of the force.
 */
Force::Force(char *p_name) :
	Force(p_name, new double[DIM] { 0, 0, 0 }) {
}

/*
 * Create a new force.
 *
 * p_name - name of the force
 * p_acc - acceleration vector of the force
 */
Force::Force(char *p_name, double *p_acc) {
	mp_name = p_name;
	mp_comp = p_acc;
}

/*
 * Deallocate resources.
 */
Force::~Force() {
	delete[] mp_name;
	delete[] mp_comp;
}

/*
 * Add a force to combine.
 *
 * p_force - force to add
 */
void Force::add(Force *p_force){
	for (int i = 0; i < DIM; i++)
		mp_comp[i] += p_force->mp_comp[i];
}

/*
 * Create a clone of the Force object.
 */
Force *Force::clone() {
	Force *clone = new Force(mp_name);
	clone->add(this);
	return clone;
}

/*
 * Returns:
 *     the component vector of the force
 */
double *Force::get_comp() {
	return mp_comp;
}

/*
 * Returns:
 *     the name of the force
 */
char *Force::get_name() {
	return mp_name;
}
