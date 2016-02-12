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
		recordPtr->fromBinary(pagerw->pagestuff->data+currentBytes);
		currentBytes += recordPtr->getBinarySize();
	}
}

bool MyDB_PageRecIter :: hasNext(){
	//cout<<"test:"<<pagerw-> pagestuff-> numBytesUsed<<"\n";
	pagerw->pagestuff =(PageStuff*) pagerw->pageHandle->getBytes();
	if((pagerw-> pagestuff-> numBytesUsed) > currentBytes ) return true;
	//cout<<"pagerw-> pagestuff-> numBytesUsed"<<endl;
	//cout<<pagerw-> pagestuff-> numBytesUsed<<endl;
	//cout<<"currentBytes"<<endl;
	//cout<<currentBytes<<endl;
	return false;
}

#endif
