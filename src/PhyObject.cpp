/*
 * PhysicsObject.cpp
 *
 */

#include "PhyObject.h"

/*
 * Static member declarations
 *
 * GRAV_ACC - the acceleration due to gravity
 * sp_list - list of all instantiated PhyObjects
 */
const double PhyObject::GRAV_ACC = 1;
LinkedList<PhyObject> *PhyObject::sp_list;

/*
 * Initialize the list of PhyObjects.
 */
void PhyObject::init() {
	sp_list = new LinkedList<PhyObject>();
}

/*
 * Deallocate resources, destroy the list of PhyObjects.
 */
void PhyObject::destroy() {
	delete sp_list;
}

/*
 * Call the update() function for each PhyObject.
 */
void PhyObject::update_all() {
	foreach (PhyObject *obj, sp_list)
		mthread_create(&obj->m_update_thread, NULL, obj, &PhyObject::update);
	foreach (PhyObject *obj, sp_list)
		pthread_join(obj->m_update_thread, NULL);
}

/*
 * Create a new PhyObject.
 */
PhyObject::PhyObject() :
		GraphicsObject() {
	mp_forces = new LinkedList<Force>();
	mp_grav = NULL;
	mp_pos = new double[Force::DIM];
	mp_vel = new double[Force::DIM];
	mp_acc = new double[Force::DIM];
	m_mass = m_calc_required = 0;
}

/*
 * Deallocate resources.
 */
PhyObject::~PhyObject() {
	delete[] mp_pos;
	delete[] mp_vel;
	delete[] mp_acc;
	mp_pos = mp_vel = mp_acc = NULL;
}

/*
 * Add a new force to the object.
 *
 * Params:
 *     p_force - pointer to the Force object to add
 */
void PhyObject::add_force(Force *p_force) {
	mp_forces->add(p_force);
	m_calc_required = true;
}

/*
 * Remove the force with the specified name.
 *
 * Params:
 *     p_name - name of the Force object to remove
 */
void PhyObject::rm_force(char *p_name) {
	foreach (Force *p_force, mp_forces) {
		if (!strcmp(p_name, p_force->get_name())) {
			mp_forces->rm_curr();
			break;
		}
	}
	m_calc_required = true;
}

/*
 * Set the mass of the physical object.
 * The mass determines how much a force accelerates the object.
 *
 * Params:
 *     mass - mass to set the object
 */
void PhyObject::set_mass(double mass) {
	mp_grav = new Force((char *) "gravity", new double[Force::DIM] { 0, (m_mass = mass) * GRAV_ACC, 0 });
}

/*
 * Calculate the acceleration due to the net force.
 */
void PhyObject::calc_acc() {
	Force *p_net = mp_grav->clone();
	double *p_netcomp;

	// Sum forces to calculate net force
	foreach (Force *p_force, mp_forces)
		p_net->add(p_force);

	// Calculate acceleration components by dividing the net force components by
	// the object's mass.
	p_netcomp = p_net->get_comp();
	for (int i = 0; i < Force::DIM; i++)
		mp_acc[i] = p_netcomp[i] / m_mass;

	delete p_net;
	m_calc_required = false;
}

/*
 * Update the movement vectors before each redraw.
 */
void PhyObject::update() {
	if (m_calc_required)
		calc_acc();
	for (int i = 0; i < Force::DIM; i++) {
		mp_pos[i] += mp_vel[i];
		mp_vel[i] += mp_acc[i];
	}
}
