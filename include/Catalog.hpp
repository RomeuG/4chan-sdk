#ifndef _CATALOG_HPP_
#define _CATALOG_HPP_

#include <CatalogEntry.hpp>

struct Catalog {
    /**
	 * std::vector of CatalogEntry
	 */
    std::vector<CatalogEntry> entries;
};

#endif
