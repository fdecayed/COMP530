
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
MyDB_PageReaderWriter :: MyDB_PageReaderWriter(MyDB_PageHandle ph, MyDB_BufferManagerPtr mp){
	pageHandle = ph;
	bufferMgrPtr = mp;
	pageType = MyDB_PageType :: RegularPage;
}

void MyDB_PageReaderWriter :: clear () {

}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr rp) {
	MyDB_RecordIteratorPtr returnval = make_shared<MyDB_PageRecIter>(rp,pageHandle,bufferMgrPtr);
	return returnval;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	pageType = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr) {
	return true;
}

#endif
