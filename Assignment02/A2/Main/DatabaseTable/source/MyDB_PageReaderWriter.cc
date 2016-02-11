
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

MyDB_PageReaderWriter :: MyDB_PageReaderWriter(MyDB_PageHandle ph, MyDB_BufferManagerPtr mp, MyDB_TableReaderWriter* rw){
	pageHandle = ph;
	bufferMgrPtr = mp;
	pageType = MyDB_PageType :: RegularPage;
	tablerw = rw;
	pagestuff =(PageStuff*) pageHandle->getBytes();
}

void MyDB_PageReaderWriter :: clear () {
	MyDB_RecordPtr emptyrecord = tablerw ->getEmptyRecord();
	MyDB_RecordPtr emptyrecordforIter = tablerw -> getEmptyRecord();
	MyDB_RecordIteratorPtr itr = getIterator(emptyrecordforIter);
	void* loc = pagestuff->data;
	while(itr->hasNext()){
		loc = emptyrecord -> toBinary(loc);
	}
	pagestuff -> numBytesUsed = 0;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr rp) {
	MyDB_RecordIteratorPtr returnval = make_shared<MyDB_PageRecIter>(rp, this);
	return returnval;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	pageType = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr newrecord) {
	if((bufferMgrPtr->getPageSize() - sizeof(PageStuff) - pagestuff-> numBytesUsed) < newrecord->getBinarySize()) return false;
	MyDB_RecordPtr emptyrecord = tablerw ->getEmptyRecord();
	MyDB_RecordPtr emptyrecordforIter = tablerw -> getEmptyRecord();
	MyDB_RecordIteratorPtr itr = getIterator(emptyrecordforIter);
	void* loc = pagestuff->data;
	while(itr->hasNext()){
			loc = emptyrecord -> fromBinary(loc);
			itr ->getNext();
	}
	newrecord ->toBinary(loc);
	return true;
}

#endif
