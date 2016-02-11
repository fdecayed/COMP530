#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include "MyDB_PageRecIterator.h"

using namespace std;

MyDB_PageRecIter :: MyDB_PageRecIter(MyDB_RecordPtr rp,MyDB_PageHandle ph, MyDB_BufferManagerPtr bm){
	pageHandle = ph;
	recordPtr = rp;
	recordSize = rp ->getBinarySize();
	bufferMgrPtr = bm;
	pageSize = bm ->getPageSize();
	currentloc = rp->fromBinary(ph->getBytes());
};

void MyDB_PageRecIter :: getNext (){
	currentloc = recordPtr->fromBinary(currentloc);
}

bool MyDB_RecordIterator :: hasNext(){
	return true;
}

#endif
