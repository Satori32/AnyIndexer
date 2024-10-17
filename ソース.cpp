/** /
#include <stdio.h>
#include <memory.h>

#include "MemoryAllocator.h"


struct AnyIndexer {
	Memory<char> T;
	size_t P = 0;

	bool (*EQr)(const char*, const char*, size_t);
};

bool F(const char* A, const char* B,size_t N) {
	return memcmp(A, B, N)==0;
}

template<class T>
AnyIndexer ConstructAny(T& In) {
	Any A;
	A.T = ConstructMemory<char>(sizeof(T));
	A.P = 0;
	A.T.Copy(&in, sizeof(T));
	A.EQr = F;

	return A;
}
template<class T>
AnyIndexer ConstructAny(T& In,bool (*Fun)(const char*, const char*,size_t)) {
	Any A;
	A.T = ConstructMemory<char>(sizeof(T));
	A.P = 0;
	A.T.Copy(&in, sizeof(T));
	A.EQr = Fun;

	return A;
}

bool Free(AnyIndexer& In) {
	In.EQr = NULL;
	In.P = 0;
	Free(In.T);
	return true;
}

template<class T>
bool EQ(AnyIndexer& In, const T& X) {
	if (Index(In.T, 0) == NULL) { return NULL; }
	T* Y = (T*)Index(In.T, 0);

	return In.EQr((char*)Y,(char*)&X,sizeof(T));

}

bool EQ(AnyIndexer& In, AnyIndexer& X) {
	if (Index(In.T, 0) == NULL) { return NULL; }
	if (Index(X.T, 0) == NULL) { return NULL; }

	return In.EQr((char*)Index(In.T,0), (char*)Index(X.T,0), Size(In.T));

}
template<class T>
bool NotEQ(AnyIndexer& In,const T& X) {
	if (Index(In.T, 0) == NULL) { return NULL; }
	T* Y = (T*)Index(In.T, 0);

	return !In.EQr((char*)Y,(char*)&X,sizeof(T));
}
bool NotEQ(AnyIndexer& In, AnyIndexer& X) {
	if (Index(In.T, 0) == NULL) { return NULL; }
	if (Index(X.T, 0) == NULL) { return NULL; }

	return !In.EQr((char*)Index(In.T,0), (char*)Index(X.T,0), Size(In.T));

}
/**/

#include "AnyIndexer.h"
int main() {
	AnyIndexer A = ConstructAny<int>(10);
	Free(A);

	return 0;
}