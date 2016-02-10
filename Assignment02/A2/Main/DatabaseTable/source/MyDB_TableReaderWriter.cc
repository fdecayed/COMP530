
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr tp, MyDB_BufferManagerPtr bp) {
	buffermgrPtr = bp;
	tablePtr = tp;

}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t) {
	static MyDB_PageReaderWriter temp;
	return temp;	
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	MyDB_RecordPtr returnval = make_shared<MyDB_Record>(tablePtr->getSchema());
	return returnval;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
	return (*this)[0];
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr) {
}

void MyDB_TableReaderWriter :: loadFromTextFile (string) {
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr) {
shared_from_this();
	return nullptr;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif

