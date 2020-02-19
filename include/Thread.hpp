#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include "Post.hpp"

#include <vector>

struct Thread {
    /**
	 * std::vector of Post
	 */
    std::vector<Post> posts;
};

#endif
