#include <Flash.hpp>
#include <TimingManager.hpp>

bool Flash::ready() {
	return true;
}

byte Flash::read_data() {
	return 0;
}

byte Flash::read_ecc_data() {
	return 0;
}

void Flash::write_data(byte data) {
	TimingManager::get_instance()->wait(WRITE_LATENCY);
	return;
}

void Flash::write_ecc_data(byte data) {
	TimingManager::get_instance()->wait(ECC_WAIT_TIME);
	return;
}

