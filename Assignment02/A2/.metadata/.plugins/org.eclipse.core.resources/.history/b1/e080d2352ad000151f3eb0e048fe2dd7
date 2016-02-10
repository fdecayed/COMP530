#ifndef PAGE_REC_ITER_H
#define PAGE_REC_ITER_H

using namespace std;

class MyDB_PageRecIter:public virtual MyDB_RecordIterator{
public:
	MyDB_PageRecIter(MyDB_RecordPtr, MyDB_PageHandle, MyDB_BufferManagerPtr);
	void MyDB_PageRecIter :: getNext ();
	bool MyDB_RecordIterator :: hasNext();
private:
	MyDB_RecordPtr recordPtr;
	MyDB_PageHandle pageHandle;
	MyDB_BufferManagerPtr bufferMgrPtr;
	size_t recordSize;
	size_t pageSize;
	void* currentloc;
};


#endif
