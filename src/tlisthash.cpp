#include "../include/tlisthash.h"

TListHash::TListHash(int _size) : THashTable(_size) {
	pList = new std::list<TRecord>[Size];
	if (pList == nullptr) throw std::exception("TabNoMem");


}