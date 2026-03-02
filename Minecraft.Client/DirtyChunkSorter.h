#pragma once
class Chunk;
class Mob;

namespace mtd2 {
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };
}

class DirtyChunkSorter : public mtd2::binary_function<const Chunk *,const Chunk *,bool> 
{
private:
	shared_ptr<Mob> cameraEntity;
	int playerIndex; // 4J added

public:
    DirtyChunkSorter(shared_ptr<Mob> cameraEntity, int playerIndex);	// 4J - added player index
	bool operator()(const Chunk *a, const Chunk *b) const;
};