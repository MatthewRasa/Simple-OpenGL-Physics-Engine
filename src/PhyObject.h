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
	 * Deallocate resources, destroy the list of PhyObjects.
	 */
	static void destroy();

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

protected:

	/*
	 * GRAV_ACC - the acceleration due to gravity
	 */
	static const double GRAV_ACC;

	/*
	 * Add a new force to the object.
	 *
	 * Params:
	 *     p_force - pointer to the Force object to add
	 */
	void add_force(Force *p_force);

	/*
	 * Remove the force with the specified name.
	 *
	 * Params:
	 *     p_name - name of the Force object to remove
	 */
	void rm_force(char *p_name);

	/*
	 * Set the mass of the physical object.
	 * The mass determines how much a force accelerates the object.
	 *
	 * Params:
	 *     mass - mass to set the object
	 */
	void set_mass(double mass);

private:

	/*
	 * sp_list - list of all instantiated PhyObjects
	 */
	static LinkedList<PhyObject> *sp_list;

	/*
	 * mp_forces - list of forces acting on the object
	 * mp_grav - force of gravity
	 * m_mass - mass of the object
	 * mp_pos - <DIM>-dimensional vector containing the position coordinates
	 * mp_vel - <DIM>-dimensional vector containing the velocity coordinates
	 * mp_acc - <DIM>-dimensional vector containing the acceleration coordinates
	 * m_calc_required - true when a force has been added or removed
	 */
	LinkedList<Force> *mp_forces;
	Force *mp_grav;
	double m_mass, *mp_pos, *mp_vel, *mp_acc;
	bool m_calc_required;

	/*
	 * Calculate the acceleration due to the net force.
	 */
	void calc_acc();

	/*
	 * Update the movement vectors before each redraw.
	 */
	void update();

};

#endif
