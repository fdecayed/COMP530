#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include "MyDB_PageRecIterator.h"

using namespace std;

MyDB_PageRecIter :: MyDB_PageRecIter(MyDB_RecordPtr rp, MyDB_PageReaderWriter* rw){
	pagerw = rw;
	recordPtr = rp;
	recordSize = rp ->getBinarySize();
	currentloc = rw-> pagestuff->data;
	pageSize = rw -> bufferMgrPtr ->getPageSize();
	currentBytes = 0;

};

void MyDB_PageRecIter :: getNext (){
	if(hasNext()){
		currentloc = recordPtr->fromBinary(currentloc);
		currentBytes =+ recordPtr->getBinarySize();
	}
}

bool MyDB_PageRecIter :: hasNext(){
	if((pagerw->pagestuff->numBytesUsed)>(pageSize - sizeof(PageStuff)-currentBytes) ) return true;
	return false;
}

#endif
