// THIS PROJECT IS DONE BY TEJAS SHARMA ONLY. 
// COPYRIGHTED MATERIAL. 
// ATTEMPT TO SHARE, STEAL, SUBMIT OR PUBLISH WITHOUT SAID OWNER'S PERMISSION 
// WILL RESULT IN STRICT ACTION BEING TAKEN.

#include <iostream>
#include <cstdlib>
using namespace std;
// NOTE: For each tile, 0 = no color coin. -1 = white on top. 1 = black on top.
// Board array rules: 2-D array of length 8*8. 
// For a tile in row i and column j, 8*i + j = index of corresponding element in array. 
// i, j start from 0 to 7 in program, 1 to 8 in input

void print (int** arr) {
    cout << endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            cout << "+--------";
        } 
        cout << "+" << endl;
        // At the top of EACH line, we do what? print + ----- to form a grid.
        for (int j = 0; j < 8; j++) {
            cout << "|";
            switch (arr [j] [i]) {
                case -1: cout << " /^^^^\\ "; break;
                case 1: cout << " /@@@@\\ "; break;
                default: cout << "        "; break;
            } 
            // Same notation. 1 means black square. Filled across three lines. 
            //-1 means white square (or blank). ALso filled across three squares. 
            // 0 means empty space.
        } 
        cout << "|" << endl;
        for (int j = 0; j < 8; j++) {
            cout << "|";
            switch (arr [j] [i]) {
                case -1: cout << " [    ] "; break;
                case 1: cout << " @@@@@@ "; break;
                default: cout << "        "; break;
            }
        } 
        cout << "|" << endl;
        for (int j = 0; j < 8; j++) {
            cout << "|";
            switch (arr [j] [i]) {
                case -1: cout << " \\____/ "; break;
                case 1: cout << " \\@@@@/ "; break;
                default: cout << "        "; break;
            }
        } 
        cout << "|" << endl; 
        // At the end of each block, each line, there is a vertical hyphen that forms the grid.
    } 
    for (int j = 0; j < 8; j++) {
        cout << "+--------";
    } 
    cout << "+" << endl; 
    // The bottom line.
} 
// NOTE: This program does not cout the square numbers. 
//You are expected to know that (x, y) means x right and y top from the left corner 
// which is (1, 1). Like first quadrant.
// Also note the order in which we printed. Top row inside memory would be x = 1 or i = 0.
// But here x is left column. So we traverse arr[j][i] instead. 
// For i too, i = 0 on bottom so reverse order.

// OK. We know that for white or black the given move is legal. We know 
// how many squares to flip on each side as well and that they are of opposite color. We flip it.
void flip (int** board, int x, int y, int* moves) {
    for (int i = 1; i <= moves[0]; i++) board[x + i][y] *= -1;
    for (int i = 1; i <= moves[1]; i++) board[x - i][y] *= -1;
    for (int i = 1; i <= moves[2]; i++) board[x][y + i] *= -1;
    for (int i = 1; i <= moves[3]; i++) board[x][y - i] *= -1;
    for (int i = 1; i <= moves[4]; i++) board[x + i][y + i] *= -1;
    for (int i = 1; i <= moves[5]; i++) board[x + i][y - i] *= -1;
    for (int i = 1; i <= moves[6]; i++) board[x - i][y + i] *= -1;
    for (int i = 1; i <= moves[7]; i++) board[x - i][y - i] *= -1;
    return;
} 
// Note: i did not initialise color as parameters. 
// This function assumes that all parameters are correct before. 
// They will indeed be correct if you look at the next function carefully.

