#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include <vector>
#include "Post.hpp"

struct Thread
{
	std::vector<Post> posts;

	Thread();
	~Thread();
};

#endif
