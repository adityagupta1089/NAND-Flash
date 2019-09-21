#include <Constants.hpp>
#include <SSD.hpp>
#include <TimingManager.hpp>
#include <cstdlib>
#include <iostream>

int main() {
	SSD ssd;

	for (int i = 0; i < SSD_OPERATIONS; i++) {
		std::cout << "Operation " << i << ":";
		address add = (address) (SSD_SIZE
			* ((double) rand() / (double) SSD_SIZE));
		_time start = TimingManager::get_instance()->get_time();
		if ((double) rand() / (RAND_MAX) < READ_PROBABILITY) {
			std::cout << "READ";
			ssd.read(add);
		} else {
			std::cout << "WRITE";
			ssd.write(add, rand_page());
		}
		TimingManager::get_instance()->wait(1e6);
		_time end = TimingManager::get_instance()->get_time();
		int msec = (end - start) / 1e6;
		int sec = msec / 1e3;
		msec %= 1000;
		std::cout << " (" << sec << " sec, " << msec << " msec)\n";
	}

	_time time = TimingManager::get_instance()->get_time();
	int msec = time / 1e6;
	int sec = msec / 1e3;
	msec %= 1000;
	std::cout << "Time taken: " << sec << " sec, " << msec << " msec\n";

	return 0;
}
