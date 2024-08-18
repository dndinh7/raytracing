#include "settings.h"

settings::settings() {
	for (int i = 0; i < NUM_FEATURES; ++i) {
		this->enabled_settings[i] = true;
	}
}

settings* settings::getInstance() {
	if (!singleton) {
		singleton.reset(new settings());
	}
	return singleton.get();
}

std::vector<bool> settings::getSettings() {
	return this->enabled_settings;
}

void settings::destroyInstance() {
	singleton.reset(nullptr);
}

bool settings::getAntiAliasing() {
	return enabled_settings[anti_aliasing];
}

std::unique_ptr<settings> settings::singleton = nullptr;