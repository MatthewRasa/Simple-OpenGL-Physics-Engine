/*
 * PhysicsObject.cpp
 *
 */

#include "PhyObject.h"

/*
 * Static member declarations
 *
 * DIM - number of dimensions used for the movement vectors
 * sp_list - list of all instantiated PhyObjects
 */
const int PhyObject::DIM = 3;
LinkedList<PhyObject> *PhyObject::sp_list;

void PhyObject::init() {
	sp_list = new LinkedList<PhyObject>();
}

void PhyObject::update_all() {
	foreach (PhyObject *obj, sp_list)
		mthread_create(&obj->m_update_thread, NULL, obj, &PhyObject::update);
	foreach (PhyObject *obj, sp_list)
		pthread_join(obj->m_update_thread, NULL);
}

PhyObject::PhyObject() :
	GraphicsObject() {
	mp_forces = new LinkedList<Force>();
	mp_grav = new Force("gravity", new double[DIM] { 0, 1, 0 });
	mp_pos = new double[DIM];
	mp_vel = new double[DIM];
	mp_acc = new double[DIM];
	m_mass = 0;

}

PhyObject::~PhyObject() {
	delete[] mp_pos;
	delete[] mp_vel;
	delete[] mp_acc;
	mp_pos = mp_vel = mp_acc = NULL;
}

void PhyObject::add_force(Force *p_force) {
	mp_forces->add(p_force);
	calc_forces();
}

void PhyObject::rm_force(char *p_name) {
	for (mp_forces->reset(); mp_forces->has_next(); mp_forces->next()) {

	}
}

void PhyObject::calc_forces() {

}

void PhyObject::update() {
	for (int i = 0; i < DIM; i++) {
		mp_pos[i] += mp_vel[i];
		mp_vel[i] += mp_acc[i];
	}
}

