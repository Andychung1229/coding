#include"board.h"

Board::Board(const int score[][BOARD_SIZE]):curPlayer(X),id(0){
    for(int i =0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            this->score[i][j]=score[i][j];
            cells[i][j]=EMPTY;
        }
    }
}
bool Board::isFull() const{
    
    for(int i =0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            if(cells[i][j]==EMPTY){
                return false;
            }
        }
    }
    return true;
}
// bool Board::isFinished() const{
//     if(isFull()){
        
//         return true;
//     }
    
//     for (int row =0;row<BOARD_SIZE;row++){
        
//         if(cells[row][0]!=EMPTY){
//             bool flag_row=true;
//             for(int col=0;col<BOARD_SIZE-1;col++){
//                 if(cells[row][col]!=cells[row][col+1]){
//                     flag_row=false;
//                 }
//             }
//             if(flag_row==true){
//                 return true;
//             }
//         }
        
//     }
    
//     for (int col =0;col<BOARD_SIZE;col++){
        
//         if(cells[0][col]!=EMPTY){
//             bool flag_col=true;
//             for(int row=0;row<BOARD_SIZE-1;row++){
//                 if(cells[row][col]!=cells[row+1][col]){
//                     flag_col=false;
//                 }
//             }
//             if(flag_col==true){
//                 return true;
//             }
//         }
//     }
//     bool flag_dia_left=true;
//     for (int col =0;col<BOARD_SIZE-1;col++){
        
//         if(cells[0][0]!=EMPTY||cells[col][col]!=cells[col+1][col+1]){
            
            
//                 flag_dia_left=false;
            
            
//         }

//     }
//     if(flag_dia_left==true){
//                 return true;
//             }
    
    
//     for (int col =0;col<BOARD_SIZE-1;col++){
//         bool flag_dia_right=true;
//         if(cells[BOARD_SIZE-1][BOARD_SIZE-1]!=EMPTY||cells[BOARD_SIZE-1-col][BOARD_SIZE-1-col]!=cells[BOARD_SIZE-2-col][BOARD_SIZE-2-col]){
            
            
//                 flag_dia_right=false;
//         }
//         if(flag_dia_right==true){
//                 return true;
//         }
            
//         }
    
    
//     return false;
// }

bool Board::isFinished() const{
    
    if (isFull()) {
        return true;
    }

    for (int row = 0; row < BOARD_SIZE; row++) {
        bool flag_row = true;
        for (int col = 1; col < BOARD_SIZE; col++) {
            if (cells[row][col] != cells[row][0] || cells[row][col] == EMPTY) {
                flag_row = false;
                break;
            }
        }
        if (flag_row) {
            return true;
        }
    }

    
    for (int col = 0; col < BOARD_SIZE; col++) {
        bool flag_col = true;
        for (int row = 1; row < BOARD_SIZE; row++) {
            if (cells[row][col] != cells[0][col] || cells[row][col] == EMPTY) {
                flag_col = false;
                break;
            }
        }
        if (flag_col) {
            return true;
        }
    }

    
    bool flag_dia_left = true;
    for (int i = 1; i < BOARD_SIZE; i++) {
        if (cells[i][i] != cells[0][0] || cells[i][i] == EMPTY) {
            flag_dia_left = false;
            break;
        }
    }
    if (flag_dia_left) {
        return true;
    }

    
    bool flag_dia_right = true;
    for (int i = 1; i < BOARD_SIZE; i++) {
        if (cells[i][BOARD_SIZE-1-i] != cells[0][BOARD_SIZE-1] || cells[i][BOARD_SIZE-1-i] == EMPTY) {
            flag_dia_right = false;
            break;
        }
    }
    if (flag_dia_right) {
        return true;
    }

    
    return false;
}
int Board::getBoardScore() const{
   
    
        bool flag_row_outside = false;
        for (int row = 0; row < BOARD_SIZE; row++) {
            bool flag_row=true;
            for (int col = 1; col < BOARD_SIZE; col++) {
                if (cells[row][col] != cells[row][0] || cells[row][col] == EMPTY) {
                    flag_row = false;
                    break;
                }
            }
            if(flag_row){
                flag_row_outside=true;
                break;
            }
        }
        
        bool flag_col_outside =false;
        for (int col = 0; col < BOARD_SIZE; col++) {
            bool flag_col = true;
            for (int row = 1; row < BOARD_SIZE; row++) {
                
                if (cells[row][col] != cells[0][col] || cells[row][col] == EMPTY) {
                    flag_col = false;
                    break;
                }
                
            }
            if(flag_col){
                    flag_col_outside=true;
                    break;
                }
        
        }
    bool flag_dia_left = true;
    for (int i = 1; i < BOARD_SIZE; i++) {
        if (cells[i][i] != cells[0][0] || cells[i][i] == EMPTY) {
            flag_dia_left = false;
            break;
        }
    }
   

    
    bool flag_dia_right = true;
    for (int i = 1; i < BOARD_SIZE; i++) {
        if (cells[i][BOARD_SIZE-1-i] != cells[0][BOARD_SIZE-1] || cells[i][BOARD_SIZE-1-i] == EMPTY) {
            flag_dia_right = false;
            break;
        }
    }
    bool flag=false;
    if (flag_dia_right||flag_col_outside||flag_dia_left||flag_row_outside) {
        flag=true;
    }




    int output=0;
    if(flag==true){
        if(getCurPlayer()==O){
            
                return WIN_SCORE;
            
        }
        if(getCurPlayer()==X){
            
                return -WIN_SCORE;
            
        }
    }else if(flag==false){
        
        
        for(int i=0;i<BOARD_SIZE;i++){//check vertical
            for(int j=0;j<BOARD_SIZE;j++){
                
                if(cells[i][j]==X){
                    
                    output+=score[i][j]*getCellWeight(X);
                }
                if(cells[i][j]==O){
                    
                    output-=score[i][j]*getCellWeight(O);
                }
                if(cells[i][j]==EMPTY){
                    output+=score[i][j]*0;
                }
            }
        }
        
    }
    return output;
    
}


bool Board::play(const BoardCoordinate& coords){
    if(coords.isValid()==false){
        return false;
    }
    if(cells[coords.row][coords.col]!=EMPTY){
        return false;
    }
    cells[coords.row][coords.col]=getCurPlayer();
    int value=(getCurPlayer()==X)?1:2;
    
    id+=value*(pow(3,(coords.row*BOARD_SIZE+coords.col)));
    if(curPlayer==X){
        curPlayer=O;
    }else{
        curPlayer=X;
    }
    return true;
}