// THE MAIN THING goes on here.
int playerMove (int** board, int x, int y, int person, int isPlayer, int makeMove) {
    int* moves = new int [8]; 
    // New array just to store 
    // 'In each direction from given position of movement, if there exists a like color square 
    // in that direction and all inbetweens unlike (no likes or zeroes) then we invert 
    // that many squares.' Like (you enter white then white/-1 is like, black/+1 is unlike)

    for (int i = 0; i < 8; i++) moves[i] = 0; // Initialising. 0 means no changing.
    if (x < 1 || x > 8 || y < 1 || y > 8) {
        if (isPlayer) cout << "Out of board square. Enter valid move." << endl; 
        // isPlayer.
        // Here, if i am validating or computer playing 
        // then i don't want unnessary error messages.
        delete [] moves;
        return 0; 
        // Exception handling.
    } 
    if (board[x - 1][y - 1] != 0) {
        delete [] moves;
        if (isPlayer) cout << "Piece exists on chosen square. Enter valid move. " << endl;
        return 0; 
        // Exception: We can't superimpose an existing square.
    } 
    x -= 1; y -= 1; 

    // We enter coordinates in 1 to 8 but internal memory uses 0 to 7. 
    // Disparity is handled this way.
    int count = 0; 
    // Number of squares to be inverted. Move is not possible if number is zero.
    int i = 1; 
    // To initialise FOR EACH direction, number of squares (i - 1) to be tilted.

    while (true) { 
        // Check right squares - that's direction 0, moves[0]
        if (x + i == 8 || board[x + i][y] == 0) break;
        if (board[x + i][y] == person) {
            count += (i - 1);
            moves[0] = (i - 1);
            break;
        } 
        // If you know the game this is not very difficult to think of. 
        // Continuous unlike squares counted --> 1 like square.
        if (board[x + i][y] == -person) i++;
    } 
    i = 1; 
    // Initialised for next direction.
    while (true) { 
        // Check left squares - direction 1
        if (x - i == -1 || board[x - i][y] == 0) break;
        if (board[x - i][y] == person) {
            count += (i - 1);
            moves[1] = (i - 1);
            break;
        } 
        if (board[x - i][y] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check top squares - direction 2
        if (y + i == 8 || board[x][y + i] == 0) break;
        if (board[x][y + i] == person) {
            count += (i - 1);
            moves[2] = (i - 1);
            break;
        } 
        if (board[x][y + i] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check bottom squares - direction 3
        if (y - i == -1 || board[x][y - i] == 0) break;
        if (board[x][y - i] == person) {
            count += (i - 1);
            moves[3] = (i - 1);
            break;
        } 
        if (board[x][y - i] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check right top squares - direction 4
        if (x + i == 8 || y + i == 8 || board[x + i][y + i] == 0) break;
        if (board[x + i][y + i] == person) {
            count += (i - 1);
            moves[4] = (i - 1);
            break;
        } 
        if (board[x + i][y + i] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check right bottom squares - direction 5
        if (x + i == 8 || y - i == -1 || board[x + i][y - i] == 0) break;
        if (board[x + i][y - i] == person) {
            count += (i - 1);
            moves[5] = (i - 1);
            break;
        } 
        if (board[x + i][y - i] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check left top squares - direction 6
        if (x - i == -1 || y + i == 8 || board[x - i][y + i] == 0) break;
        if (board[x - i][y + i] == person) {
            count += (i - 1);
            moves[6] = (i - 1);
            break;
        } 
        if (board[x - i][y + i] == -person) i++;
    } 
    i = 1;
    while (true) { 
        // Check left bottom squares - direction 7
        if (x - i == -1 || y - i == -1 || board[x - i][y - i] == 0) break;
        if (board[x - i][y - i] == person) {
            count += (i - 1);
            moves[7] = (i - 1);
            break;
        } 
        if (board[x - i][y - i] == -person) i++;
    } 
    i = 1;
    // OK. NOW we know how many to move in each direction and count = total. 
    // Note that i gave (i - 1) for each direction that is number of squares moved.

    if (count == 0) {
        if (isPlayer) cout << "No piece to flip to your color. Enter valid move. " << endl;
        delete [] moves;
        return 0; 
        // Again, rules.
    }
    if (makeMove) { 
        // Sometimes i just want to test if this is a valid move or not. 
        // Or get the most optimal move (max. no. of squares) if the computer is playing.
        board[x][y] = person; 
        // NOW we set the square we place the coin on from 0 to (+- 1)
        flip (board, x, y, moves); 
        // The flipping part of the now valid move.
    }
    delete [] moves;
    return count; 
    // To see which is the most optimal.
}

// Mainly to check validity of moves. 
// I check EVERY square and find if any move is valid. 
// If not then the previous player repeats turn. 
// If both can't make a move (or filled board) then game terminates.
int isMovable (int** board, int person, int isPlayer, int diff, int diff0, char* X) { 
    // Difficulty level = order of the number of steps the computer thinks ahead.
    int max = 0, xin = 0, yin = 0;
    int maxin = 0; 
    // Observe: I store all moves of equal and maximum efficiency possible in 'maxarr' array. 
    int* maxarr = new int [28];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
        {
            int point = playerMove (board, i + 1, j + 1, person, 0, 0); 
            // Match function input format.
            if (point > 0 && i % 7 == 0) point += 2; 
            // Prefer corners > edges > normal squares. Smart computer.
            if (point > 0 && j % 7 == 0) point += 2;

            if (point > 0 && diff > 1) {
                int** board1 = new int* [8]; 
                // Duplicate board for checking future moves (smart algorithm)

                for (int i = 0; i < 8; i++) 
                    board1[i] = new int [8];
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        board1[i][j] = board[i][j];
                
                point -= playerMove (board1, i + 1, j + 1, person, 0, 0);
                point += playerMove (board1, i + 1, j + 1, person, 0, 1); 
                // Just replace point with itself but execute the point ON THE NEW BOARD.

                point -= isMovable (board1, -person, 0, diff-1, diff0, X); 
                // OK. Now Computer moves for you/player what you will think best of.
                point += isMovable (board1, person, 0, diff-1, diff0, X) + 1; 
                // According to that the computer makes its next move... 
                // but does not display anything (disp = 0) and 
                // computes the most efficient sum of moves...
                for (int i = 0; i < 8; i++) delete [] board1[i];
                delete [] board1;
            }
            // Difficulty 0 means any random legal move done by computer. 
            // Difficulty 1 is greedy.
            if ((diff == 0 && point > 0) || (point == max && point > 0))
                maxarr[maxin++] = i*8 + j;
            // Now, array has one more element with equally efficient move.

            if ((point > max && diff > 0) || (point > 0 && max == 0)) {
                max = point; 
                // OK. max > 0 means there exists a valid move. 
                // I find the one with MAXIMUM color changes and do this. 
                // (Note: This is a smart but GREEDY computer, 
                // not a Big picture planning computer)
                maxin = 1; 
                // New maximum declared; Only one space in array. 
                // Previous maximas after maxin are ignored.
                maxarr[0] = i*8 + j;
            }
        }
    } srand (time(0)); 
    // random seed initialised this way.
    if (max > 0) { 
        // If computer is playing (isPlayer is zero) then inbuilt function to make the move.
        int ptin = maxarr[(rand() % maxin)]; 
        // Random move among most efficient ones.
        delete [] maxarr;
        xin = ptin / 8; yin = ptin % 8;

        if (!(isPlayer)) {
            if (diff == diff0) { 
                cout << "Computer's turn. Enter to Continue: "; 
                cin.getline(X, 200);
            }
            // a is a useless variable but this is the easiest way i could think of

            if (diff == diff0) { 
                cout << "Computer made a move at (" << xin + 1;
                cout << ", " << yin + 1 << ")." << endl;
            }
            playerMove (board, xin + 1, yin + 1, person, 0, 1); 
            // Again, the input format required is 1 to 8 
            // not the 0 to 7 used in processing. 1 to 8 is user input bases, similar.
            if (diff == diff0) print (board); 
            // Only the original board is printed, only once.
        } 
        return max;
    } 
    else if (diff > 1) { 
        delete [] maxarr;
        return isMovable (board, person, 0, diff - 1, diff0 - 1, X);
    }
    delete [] maxarr;
    return 0;
}


int results (int** board) { 
    // Extra. Declares the winner of the match.
    int p1 = 0, p2 = 0; 
    // You know. Who has the maximum squares of their color (coins duh) is the winner.

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == -1) p2 += 1;
            if (board[i][j] == 1) p1 += 1;
        }
    } 
    if (p1 == p2) return 0;
    else if (p1 > p2) return 1;
    else return -1;
} 
// NOTE: this just declares which COLOR won. not which PLAYER.


int main() {
    int** board = new int* [8];
    for (int i = 0; i < 8; i++) {
        board[i] = new int [8];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == 3 && j == 3) || (i == 4 && j == 4)) board[i][j] = 1;
            else if ((i == 3 && j == 4) || (i == 4 && j == 3)) board[i][j] = -1;
            else board[i][j] = 0;
        }
    }
    char* X = new char [201];
    int comp = 0, color = 0, diff = 1;
    cout << endl << "OTHELLO GAME" << endl;
    cout << "Gameplay options: " << endl;
    cout << "    1: Two Player Game." << endl;
    cout << "    0: You vs Computer Game." << endl;
    cout << "Enter choice: " ; 
    cin.getline(X, 200);
    if (X[0] == '0') comp = 0;
    else if (X[0] == '1') comp = 1;
    else
        throw invalid_argument("\nInvalid Choice!");
    // if (comp) means if (computer is not playing but its p1 vs p2) and not 
    // if (computer is playing) Don't confuse here.

    if (comp == 0) {
        cout << endl << "Difficulty Levels: " << endl;
        cout << "    0. Easy" << endl;
        cout << "    1. Normal" << endl;
        cout << "    2. Hard" << endl;
        cout << "    3. Extreme" << endl;
        cout << "Enter your choice: ";
        cin.getline(X, 200);
        diff = X[0] - 48;
        cout << endl;
		if (diff < 0 || diff > 3) 
            throw invalid_argument("\nInvalid Difficulty!");
        cout << "Enter your color of choice (Black starts first) "; 
        cout << "[Enter 1 for black, -1 for white]: ";
    } 
    else {
        cout << "Enter color of player 1 (Black starts first) ";
        cout << "[Enter 1 for black, -1 for white]: ";
    } 
    cin.getline(X, 200);
    if (X[0] == '-') color = 48 - X[1];
    else color = X[0] - 48;
	if (color*color != 1) 
        throw invalid_argument("\nInvalid Color!");
    cout << endl << "Squares (x, y) are numbered from (1, 1) to (8, 8). ";
    cout << "(1, 1) being the bottom left and (8, 8) top right" << endl; 
    cout << "Note that x --> left (1) to right (8). ";
    cout << "y --> bottom (1) to right (8)." << endl;

    int player = color; 
    // Yeah. If player is 1 (not +color, but 1) it means you or Player 1 
    // and -1 it means the computer or Player 2. 
    // Player*color ALWAYS returns the color of square which current player is playing.
    print (board);

    while (true) { 
        // Infinite loop, terminates when gameplay ends.
        cout << endl; cin.sync();
        if (player == -1 && comp == 0) { 
            // It means computer's turn.
            if (isMovable (board, player*color, 0, diff, diff, X)) { 
                // Note the parameters called for each function.
                player *= -1; 
                // Your turn next.
            } else {
                cout << "No valid move for computer. It's your turn now!" << endl;
                player *= -1;
            }
        } 
        else if (player == -1) { 
            // Player 2 basically.
            if (isMovable (board, player*color, 1, 1, 1, X)) {
                cout << "Player 2: Enter move ";
                cout << "(place your color coin on x, y coordinates)." << endl;
                cout << "Enter space separated integers x, y starting 1 to 8: ";
                cin.getline(X, 200);
                int x = X[0] - 48;
                int y = X[2] - 48;

                int chk = playerMove (board, x, y, player*color, 1, 1);
                if (chk) {
                    print (board); 
                    // After EACH move i print the board. 
                    // print board for computer move is already taken care of.
                    player *= -1; 
                    // Player 1's turn.
                    continue;
                } 
                else continue; 
                //Repeat move, player 2 (error message given).
            } 
            else { 
                // So now no valid move for player 2
                if (!(isMovable (board, -player*color, 1, 1, 1, X))) break; 
                // No valid move for player 1 as well. 
                // Either all squares filled or a stalemate scenario. 
                // Time to end things!
                cout << "No valid move for Player 2. Player 1, play again!" << endl;
                player *= -1;
            }
        } 
        else {
            if (isMovable (board, player*color, 1, 1, 1, X)) {
                if (comp) {
                    cout << "Player 1: Enter move ";
                    cout << "(place your color coin on x, y coordinates)." << endl;
                }
                else {
                    cout << "Enter your move ";
                    cout << "(place your color coin on x, y coordinates)." << endl;
                }
                cout << "Enter space separated integers x, y starting 1 to 8: ";
                cin.getline(X, 200);
                int x = X[0] - 48;
                int y = X[2] - 48;

                int chk = playerMove (board, x, y, player*color, 1, 1);
                if (chk) {
                    print (board);
                    player *= -1; 
                    // Player 2's turn
                    continue;
                } 
                else 
                    continue; 
                // Repeat move, Player 1 (error message given)
            } 
            else {
                if (!(isMovable (board, -player*color, comp, diff, 1, X))) break; 
                // Both players no valid move. End things here.
                if (comp) cout << "No valid move for Player 1. Player 2, play again!" << endl; 
                // Separate messages for you vs comp and p1 vs p2.
                else cout << "You have no valid moves. Computer will play again!" << endl; 
                // This is a different if.
                player *= -1;
            }
        }
    } 
    cout << endl << "No possible moves. Game has ended." << endl; 
    delete [] X;
    // Once break executed.

    int win = results (board); 
    // Winning color.
    for (int i = 0; i < 8; i++) delete [] board[i];
    delete [] board;
    if (win == 0) {
        cout << "THE RESULT OF THIS GAME IS: A TIE !!" << endl << endl;
    } 
    else if (win == color) { 
        // That color is player 1 or you.
        if (comp) cout << "THE WINNER IS: PLAYER 1 !!" << endl << endl;
        else cout << "YOU ARE THE WINNER !!" << endl << endl;
    } 
    else { 
        // Otherwise.
        if (comp) cout << "THE WINNER IS: PLAYER 2 !!" << endl << endl;
        else cout << "THE WINNER IS: THE COMPUTER !!" << endl << endl;
    } 
} 
// THE END.                                                                                                                                                                                                         22B0909
