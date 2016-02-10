
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr tp, MyDB_BufferManagerPtr bp) {
  buffermgrPtr = bp;
  tablePtr = tp;
  for(int i=0;i<=tp->lastPage();++i) pageRWs.push_back(MyDB_PageReaderWriter(bp->getPage(tp,i),bp));
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t i) {
  return pageRWs[i];	
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	MyDB_RecordPtr returnval = make_shared<MyDB_Record>(tablePtr->getSchema());
	return returnval;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
  return pageRWs.back();
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {
  if(last().append(record)) return;
  MyDB_PageReaderWriter temp(buffermgrPtr->getPage(tablePtr,tablePtr->lastPage()+1),buffermgrPtr);
  temp.append(record);
  pageRWs.push_back(temp);
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fromMe) {
  tablePtr->setLastPage(-1);
  pageRWs.clear();
  MyDB_RecordPtr record = getEmptyRecord();
  ifstream myfile(fromMe);
  string line;
  if(myfile.is_open()){
    while(getline(myfile,line)){
      record->fromString(line);
      append(record);
    }
  }
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr record) {
  return make_shared<MyDB_RecordIterator>(shared_from_this(),record);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif

