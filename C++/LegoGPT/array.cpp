#include "array.h"

DataMap::DataMap(){
    arraySize=0;
    keys=nullptr;
    values=nullptr;
}
DataMap::~DataMap(){
    clear();
}
void DataMap::clear(){
    if (arraySize!=0){
        arraySize=0;
        delete[]keys;
        delete[]values;
    }
}
void DataMap::insert(const string &key, const string &value){
    
    string *temp_key= new string[arraySize+1];
    string *temp_value= new string[arraySize+1];
    for (int i = 0; i < arraySize; i++)
    {
        temp_key[i] = keys[i];
        temp_value[i]=values[i];
    }
    temp_key[arraySize] = key;
    temp_value[arraySize] = value;
    arraySize++;
    delete[] keys;
    delete []values;
    keys=temp_key;
    values=temp_value;
    return;
}
string DataMap::find(const string &key) const{
    string no="no";
    for(int i=0;i<arraySize;i++){
        if(keys[i]==key){
            return values[i];
        }
        
    }
    return no;
    
}
