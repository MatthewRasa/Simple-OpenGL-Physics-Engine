/*
 * PhyObject.h
 *
 *  Created on: Mar 12, 2016
 *      Author: matt
 */
#ifndef PHYOBJECT_H_
#define PHYOBJECT_H_

#include "GraphicsObject.h"
#include "Force.h"

/*
 * Class the represents a physical object in space.
 */
class PhyObject: public GraphicsObject {
public:

	/*
	 * Initialize the list of PhyObjects.
	 */
	static void init();

	/*
	 * Call the update() function for each PhyObject.
	 */
	static void update_all();

	/*
	 * Create a new PhyObject.
	 */
	PhyObject();

	/*
	 * Deallocate resources.
	 */
	virtual ~PhyObject();

	void add_force(Force *p_force);

	void rm_force(char *p_name);

private:

	/*
	 * DIM - number of dimensions used for the movement vectors
	 * sp_list - list of all instantiated PhyObjects
	 */
	static const int DIM;
	static LinkedList<PhyObject> *sp_list;

	/*
	 * mp_forces - list of forces acting on the object
	 * mp_grav - force of gravity
	 * m_mass - mass of the object
	 * mp_pos - <DIM>-dimensional vector containing the position coordinates
	 * mp_vel - <DIM>-dimensional vector containing the velocity coordinates
	 * mp_acc - <DIM>-dimensional vector containing the acceleration coordinates
	 */
	LinkedList<Force> *mp_forces;
	Force *mp_grav;
	double m_mass, *mp_pos, *mp_vel, *mp_acc;

	void calc_forces();

	/*
	 * Update the movement vectors before each redraw.
	 */
	void update();

};

#endif
