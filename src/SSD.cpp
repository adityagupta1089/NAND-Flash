#include <SSD.hpp>

void SSD::read(address add) {
	ftl.read(add);
}

void SSD::write(address add, page _page) {
	ftl.write(add, _page);
}
