#ifndef PAGE_REC_ITER_H
#define PAGE_REC_ITER_H

using namespace std;

class MyDB_PageRecIter:public virtual MyDB_RecordIterator{
public:
	MyDB_PageRecIter(MyDB_RecordPtr, MyDB_PageReaderWriter*);
	void MyDB_PageRecIter :: getNext ();
	bool MyDB_PageRecIter :: hasNext();
private:
	MyDB_PageReaderWriter* pagerw;
	MyDB_RecordPtr recordPtr;
	size_t recordSize;
	size_t pageSize;
	void* currentloc;
	int currentBytes;
};


#endif
