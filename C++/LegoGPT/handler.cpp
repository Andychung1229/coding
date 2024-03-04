#include "handler.h"
HandlerModule::~HandlerModule(){
    // delete languageFilter;
    // delete toneFilter;
}
void HandlerModule::trainData(const string &question, const string &answer){
    data.insert(question,answer);
}
string HandlerModule::inneranswer(const string &question) const{
    return data.find(question);
}
string HandlerModule::answer(const string &question) const{
    string ques=question;
    string answer;
    string no="no";
    // cout<<ques<<endl;
    if(languageFilter!=nullptr&&toneFilter!=nullptr){
        
        ques=languageFilter->translatePreData(question);
        
        if(ques!=no){
            
            string ques2=toneFilter->translatePreData(ques);
            if(ques2!=no){
                ques=ques2;
            }
        }else{
            ques=toneFilter->translatePreData(question);
        }
        
        
        if(ques==no){
            ques=question;
        }
    }
    else if (languageFilter!=nullptr ){
        ques=languageFilter->translatePreData(question);
        // cout<<ques<<endl;
        if(ques==no){
            ques=question;
        }
    }
    else if(toneFilter!=nullptr){
        ques=toneFilter->translatePreData(question);
        // cout<<ques<<endl;
        if(ques==no){
            ques=question;
        }
    }
    answer=inneranswer(ques);
    // cout<<answer<<endl;
    
    if(languageFilter!=nullptr&&toneFilter!=nullptr){
        string answer1=toneFilter->translatePostData(answer);
        // cout<<answer1<<endl;
        if(answer1==no){
            string answer2=languageFilter->translatePostData(answer);
            cout<<answer2<<endl;
            if(answer2!=no){
                // answer=answer2;
            }
        }else{
            string answer2=languageFilter->translatePostData(answer1);
            // cout<<answer2<<endl;
            if(answer2!=no){
                answer=answer2;
            }
            else {
                answer=answer1;
            }
        }
        // cout<<answer<<endl;
        
    }
    else if (languageFilter!=nullptr ){
        string answer1=languageFilter->translatePostData(answer);
        if(answer1!=no){
            answer=answer1;
        }
    }
    else if(toneFilter!=nullptr){
        string answer1=toneFilter->translatePostData(answer);
        if(answer1!=no){
            answer=answer1;
        }
        // cout<<answer<<endl;
    }
    if (answer=="no"){
        string temp="Sorry, I don't know";
        return temp;
    }
    return answer;
}

HandlerMap::HandlerMap(){
    arraySize=0;
    names=nullptr;
    handlerModules=nullptr;
}
void HandlerMap::clear(){
    if (arraySize != 0){
        {
            
            delete[] handlerModules;
            
            delete[] names;
            
        }
        return;
        arraySize=0;
    }

    
}
HandlerMap::~HandlerMap(){
    clear();
}
void HandlerMap::insert(string key, HandlerModule* value){
    if(arraySize==0){
        names=new string[1];
        handlerModules= new HandlerModule*[1];
        names[0]=key;
        handlerModules[0]=value;
    }
    arraySize++;
    string *temp_key= new string[arraySize];
    HandlerModule **temp_value= new HandlerModule*[arraySize];
    for (int i = 0; i < arraySize - 1; i++)
    {
        temp_key[i] = names[i];
        temp_value[i]=handlerModules[i];
    }
    temp_key[arraySize-1] = key;
    temp_value[arraySize-1] = value;
    delete[] names;
    delete []handlerModules;
    names=temp_key;
    handlerModules=temp_value;
    return;
}
HandlerModule* HandlerMap::find(const string & key) const {
    for( int i=0;i<arraySize;i++){
        if(key==names[i]){
            return handlerModules[i];
        }
    }
    return nullptr;
}
string HandlerMap::getNames(int index)const {
    return names[index];
}