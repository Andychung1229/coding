#include <iostream>
#include "player.h"
#include"match.h"
#include"swiss.h"


Swiss::Swiss(const int numRounds, const PlayerList& list):curRound(0),numRounds(numRounds),list(list){
        
        this->list.sort();
      };

Swiss::~Swiss(){};

void Swiss::play(){
    curRound=1;
    for(int u=0;u<numRounds;curRound++,u++){
        PlayerList* temp=new PlayerList [2*curRound-1];
        int start_index=0;
        for (int i=2*curRound-2;i>=0;i--){
            for( int j=0;j<list.getNumPlayers();j++){
                if(list.getPlayer(j)->getScore()==i){
                    temp[2*curRound-2-i].addPlayer(list.getPlayer(j));
                }
            }
        }
        
        // int start_index=0;
        // for(int i=2*curRound-2;i>=0;i--){
            
        //     for(int j=0;j<list.getNumPlayers();j++){
        //         if(i==0){
                    
        //             temp[2*curRound-2-i]=*list.splice(start_index,list.getNumPlayers());
        //             cout<<" the size of the last playerlist:"<<temp[2*curRound-2-i].getNumPlayers()<<endl;
        //             break;
        //         }
        //         if(list.getPlayer(start_index+j)->getScore()<i){
                    
        //             temp[2*curRound-2-i]=*list.splice(start_index,j);
        //             start_index=j;
        //             cout<<" the size of this playerlist:"<<temp[2*curRound-2-i].getNumPlayers()<<" "<<start_index<<endl;
                    
        //             continue;
                    
        //         }
                

        // }
        for(int i=0;i<2*curRound-1;i++){
            int num_players=temp[i].getNumPlayers();
            int middle_index=num_players/2;
            int num_match=middle_index;
            //  cout<<num_players<<endl<<middle_index<<endl;
            
            if(temp[i].getNumPlayers()==0){
                continue;
            }
            // cout<<"debuggong"<<endl;
            temp[i].sort();
            
            for(int j=0;j<num_match;j++){
                
                Match match (temp[i].getPlayer(j),temp[i].getPlayer(j+middle_index));
                match.play();
            }
            if((temp[i].getNumPlayers()%2==1)&&(i==2*curRound-2)){
                temp[i].getPlayer(num_players-1)->addScore(2);
                // cout<<"debug"<<endl;
            }
            else if (temp[i].getNumPlayers()%2==1){
                // cout<<"debuged"<<endl;
                temp[i+1].addPlayer(temp[i].getPlayer(num_players-1));
            }

        }
        list.sort();
        printLeaderboard();
        delete [] temp;
    }
}
    
    // curRound=1;
    //     for(curRound<=numRounds;curRound++;){
    //         cout<<curRound<<" "<<numRounds<<endl;
    //         PlayerList* temp=new PlayerList[2*curRound-1];
    //         for( int i=0;i<list.getNumPlayers();i++){
    //             for( int j=0;j<2*curRound-1;j++){
    //                 if(list.getPlayer(i)->getScore()==j){
    //                     temp[j].addPlayer(list.getPlayer(i));
    //                     continue;
    //                 }
    //             }
                
    //         }
    //         for(int i=2*curRound-2;i>=0;i--){
    //             temp[i].sort();
    //             int num_players=temp[i].getNumPlayers();
    //             int middle=(num_players%2==0)?num_players/2-1:num_players/2;
    //             int num_match=num_players/2;
    //             for (int i=0;i<num_match;i++){
    //                 Match match(temp[i].getPlayer(i),temp[i].getPlayer(i+middle+1));
    //                 match.play();
    //             }
                
    //             if(num_match%2==0){
    //                 continue;
    //             }else if (i==0&&num_players%2==1){
    //                 temp[i].getPlayer(num_players-1)->addScore(2);
    //             }
    //             else{
    //                 temp[i-1].addPlayer(temp[i].getPlayer(num_players-1));
    //             }


    //         }
    //         list.sort();
    //         printLeaderboard();
    //         delete[]temp;

    //     }


// class Swiss {
//   private:
//       int curRound;
//       int numRounds;
//       PlayerList list;

//   public:
//       // TASK 4: Implement the conversion constructor
//       Swiss(const int numRounds, const PlayerList& list):curRound(0),numRounds(numRounds),list(list){
//         this->list.sort();
//         printLeaderboard();
//       };

//       // TASK 5: Implement the function to conduct the Swiss tournament
//       void play(){
//         for(curRound<=numRounds;++curRound;){
//             PlayerList* temp=new PlayerList[2*curRound-1];
//             for( int i=0;i<list.getNumPlayers();i++){
//                 for( int j=0;j<2*curRound-1;j++){
//                     if(list.getPlayer(i)->getScore()==j){
//                         temp[j].addPlayer(list.getPlayer(i));
//                         continue;
//                     }
//                 }
//             }
//             for(int i=2*curRound-2;i>=0;i--){
//                 temp[i].sort();
//                 int num_players=temp[i].getNumPlayers();
//                 int middle=(num_players%2==0)?num_players/2-1:num_players/2;
//                 int num_match=num_players/2;
//                 for (int i=0;i<num_match;i++){
//                     Match match(temp[i].getPlayer(i),temp[i].getPlayer(i+middle));
//                     match.play();
//                 }
//                 if(num_match%2==0){
//                     continue;
//                 }else if (i==0&&num_players%2==1){
//                     temp[i].getPlayer(num_players-1)->addScore(2);
//                 }
//                 else{
//                     temp[i-1].addPlayer(temp[i].getPlayer(num_players-1));
//                 }


//             }
//             list.sort();
//             printLeaderboard();
//             delete[]temp;

//         }

        
//       };

//       // The leaderboard print function is given
//       void printLeaderboard() const {
//           std::cout << "===================================" << std::endl;
//           std::cout << "ROUND " << curRound << "/" << numRounds << " ENDED." << std::endl;
//           for (int i=0; i<list.getNumPlayers(); ++i) {
//               list.getPlayer(i)->print();
//               std::cout << ": " << list.getPlayer(i)->getScore() << std::endl;
//           }
//           std::cout << "===================================" << std::endl;
//       }
// };