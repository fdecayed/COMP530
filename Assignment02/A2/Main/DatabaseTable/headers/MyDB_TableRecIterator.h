#ifndef TABLE_REC_ITER_H
#define TABLE_REC_ITER_H

#include "MyDB_RecordIterator.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageRecIterator.h"
#include "MyDB_Record.h"
using namespace std;

class MyDB_TableRecIter : public MyDB_RecordIterator{
 public:
  void getNext();
  bool hasNext();
  MyDB_TableRecIter(MyDB_TableReaderWriterPtr,MyDB_RecordPtr);
  ~MyDB_TableRecIter();

 private:
  MyDB_TableReaderWriterPtr parent;
  int curPage;
  MyDB_RecordIteratorPtr curIt;
  MyDB_RecordPtr record;
};


#endif
