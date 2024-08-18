#ifndef SETTINGS_H
#define SETTINGS_H

#define NUM_FEATURES 1

#include <vector>
#include <memory>

enum feature {
	anti_aliasing=0,
};

class settings {
	public:

		static settings* getInstance();
		static void destroyInstance();

		bool getAntiAliasing();

		// copy constructor not allowed
		settings(settings const&) = delete;

		// assignment constructor not allowed
		settings& operator=(settings const&) = delete;

	private:
		// true if the settings will be turned on for ray_tracing
		std::vector<bool> enabled_settings{ NUM_FEATURES };

		settings();

		std::vector<bool> getSettings();

		static std::unique_ptr<settings> singleton;
};

#endif