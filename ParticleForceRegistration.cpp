#include "ParticleForceRegistration.h"

bool ParticleForceRegistration::operator==(const ParticleForceRegistration& reg) {
	return particle == reg.particle && forceGenerator == reg.forceGenerator;
}
