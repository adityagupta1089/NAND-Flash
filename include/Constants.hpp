#ifndef INCLUDE_CONSTANTS_HPP_
#define INCLUDE_CONSTANTS_HPP_

#include <bitset>
#include <cstdlib>

typedef std::bitset<8> byte;

const int PAGE_SIZE = 2048;

struct page {
		byte data[PAGE_SIZE];
};

inline byte rand_byte() {
	byte result;
	for (int i = 0; i < 8; i++) {
		result[i] = rand() % 2;
	}
	return result;
}

inline page rand_page() {
	page result;
	for (int i = 0; i < PAGE_SIZE; i++) {
		result.data[i] = rand_byte();
	}
	return result;
}

typedef unsigned long long address;

typedef unsigned long long _time;

const _time tWB = 5e5;
const _time tWHR = 5e5;
const _time ECC_WAIT_TIME = 5e5;
const _time WRITE_LATENCY = 5e5;

const int SSD_OPERATIONS = 1000;
const double READ_PROBABILITY = 0.5;
const unsigned long long SSD_SIZE = 1024ULL;

const int COLUMNS_X = 2;
const int COLUMNS_Y = 2;
const int ROWS_X = 2;
const int ROWS_Y = 2;

const unsigned long long ROW_SIZE = SSD_SIZE / (ROWS_X * ROWS_Y);
const unsigned long long COLUMN_SIZE = ROW_SIZE / (COLUMNS_X * COLUMNS_Y);

const int WEAR_LIMIT = 10000;

#endif /* INCLUDE_CONSTANTS_HPP_ */
