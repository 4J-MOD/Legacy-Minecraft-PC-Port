#pragma once
class Entity;
class Chunk;

namespace std {
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };
}

class DistanceChunkSorter : public std::binary_function<const Chunk *,const Chunk *,bool> 
{
private:
	double ix, iy, iz;

public:
    DistanceChunkSorter(shared_ptr<Entity> player);
	bool operator()(const Chunk *a, const Chunk *b) const;
};