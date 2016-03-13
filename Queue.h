/*
 * Queue.h
 *
 * Contains template class Queue.
 */
#ifndef QUEUE_H_
#define QUEUE_H_

/*
 * Template class that models a linked queue.
 */
template<typename T>
class Queue {
public:

	/*
	 * Initialize a new queue.
	 */
	Queue() {
		mp_list = new LinkedList<T>();
	}

	/*
	 * Dellocate resources
	 */
	~Queue() {
		delete mp_list;
	}

	/*
	 * Add element to the tail of the queue.
	 *
	 * Params:
	 *     p_elem - element to enqueue
	 */
	void enqueue(T *p_elem) {
		mp_list->to_tail();
		mp_list->add(p_elem);
	}

	/*
	 * Remove element from the head of the queue.
	 *
	 * Returns:
	 *     the dequeued element
	 */
	T *dequeue() {
		mp_list->reset();
		return mp_list->free();
	}

private:

	/*
	 * mp_list - underlying LinkedList storing the data for the queue
	 */
	LinkedList<T> *mp_list;
};

#endif
