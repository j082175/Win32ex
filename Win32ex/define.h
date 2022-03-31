#pragma once

#define SINGLE(type) \
static type* getInstance()\
{\
	static type mgr;\
	return &mgr;\
};