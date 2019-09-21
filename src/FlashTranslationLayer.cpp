#include <FlashTranslationLayer.hpp>
#include <vector>

void FlashTranslationLayer::read(address add) {
	address mapped = mapping_table[add];

	nfc.set_command(FlashController::command_code::page_read);
	int rows = mapped / ROW_SIZE;
	nfc.set_ra0(rows / ROWS_X);
	nfc.set_ra1(rows % ROWS_X);
	int cols = (mapped % ROW_SIZE) / COLUMN_SIZE;
	nfc.set_ca0(cols / COLUMNS_X);
	nfc.set_ca1(cols % COLUMNS_X);
	nfc.start();
}

void FlashTranslationLayer::write(address add, page _page) {
	address mapped = mapping_table[add];
	int rows = mapped / ROW_SIZE;
	int cols = (mapped % ROW_SIZE) / COLUMN_SIZE;
	int rx = rows / ROWS_X, ry = rows % ROWS_X;
	int cx = cols / COLUMNS_X, cy = cols % COLUMNS_X;

	// Copy data to buffer, with modifided entry
	for (int i = 0; i < COLUMNS_X; i++) {
		for (int j = 0; j < COLUMNS_Y; j++) {
			if (i == cx && j == cy) {
				nfc.getBufferRam().push_back(_page);
			} else {
				nfc.set_command(FlashController::command_code::page_read);
				nfc.set_ra0(rx);
				nfc.set_ra1(ry);
				nfc.set_ca0(i);
				nfc.set_ca1(j);
				nfc.start();
			}
		}
	}

	// garbage collection
	nfc.set_command(FlashController::command_code::block_erase);
	nfc.set_ra0(rx);
	nfc.set_ra1(ry);
	nfc.start();
	wear(rx, ry);

	// re write from buffer
	std::pair<int, int> new_block = get_new_block();
	for (int i = 0; i < COLUMNS_X; i++) {
		for (int j = 0; j < COLUMNS_Y; j++) {
			nfc.set_command(FlashController::command_code::page_program);
			nfc.set_ra0(new_block.first);
			nfc.set_ra1(new_block.second);
			nfc.set_ca0(i);
			nfc.set_ca1(j);
			nfc.start();
		}
	}
	wear(rx, ry);

	nfc.getBufferRam().clear();
}

std::pair<int, int> FlashTranslationLayer::get_new_block() {
	int min_cnt = WEAR_LIMIT;
	int min_loc_x, min_loc_y;
	for (int i = 0; i < ROWS_X; i++) {
		for (int j = 0; j < ROWS_Y; j++) {
			int wear_cnt = get_wear_levelling_count(i, j);
			if (wear_cnt < min_cnt) {
				min_cnt = wear_cnt;
				min_loc_x = i;
				min_loc_y = j;
			}
		}
	}
	return std::make_pair(min_loc_x, min_loc_y);
}

int FlashTranslationLayer::get_wear_levelling_count(int x, int y) {
	std::pair<int, int> loc = std::make_pair(x, y);
	if (wear_levelling_count.find(loc) != wear_levelling_count.end()) {
		return wear_levelling_count[loc];
	} else {
		return 0;
	}
}

void FlashTranslationLayer::wear(int x, int y) {
	std::pair<int, int> loc = std::make_pair(x, y);
	if (wear_levelling_count.find(loc) != wear_levelling_count.end()) {
		wear_levelling_count[loc]++;
	} else {
		wear_levelling_count[loc] = 1;
	}
}
