#include "ContactResolver.h"
#include "Contact.h"
#include "RigidBody.h"

void ContactResolver::resolveContacts(const std::list<Contact>& contacts, int iterations) const
{
	for (auto& contact : contacts)
		contact.resolveContact();
}
