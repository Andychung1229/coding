#include <iostream>
#include <cstring>
#include "player.h"

Player:: Player(const char* const name, const int elo){
        this->elo=elo;
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        score=0;
      };

Player::~Player(){delete[]name;};

PlayerList::PlayerList(){
        numPlayers=0;
        players=nullptr;
      };


PlayerList::PlayerList(const PlayerList& list){
        numPlayers=list.getNumPlayers();
        players=new Player*[numPlayers];
        for(int i=0;i<numPlayers;i++){
            players[i]=list.getPlayer(i);
        }
      };

PlayerList::~PlayerList(){
        delete [] players;
      };
void PlayerList::addPlayer(Player* const player){
        numPlayers++;
        Player**temp=new Player*[numPlayers];
        for(int i=0;i<numPlayers-1;i++){
            temp[i]=players[i];
        }
        temp[numPlayers-1]=player;
        delete[]players;
        players=temp;
      };
void PlayerList:: sort(){
  

        bool flag=0;
        int num=numPlayers-1;
        do{
            
            flag=0;
            for(int i=0;i<num;i++){
                
                if(players[i]->getScore()<players[i+1]->getScore()){
                  
                    Player* temp=players[i];
                    players[i]=players[i+1];
                    players[i+1]=temp;
                    flag=1;
                }else if ((players[i]->getScore()==players[i+1]->getScore())
                &&(players[i]->getELO()<players[i+1]->getELO())){
                  
                  Player* temp=players[i];
                    players[i]=players[i+1];
                    players[i+1]=temp;
                    flag=1;
                }
                
            }
            num--;
        }while(flag==1);
      };
PlayerList* PlayerList::splice(const int startIndex, const int endIndex) const{
        int num=endIndex-startIndex;
        PlayerList* temp=new PlayerList;
        if(startIndex<0||endIndex>num||startIndex>=endIndex){
          return temp;
        }
        
        for(int i=0;i<num;i++){
          temp->addPlayer(this->getPlayer(startIndex+i));
        }
        return temp;

      };
// class PlayerList {
//   private:
//       int numPlayers;
//       Player** players;

//   public:
//       // TASK 2: Implement the default constructor, conversion constructor and destructor
//       PlayerList(){
//         numPlayers=0;
//         players=nullptr;
//       };
//       PlayerList(const PlayerList& list){
//         numPlayers=list.getNumPlayers();
//         players=new Player*[numPlayers];
//         for(int i=0;i<numPlayers;i++){
//             players[i]=list.getPlayer(i);
//         }
//       };
//       ~PlayerList(){
//         delete [] players;
//       };

//       // The following accessor functions are given
//       int getNumPlayers() const { return numPlayers; }
//       Player* getPlayer(const int index) const { return players[index]; }

//       // TASK 3: Implement PlayerList insert, sort and splice
//       void addPlayer(Player* const player){
//         numPlayers++;
//         Player**temp=new Player*[numPlayers];
//         for(int i=0;i<numPlayers-1;i++){
//             temp[i]=players[i];
//         }
//         temp[numPlayers-1]=player;
//         delete[]players;
//         players=temp;
//       };
//       void sort(){
//         bool flag=0;
//         int num=numPlayers;
//         do{
//             flag=0;
//             for(int i=0;i<num;i++){
//                 if(players[i]->getScore()<players[i+1]->getScore()){
//                     Player* temp=players[i+1];
//                     players[i]=players[i+1];
//                     players[i+1]=temp;
//                     flag=1;
//                 }else if ((players[i]->getELO()==players[i+1]->getELO())
//                 &&(players[i]->getELO()<players[i+1]->getELO())){
//                   Player* temp=players[i+1];
//                     players[i]=players[i+1];
//                     players[i+1]=temp;
//                     flag=1;
//                 }
                
//             }
//             num--;
//         }while(flag=0);
//       };
//       PlayerList* splice(const int startIndex, const int endIndex) const{
//         int num=endIndex-startIndex;
//         PlayerList* temp=new PlayerList;
//         if(startIndex<0||endIndex>num||startIndex>=endIndex){
//           return temp;
//         }
        
//         for(int i=0;i<num;i++){
//           temp->addPlayer(this->getPlayer(startIndex+i));
//         }
//         return temp;

//       };
// };