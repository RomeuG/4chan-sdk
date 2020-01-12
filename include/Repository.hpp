#ifndef _REPOSITORY_HPP_
#define _REPOSITORY_HPP_

#include <Catalog.hpp>
#include <Constants.hpp>
#include <Download.hpp>
#include <JsonUtils.hpp>
#include <Thread.hpp>

namespace channer::repo
{
auto get_thread(std::string const& board, std::string const& thread, bool file_only = false) -> Thread;
auto get_catalog(std::string const& board, bool file_only = false) -> Catalog;
}

#endif
