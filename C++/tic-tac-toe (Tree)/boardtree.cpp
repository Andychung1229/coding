#include "boardtree.h"



BoardTree::BoardTree(const Board& board){
    root=new BoardNode(board);
}
BoardTree::~BoardTree(){
    delete root;
}
BoardTree* BoardTree::getSubTree(const BoardCoordinate &coords){

    if(root->subTree[coords.row][coords.col].isEmpty()){
        Board updated_board=root->board;
        if(updated_board.play(coords)){
            root->subTree[coords.row][coords.col].root=new BoardNode(updated_board);
            // cout<< root->subTree[coords.row][coords.col].root->board;
            return &root->subTree[coords.row][coords.col];

        }else{
            return &root->subTree[coords.row][coords.col];
        }

    }else {
        return &(root->subTree[coords.row][coords.col]);
    }
}
BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth){
    if(root==nullptr){
        return BoardOptimalMove();
    }
    if (depth == 0 || root->board.isFinished()){
        BoardCoordinate x (1,1);
        return BoardOptimalMove(root->board.getBoardScore(), x);
    }
    
//    if(BoardHashTable::getInstance().getHashedMove(root->board.getID(),depth).score!=ILLEGAL){
//     return BoardHashTable::getInstance().getHashedMove(root->board.getID(),depth);
//    }

    int estimatedScore=(root->board.getCurPlayer()==X)?-WIN_SCORE-1:WIN_SCORE+1;
    BoardOptimalMove bestMove;
    for(int i=0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            
            BoardCoordinate temp(i,j);
            getSubTree(temp);
            
            

            BoardOptimalMove childMove = root->subTree[i][j].getOptimalMove(depth - 1);
            
            if (childMove.score == ILLEGAL) {
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                continue;
            }
            if ((childMove.score>estimatedScore&&root->board.getCurPlayer()==X)||(childMove.score<estimatedScore&&root->board.getCurPlayer()==O)) {
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore,temp);
                }
        }
    }
    // BoardHashTable::getInstance().updateTable(root->board.getID(), depth, bestMove);
    
    return bestMove;
}
// BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth) {
//     // If the game tree is empty, return a dummy illegal move
//     if (root == nullptr) {
//         return BoardOptimalMove();
//     }

//     // If the search depth is 0 or the board state is finished, return a BoardOptimalMove object representing the score of the current board and any arbitrary move coordinate
//     if (depth == 0 || root->board.isFinished()) {
//         BoardCoordinate x(1, 1); // Any arbitrary move coordinate
//         return BoardOptimalMove(root->board.getBoardScore(), x);
//     }

//     // Initialize the estimated score to a large negative or positive value depending on the current player's turn
//     int estimatedScore = (root->board.getCurPlayer() == X) ? -WIN_SCORE - 1 : WIN_SCORE + 1;
//     BoardOptimalMove bestMove;

//     // Loop through all possible moves on the board (represented by subtrees in the game tree)
//     for (int i = 0; i < BOARD_SIZE; i++) {
//         for (int j = 0; j < BOARD_SIZE; j++) {
//             BoardCoordinate temp(i, j);
//             getSubTree(temp);

//             // Recursively call the getOptimalMove function with depth - 1 to obtain the best move for the opponent
//             BoardOptimalMove childMove = root->subTree[i][j].getOptimalMove(depth - 1);

//             // If the child move is illegal (i.e., the child node represents an invalid move or board state), skip to the next subtree
//             if (childMove.score == ILLEGAL) {
//                 continue;
//             }

//             // Update estimatedScore and bestMove if the child move has a higher score than the current estimatedScore (for X player) or a lower score (for O player)
//             if ((childMove.score > estimatedScore && root->board.getCurPlayer() == X) || (childMove.score < estimatedScore && root->board.getCurPlayer() == O)) {
//                 estimatedScore = childMove.score;
//                 bestMove = BoardOptimalMove(estimatedScore, temp);
//             }
//         }
//     }

//     // Return the bestMove object, which represents the optimal move found for the current player
//     return bestMove;
// }
BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta){
    if(root==nullptr){
        return BoardOptimalMove();
    }
    if (depth == 0 || root->board.isFinished()){
        BoardCoordinate x (1,1);
        return BoardOptimalMove(root->board.getBoardScore(), x);
    }
    int estimatedScore=(root->board.getCurPlayer()==X)?-WIN_SCORE-1:WIN_SCORE+1;
    BoardOptimalMove bestMove;

    for(int i=0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            BoardCoordinate temp(i,j);
            // if(root->subTree[i][j].isEmpty()){
            //     getSubTree(temp);
            // }
            BoardTree* subtree=getSubTree(temp);

            // BoardOptimalMove childMove = root->subTree[i][j].getOptimalMoveAlphaBeta(depth - 1,alpha,beta);
            BoardOptimalMove childMove = subtree->getOptimalMoveAlphaBeta(depth - 1,alpha,beta);
            if (childMove.score == ILLEGAL) {
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                continue;
            }
            if ((childMove.score>estimatedScore&&root->board.getCurPlayer()==X)||(childMove.score<estimatedScore&&root->board.getCurPlayer()==O)) {
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore,temp);
                }
            if (root->board.getCurPlayer()==X){
                
                if(alpha>=beta){
                    return bestMove;
                }
                if(estimatedScore>alpha){
                    alpha=childMove.score;
                }
                // if(estimatedScore>beta){
                //     return bestMove;
                // }
                // alpha=(estimatedScore>alpha)?estimatedScore:alpha;
            }else{
                
                if(beta<=alpha){
                    return bestMove;
                }
                if(estimatedScore<beta){
                    beta=childMove.score;
                }
                // if(estimatedScore<alpha){
                //     return bestMove;
                // }
                // beta=(estimatedScore<beta)?estimatedScore:beta;
            }
        }
    }
    return bestMove;
}

// BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta) {
//     if (root == nullptr) {
//         return BoardOptimalMove();
//     }
//     if (depth == 0 || root->board.isFinished()) {
//         BoardCoordinate x(1, 1);
//         return BoardOptimalMove(root->board.getBoardScore(), x);
//     }
//     int estimatedScore = (root->board.getCurPlayer() == X) ?-WIN_SCORE-1 : WIN_SCORE+1;
//     BoardOptimalMove bestMove;
//     for (int i = 0; i < BOARD_SIZE; i++) {
//         for (int j = 0; j < BOARD_SIZE; j++) {
//             BoardCoordinate temp(i, j);
//             if (root->subTree[i][j].isEmpty()) {
//                 getSubTree(temp);
//             }
//             BoardOptimalMove childMove = root->subTree[i][j].getOptimalMoveAlphaBeta(depth - 1, alpha, beta);
//             if (childMove.score == ILLEGAL) {
//                 continue;
//             }
//             if ((childMove.score > estimatedScore && root->board.getCurPlayer() == X) || 
//                 (childMove.score < estimatedScore && root->board.getCurPlayer() == O)) {
//                 estimatedScore = childMove.score;
//                 bestMove = BoardOptimalMove(estimatedScore, temp);
//             }
//             if (root->board.getCurPlayer() == X) {
//                 if (childMove.score > alpha) {
//                     alpha = childMove.score;
//                 }
//                 if (childMove.score >= beta) {
//                     return bestMove;
//                 }
//             } else {
//                 if (childMove.score < beta) {
//                     beta = childMove.score;
//                 }
//                 if (childMove.score <= alpha) {
//                     return bestMove;
//                 }
//             }
//         }
//     }
//     return bestMove;
// }