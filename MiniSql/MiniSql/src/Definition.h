#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include <string>
#include <vector>

#define BLOCKNUM 10
#define BLOCKSIZE 4096
typedef unsigned char BYTE;
typedef int ADDRESS;
typedef std::vector<std::vector<std::string>> RECORDBUFFER;

struct Expression;
struct Operand;
class Table;
class Data;
class Block;
class ArrayList;

enum OPERATOR
{
	GREATER,
	LESS,
	EQUAL,
	NOTEQUAL,
	GREATER_AND_EQUAL,
	LESS_AND_EQUAL,
	UNDEFINED
};

OPERATOR reverseOperator(OPERATOR op);

struct Operand
{
	std::string operandName;
	bool isAttribute;
};

struct Expression
{
	Operand leftOperand;
	Operand rightOperand;
	OPERATOR op;
	void swap();
};

enum TYPE
{
	INT,
	CHAR,
	FLOAT,
	UNDEFINEDTYPE
};

TYPE stringToTYPE(std::string s);
OPERATOR stringToOperator(std::string s);

class Table
{
public:
	Table(){}
	Table(const std::string& tableName, std::vector<Data>& tableVec);
	const std::string& getTableName()const { return tableName; }
	void setTableName(const std::string& tableName) { this->tableName = tableName; }
	const std::vector<Data>& getTableVec()const { return tableVec; }
	void setTableVec(const std::vector<Data>& tableVec);
	int getPrimaryKeyIndex()const { return primaryKeyIndex; }
	void setPrimaryKeyIndex(int primaryKeyIndex) { this->primaryKeyIndex = primaryKeyIndex; }
	int getLength()const{return length;}
	void pushData(Data& data) { tableVec.push_back(data); }
	bool isAttribute(const std::string& s);
	Data getData(const std::string& s);
	~Table(){}
private:
	std::string tableName;
	std::vector<Data> tableVec;
	int primaryKeyIndex;
	int length;
};

class Data
{
private:
	std::string attribute;
	TYPE type;
	int length;
	int offset;
	bool uniqueFlag;
	bool primaryFlag;
public:
	Data():uniqueFlag(false),primaryFlag(false){}
	Data(const std::string& attribute, TYPE type, int length, bool isUnique, bool isPrimary)
		:attribute(attribute), type(type), length(length), uniqueFlag(isUnique) ,primaryFlag(isPrimary){};
	const std::string& getAttribute()const { return attribute; }
	void setAttribute(const std::string& attr) { attribute = attr; }
	TYPE getType()const { return type; }
	void setType(TYPE type);
	int getLength()const{ return length; }
	void setLength(int len) { length = len; }
	bool isUnique()const { return uniqueFlag; }
	void setUnique(bool flag) { uniqueFlag = flag; }
	bool isPrimary()const { return primaryFlag; }
	void setPrimary(bool flag) { primaryFlag = flag; }
	void setOffset(const int off){ offset = off; }
	int getOffset(){ return offset; }
	~Data(){}
};

class Block
{
public:
	Block(){ dirtyBit = false; isPinned = false; }
	~Block(){}
	void setBlockData(BYTE* data){ memcpy(blockData, data, BLOCKSIZE); }
	BYTE* getBlockData(){ return blockData; }
	void setDirtyBit(bool isDirty){ this->dirtyBit = isDirty; }
	bool getDirtyBit(){ return dirtyBit; }
	void setPinnedBit(bool pinnnedBit){ this->isPinned = pinnnedBit; }
	bool getPinnnedBit(){ return isPinned; }
	void setFileName(const std::string& fileName){ this->fileName = fileName; }
	std::string getFileName(){ return fileName; }
	void setTag(ADDRESS tag){ this->tag = tag; }
	ADDRESS getTag(){ return tag; }
	void clear(){ dirtyBit = false; fileName = ""; }
private:
	BYTE blockData[BLOCKSIZE];
	bool dirtyBit;
	bool isPinned;
	ADDRESS tag;
	std::string fileName;
};

class ArrayList
{
private:
	int header, tail;
	struct{
		int last;
		int next;
	} arraylist[BLOCKNUM];
public:
	ArrayList();
	~ArrayList();
	void moveTail(int index);
	int getHeader();
	int getNext(int index){ return arraylist[index].next; }	//test function
};

#endif