#ifndef PAGE_REC_ITER_H
#define PAGE_REC_ITER_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"
#include "MyDB_PageReaderWriter.h"

using namespace std;
//class MyDB_PageRecIter;
//typedef shared_ptr <MyDB_PageRecIter> MyDB_PageRecIteratorPtr;

class MyDB_PageRecIter : public MyDB_RecordIterator{
public:
	MyDB_PageRecIter(MyDB_RecordPtr, MyDB_PageHandle, MyDB_BufferManagerPtr);
	void getNext ();
	bool hasNext();
private:
	MyDB_RecordPtr recordPtr;
	MyDB_PageHandle pageHandle;
	MyDB_BufferManagerPtr bufferMgrPtr;
	size_t recordSize;
	size_t pageSize;
	void* currentloc;
};


#endif
