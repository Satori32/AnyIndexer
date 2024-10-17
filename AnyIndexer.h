#pragma once
#include <stdio.h>
#include <memory.h>

#include "MemoryAllocator.h"


struct AnyIndexer {
	Memory<char> T;
	size_t P = 0;

	bool (*EQr)(const char*, const char*, size_t);
};

template<class T> AnyIndexer ConstructAny(T& In);
template<class T> AnyIndexer ConstructAny(T& In, bool (*Fun)(const char*, const char*, size_t));
bool Free(AnyIndexer& In);
template<class T> bool EQ(AnyIndexer& In, const T& X);
bool EQ(AnyIndexer& In, AnyIndexer& X);
template<class T> bool NotEQ(AnyIndexer& In, const T& X);
bool NotEQ(AnyIndexer& In, AnyIndexer& X);