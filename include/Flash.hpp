#ifndef NAND_FLASH_HPP_
#define NAND_FLASH_HPP_

#include <Constants.hpp>

class Flash {
	public:
		enum command_code {
			read_start_address = 0x00,
			read_end_address = 0x30,
			read_start_ecc_address = 0x05,
			read_end_ecc_address = 0xe0,

			program_address = 0x80,
			program_start_ecc_address = 0x85,
			program_end_ecc_data = 0x10,

			block_erase_start_address = 0x60,
			block_erase_end_address = 0xD0,

			test_successful = 0x70,
			nop
		};

		Flash()
				: nf_cmd(nop), ra0(0), ra1(0), ca0(0), ca1(0), successful(0) {
		}

		bool ready();

		byte read_data();
		byte read_ecc_data();

		void write_data(byte);
		void write_ecc_data(byte);

	private:
		command_code nf_cmd;

		address ra0, ra1, ca0, ca1;

		bool successful;

	public:
		// Setters
		void set_command(command_code cmd) {
			nf_cmd = cmd;
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
		bool is_successful() const {
			return this->successful;
		}
};

#endif /* NAND_FLASH_HPP_ */
