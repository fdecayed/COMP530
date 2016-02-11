
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include <memory>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableRecIterator.h"
#include <iostream>
using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr tp, MyDB_BufferManagerPtr bp) {
  buffermgrPtr = bp;
  tablePtr = tp;
  for(int i=0;i<=tp->lastPage();++i) pageRWs.push_back(MyDB_PageReaderWriter(bp->getPage(tp,i),bp,this));
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t i) {
   while(i > tablePtr->lastPage()){
	   MyDB_PageReaderWriter temp(buffermgrPtr->getPage(tablePtr,tablePtr->lastPage()+1),buffermgrPtr, this);
	   tablePtr -> setLastPage((size_t)(tablePtr->lastPage() + 1));
	   pageRWs.push_back(temp);
   }
  return pageRWs[i];	
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	MyDB_RecordPtr returnval = make_shared<MyDB_Record>(tablePtr->getSchema());
	return returnval;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
  if(pageRWs.empty()) pageRWs.push_back(MyDB_PageReaderWriter(buffermgrPtr->getPage(tablePtr,0),buffermgrPtr, this));
  tablePtr -> setLastPage(0);
  return pageRWs.back();
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {

  if(last().append(record)) return;
  MyDB_PageReaderWriter temp(buffermgrPtr->getPage(tablePtr,tablePtr->lastPage()+1),buffermgrPtr, this);
  tablePtr -> setLastPage((size_t)(tablePtr->lastPage() + 1));
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
	cout << "tbwr" << "\n";
  return make_shared<MyDB_TableRecIter>(shared_from_this(),record);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif

