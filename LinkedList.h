/*
 * LinkedList.h
 *
 * Contains template class LinkedList.
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "stdio.h"
#include "stdlib.h"
#include "typeinfo"

/*
 * Template class that models a LinkedList.
 */
template<typename T> class LinkedList {
public:

	/*
	 * REMOVE_DATA - Remove all data contained within the list on deletion
	 * FREE_DATA - Free all data contained within the list on deletion
	 */
	static const bool REMOVE_DATA = 0, FREE_DATA = 1;

	/*
	 * Initialize empty LinkedList with the specified delete mode
	 *
	 * Params:
	 *     delete_mode - deletion mode for the list
	 */
	LinkedList<T>(bool delete_mode) {
		mp_curr = mp_head = mp_tail = NULL;
		m_length = 0;
		m_delete_mode = delete_mode;
	}

	/*
	 * Initialize empty LinkedList.
	 */
	LinkedList<T>() {
		mp_curr = mp_head = mp_tail = NULL;
		m_length = 0;
		m_delete_mode = REMOVE_DATA;
	}

	/*
	 * Clear the LinkedList, deleting all Nodes/elements.
	 */
	virtual ~LinkedList<T>() {
		m_delete_mode ? free() : clear();
	}

	/*
	 * Add an element of type 'T' to the list after the current Node.
	 *
	 * Params:
	 *     p_elem - pointer of element to add
	 */
	void add(T *p_elem) {
		if (mp_curr == NULL) { // List is empty
			mp_curr = mp_head = mp_tail = new Node(p_elem);
		} else {
			Node *p_temp = new Node(p_elem);
			if (mp_curr->mp_next == NULL) { // List points to tail
				mp_tail = p_temp;
			} else {
				p_temp->mp_next = mp_curr->mp_next;
				p_temp->mp_next->mp_prev = p_temp;
			}
			p_temp->mp_prev = mp_curr;
			mp_curr->mp_next = p_temp;
			mp_curr = p_temp;
		}
		m_length++;
	}

	/*
	 * Add an element of type 'T' to the list before the current Node.
	 *
	 * Params:
	 *     p_elem - pointer of element to add
	 */
	void add_before(T *p_elem) {
		if (mp_curr == NULL) { // List is empty
			mp_curr = mp_head = mp_tail = new Node(p_elem);
		} else {
			Node *p_temp = new Node(p_elem);
			if (mp_curr->mp_prev == NULL) { // List points to head
				mp_head = p_temp;
			} else {
				p_temp->mp_prev = mp_curr->mp_prev;
				p_temp->mp_prev->mp_next = p_temp;
			}
			p_temp->mp_next = mp_curr;
			mp_curr->mp_prev = p_temp;
		}
		m_length++;
	}

	/*
	 * Delete all Nodes/elements from the list.
	 */
	void clear() {
		for (reset(); has_next(); rm_curr());
		mp_curr = mp_head = mp_tail = NULL;
	}

	/*
	 * Remove all Nodes/elements from the list, but do not delete the elements.
	 */
	void free() {
		for (reset(); has_next(); free_curr());
		mp_curr = mp_head = mp_tail = NULL;
	}

	/*
	 * Frees the current Node.
	 *
	 * Returns:
	 *     the pointer to the element contained within the deleted Node
	 */
	T *free_curr() {
		// Save removed p_node
		Node *p_node = mp_curr;
		T *p_elem = p_node->mp_elem;

		// Remove p_node from list
		if (p_node->mp_prev != NULL)
			p_node->mp_prev->mp_next = p_node->mp_next;
		if (p_node->mp_next != NULL)
			p_node->mp_next->mp_prev = p_node->mp_prev;

		// Reset the current p_node
		if (p_node == mp_head)
			mp_head = mp_curr = p_node->mp_next;
		else if (p_node == mp_tail)
			mp_tail = mp_curr = p_node->mp_prev;
		else
			mp_curr = p_node->mp_next;

		// Deallocate removed p_node
		delete p_node;
		m_length--;

		return p_elem;
	}

	/*
	 * Returns:
	 *     a pointer to the element contained in the current Node.
	 */
	T* curr() {
		return mp_curr->mp_elem;
	}

	/*
	 * Determine if there are elements after the current Node.
	 *
	 * Returns:
	 *     true if there are elements following the current Node
	 */
	bool has_next() {
		return mp_curr != NULL;
	}

	/*
	 * Increment the list to point to the next Node.
	 */
	void next() {
		if (mp_curr == NULL) {
			printf("[ERROR] Tried to increment past last node in list.");
			return;
		}
		mp_curr = mp_curr->mp_next;
	}

	/*
	 * Removes the current Node.
	 */
	void rm_curr() {
		T *p_elem = free_curr();
		sizeof(p_elem) > sizeof(T) ? delete[] p_elem : delete p_elem;
	}

	/*
	 * Set the current Node to the head Node (at the front of the list).
	 * This is useful to call before iterating through the entire list.
	 */
	void reset() {
		mp_curr = mp_head;
	}

	/*
	 * Set the deletion mode for the list.
	 *
	 * Params:
	 *     delete_mode - determine whether to remove or free on list deletion
	 */
	void set_delete_mode(bool delete_mode) {
		m_delete_mode = delete_mode;
	}

	/*
	 * Get the size of the list.
	 *
	 * Returns:
	 *     the current number of Nodes in the list
	 */
	int size() {
		return m_length;
	}

	/*
	 * Set the list to the tail Node.
	 */
	void to_tail() {
		mp_curr = mp_tail;
	}

private:

	/*
	 * Represents a Node in the LinkedList.
	 */
	class Node {
	public:

		/*
		 * Initialize a new Node with an element to hold.
		 *
		 * Params:
		 *     p_elem - pointer to the element to be placed in the Node
		 */
		Node(T *p_elem) {
			mp_elem = p_elem;
			mp_next = mp_prev = NULL;
		}

		/*
		 * Set all pointers to NULL, but do not deallocate any resources.
		 * The element contained within the Node is not deleted so that it can
		 * be returned after this Node is deleted during remove().
		 */
		~Node() {
			mp_elem = NULL;
			mp_next = mp_prev = NULL;
		}

		/*
		 * mp_next - pointer to the next Node in the list
		 * mp_prev - pointer to the previous Node in the list
		 * mp_elem - pointer to the element contained in this node
		 */
		Node *mp_next, *mp_prev;
		T *mp_elem;
	};

	/*
	 * mp_curr - pointer to the current location in the list
	 * mp_head - pointer to the first Node entered into the list
	 * mp_tail - pointer to the last Node entered into the list
	 * m_length - current number of elements in the list
	 */
	Node *mp_curr, *mp_head, *mp_tail;
	int m_length;
	bool m_delete_mode;

};

