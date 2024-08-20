#ifndef LIST_H
#define LIST_H

template <class T>
class ListNode {
public:
	ListNode();
	template <class U>
	friend class List;
private:
	T* indirectObject;
	ListNode* link;
};

template <class T>
class List { // Interface for a List template as an indirect container.
public:
// Modifiers Members:
	int insert(T& object);
	int append(T& object);
	T* remove();
	void reset();
	void next();
	T* retrieve();
	T* operator[](int i);
// Implementor Members:
	int size();
	int end();
// Backbone Members:
	List& operator= (const List& l);
	List(const List& l);
	List();
	~List();
private:
	ListNode <T>* head;
	ListNode <T>* current;
	int count;
};
#endif // !LIST_H
