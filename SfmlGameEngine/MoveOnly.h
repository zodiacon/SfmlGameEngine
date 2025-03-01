#pragma once

class MoveOnly abstract {
public:
	MoveOnly() = default;
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly const&) = delete;
	MoveOnly(MoveOnly&&) = default;
	MoveOnly& operator=(MoveOnly&&) = default;
};

