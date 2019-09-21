#include <FlashController.hpp>
#include <TimingManager.hpp>

void FlashController::start() {
	switch (nfc_cmd) {
		case page_read:
			read();
			break;
		case page_program:
			program();
			break;
		case block_erase:
			erase();
			break;
		default:
			// Nothing to do
			break;
	}
}

void FlashController::read() {
	// Write command 00h
	flash.set_command(Flash::command_code::read_start_address);
	// Write column address 0 (CA0)
	flash.set_ca0(this->ca0);
	// Write column address 1 (CA1)
	flash.set_ca1(this->ca1);
	// Write row address 0 (RA0)
	flash.set_ra0(this->ra0);
	// Write row address 1 (RA1)
	flash.set_ra1(this->ra1);
	// Write command 30h
	flash.set_command(Flash::command_code::read_end_address);
	// Wait tWB
	TimingManager::get_instance()->wait(tWB);
	// Wait for R_nB = 1
	while (!flash.ready())
		;

	page _page;
	for (int i = 0; i < PAGE_SIZE; i++) {
		// read data from flash
		_page.data[i] = flash.read_data();
		buffer_ram.push_back(_page);
	}
	// Write command 05h
	flash.set_command(Flash::command_code::read_start_ecc_address);
	// Write column address 0 (CA0)
	flash.set_ca0(this->ca0);
	// Write column address 1 (CA1)
	flash.set_ca1(this->ca1);
	// Write command e0h
	flash.set_command(Flash::command_code::read_end_ecc_address);
	for (int i = 0; i < 12; i++) {
		// read ECC data from flash
		flash.read_ecc_data();
	}
}

void FlashController::program() {
	// Write command 80h
	flash.set_command(Flash::command_code::program_address);
	// Write column address 0 (CA0)
	flash.set_ca0(this->ca0);
	// Write column address 1 (CA1)
	flash.set_ca1(this->ca1);
	// Write row address 0 (RA0)
	flash.set_ra0(this->ra0);
	// Write row address 1 (RA1)
	flash.set_ra1(this->ra1);

	for (int i = 0; i < PAGE_SIZE; i++) {
		// write data to flash
		flash.write_data(rand_byte());
	}
	// Write command 85h
	flash.set_command(Flash::command_code::program_start_ecc_address);
	// Write column address 0 (CA0)
	flash.set_ca0(this->ca0);
	// Write column address 1 (CA1)
	flash.set_ca1(this->ca1);
	for (int i = 0; i < 12; i++) {
		// write ECC data to flash
		flash.write_ecc_data(rand_byte());
	}
	// Write command 10h
	flash.set_command(Flash::command_code::program_end_ecc_data);
	// Wait for tWB
	TimingManager::get_instance()->wait(tWB);
	// Wait for R_nB = 1
	while (!flash.ready())
		;
	// Write command 70h
	flash.set_command(Flash::command_code::test_successful);
	if (!flash.is_successful()) {
		// Program error
	}
}

void FlashController::erase() {
	// Write command 60h
	flash.set_command(Flash::command_code::block_erase_start_address);
	// Write row address 0 (RA0)
	flash.set_ra0(this->ra0);
	// Write row address 1 (RA1)
	flash.set_ra1(this->ra1);
	// Write command d0h
	flash.set_command(Flash::command_code::block_erase_end_address);
	// Wait for tWB
	TimingManager::get_instance()->wait(tWB);
	// Wait for R_nB = 1
	while (!flash.ready())
		;
	// Write command 70h
	flash.set_command(Flash::command_code::test_successful);
	// Wait for tWHR
	TimingManager::get_instance()->wait(tWHR);
}
