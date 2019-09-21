#ifndef TIMINGMANAGER_HPP_
#define TIMINGMANAGER_HPP_

#include <Constants.hpp>

class TimingManager {
	private:
		static TimingManager* instance;

		_time t;

		TimingManager()
				: t(0) {
		}

	public:
		// Setters
		void wait(_time dt) {
			t += dt;
		}

		// Getters
		static TimingManager* get_instance() {
			if (!instance) instance = new TimingManager;
			return instance;
		}

		_time get_time() const {
			return t;
		}

};

#endif /* TIMINGMANAGER_HPP_ */
