#ifndef _CATALOG_HPP_
#define _CATALOG_HPP_

#include <CatalogEntry.hpp>

namespace channer::json
{
struct Catalog {
    /**
	 * std::vector of CatalogEntry
	 */
    std::vector<CatalogEntry> entries;
};
}
#endif
