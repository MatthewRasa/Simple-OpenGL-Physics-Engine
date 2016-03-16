/*
 * Force.h
 */
#ifndef FORCE_H_
#define FORCE_H_

class Force {
public:

	/*
	 * Create a new force.
	 *
	 * p_name - name of the force
	 * p_acc - acceleration vector of the force
	 */
	Force(char *p_name, double *p_acc);

	/*
	 * Deallocate resources.
	 */
	virtual ~Force();

private:

	/*
	 * mp_name - name of the force
	 * mp_acc - acceleration vector of the force
	 */
	char *mp_name;
	double *mp_acc;

};

#endif
