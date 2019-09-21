#ifndef NANDFLASHCONTROLLER_H_
#define NANDFLASHCONTROLLER_H_

#include <Constants.hpp>
#include <Flash.hpp>
#include <vector>

class FlashController {
	public:
		enum command_code {
			block_erase = 0b100,
			page_program = 0b001,
			page_read = 0b010,
			nop = 0b0
		};

		FlashController()
				: nfc_cmd(nop), ra0(0), ra1(0), ca0(0), ca1(0) {
		}

		void start();

	private:
		Flash flash;
		command_code nfc_cmd;

		address ra0, ra1, ca0, ca1;

		std::vector<page> buffer_ram;

		void read();
		void program();
		void erase();

	public:
		// Setters
		void set_command(command_code cmd) {
			nfc_cmd = cmd;
		}

		void set_ca0(address ca0) {
			this->ca0 = ca0;
		}

		void set_ca1(address ca1) {
			this->ca1 = ca1;
		}

		void set_ra0(address ra0) {
			this->ra0 = ra0;
		}

		void set_ra1(address ra1) {
			this->ra1 = ra1;
		}

		// Getters
		std::vector<page>& getBufferRam() {
			return buffer_ram;
		}
};

#endif /* NANDFLASHCONTROLLER_H_ */