/*
 * Macro to simulate for-each loop.
 */
#define foreach(elem, l) \
	if (int _cont = 1) \
		if (typeof(l) _list = (l)) \
			for (_list->reset(); _list->has_next(); _list->next(), _cont = !_cont) \
				for (elem = _list->curr(); _cont; _cont = !_cont)

/*
 * Macro to simulate a for-each loop that frees each element from the list.
 * Used for easily copying elements out of one list
 */
#define forfreeeach(elem, l) \
	if (int _cont = 1) \
		for (typeof(l) _list = (l); _list != NULL; _list->set_delete_mode(LinkedList<typeof(l)>::FREE_DATA), delete _list, _list = NULL) \
			for (_list->reset(); _list->has_next(); _list->next(), _cont = !_cont) \
				for (elem = _list->curr(); _cont; _cont = !_cont)

/*
 * Macro to simulate a for-each loop that deletes the original list.
 * Used for easily cleaning up lists returned from functions.
 */
#define forrmeach(elem, l) \
	if (int _cont = 1) \
		for (typeof(l) _list = (l); _list != NULL; _list->set_delete_mode(LinkedList<typeof(l)>::REMOVE_DATA), delete _list, _list = NULL) \
			for (_list->reset(); _list->has_next(); _list->next(), _cont = !_cont) \
				for (elem = _list->curr(); _cont; _cont = !_cont)

#endif
