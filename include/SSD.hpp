#ifndef SSD_HPP_
#define SSD_HPP_

#include <Constants.hpp>
#include <FlashTranslationLayer.hpp>

class SSD {
	public:
		void read(address);
		void write(address, page);

	private:
		FlashTranslationLayer ftl;
};

#endif /* SSD_HPP_ */
