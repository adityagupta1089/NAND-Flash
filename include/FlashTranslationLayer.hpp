#ifndef NANDFLASHTRANSLATIONLAYER_HPP_
#define NANDFLASHTRANSLATIONLAYER_HPP_

#include <Constants.hpp>
#include <FlashController.hpp>
#include <map>
#include <utility>

class FlashTranslationLayer {
	public:
		void read(address);
		void write(address, page);

		std::pair<int, int> get_new_block();

		int get_wear_levelling_count(int, int);
		void wear(int x, int y);

	private:
		FlashController nfc;

		std::map<address, address> mapping_table;
		std::map<std::pair<int, int>, int> wear_levelling_count;
};

#endif /* NANDFLASHTRANSLATIONLAYER_HPP_ */
