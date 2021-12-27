#include "BodyRegistration.h"

bool BodyRegistration::operator==(const BodyRegistration& other) const {
	return body == other.body && forceGenerator == other.forceGenerator;
}
