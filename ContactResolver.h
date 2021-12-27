#pragma once
#include <Eigen/Dense>
#include <list>

class Contact;

class ContactResolver {
public:
	void resolveContacts(const std::list<Contact>& contacts, int iterations) const;
};

