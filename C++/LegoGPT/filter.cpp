#include "filter.h"

FilterModule::~FilterModule(){ 
}

void FilterModule::trainPreData(const string &source, const string &target){
    preData.insert(source,target);
}
void FilterModule::trainPostData(const string &source, const string &target){
    postData.insert(source,target);
}
string FilterModule::translatePreData(string question) const{
    return preData.find(question);
}
string FilterModule::translatePostData(string question) const{
    return postData.find(question);
}

void FilterArray::insert(FilterModule *input){
    FilterModule** temp1=new FilterModule* [arraySize+1];
    for ( int i=0;i<arraySize;i++){
        temp1[i]=array[i];
    }
    temp1[arraySize]=input;
    arraySize++;
    delete[]array;
    array=temp1;
    
    
}
FilterModule* FilterArray::get(int index) const{
    return array[index];
}