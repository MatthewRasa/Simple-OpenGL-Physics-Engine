/*
 * Force.h
 */
#ifndef FORCE_H_
#define FORCE_H_

/*
 * Class to represent a force placed on a physical object.
 */
class Force {
public:

	/*
	 * DIM - number of dimensions used for the force vectors
	 */
	const static int DIM;

	/*
	 * Create a new force with no magnitude.
	 *
	 * p_name - name of the force.
	 */
	Force(char *p_name);

	/*
	 * Create a new force.
	 *
	 * p_name - name of the force
	 * p_comp - component vector of the force
	 */
	Force(char *p_name, double *p_comp);

	/*
	 * Deallocate resources.
	 */
	virtual ~Force();

	/*
	 * Add a force to combine.
	 *
	 * p_force - force to add
	 */
	void add(Force *p_force);

	/*
	 * Create a clone of the Force object.
	 */
	Force *clone();

	/*
	 * Returns:
	 *     the component vector of the force
	 */
	double *get_comp();

	/*
	 * Returns:
	 *     the name of the force
	 */
	char *get_name();

private:

	/*
	 * mp_name - name of the force
	 * mp_comp - component vector of the force
	 */
	char *mp_name;
	double *mp_comp;

};

#endif
