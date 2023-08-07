#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Chess
{
	public:
		
	// Chess constructor
	Chess()
	{
		setupBoard();
	}

    // Chess destructor
    ~Chess() 
    {
    	 // Deallocate memory for the chessboard rows
        for (int i = 0; i < 8; i++) 
        {
            delete[] board[i];
        }
        delete[] board;	// Deallocate memory for the chessboard itself
    }

	// Initialize the chessboard with the initial piece positions
    void setupBoard()
	{
    
    board = new string*[8];
    for (int i = 0; i < 8; i++) 
    {
        board[i] = new string[8];
    }

   // Set up the initial positions of the black pieces
    board[0][0] = "ks";	// Black king (k) starts at position a1
    board[0][1] = "as";	// Black queen (a) starts at position b1
    board[0][2] = "fs";	// Black bishop (f) starts at position c1
    board[0][3] = "vs";	// Black knight (v) starts at position d1
    board[0][4] = "ss";	// Black rook (s) starts at position e1
    board[0][5] = "fs";	// Black bishop (f) starts at position f1
    board[0][6] = "as";	// Black queen (a) starts at position g1
    board[0][7] = "ks";	// Black king (k) starts at position h1

	// Set up the initial positions of the black and white pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = "ps";
        board[6][i] = "pb";
    }
	// Set empty spaces for the middle rows of the chessboard
    for (int i = 2; i < 8-2; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = "--";
        }
    }

	// Set up the initial positions of the white pieces
    board[7][0] = "kb";	// White king (k) starts at position a8
    board[7][1] = "ab";	// White queen (a) starts at position b8
    board[7][2] = "fb";	// White bishop (f) starts at position c8
    board[7][3] = "vb";	// White knight (v) starts at position d8
    board[7][4] = "sb";	// White rook (s) starts at position e8
    board[7][5] = "fb";	// White bishop (f) starts at position f8
    board[7][6] = "ab";	// White queen (a) starts at position g8
    board[7][7] = "kb";	// White king (k) starts at position h8
} 

	// Get the piece at the specified position on the chessboard
    string getPiece(int row, int col)
    {
        return board[row][col];	 // Return the piece at the given row and column
    }

	// Set the piece at the specified position on the chessboard
    void setPiece(int row, int col, string piece)
    {
        board[row][col] = piece;	// Set the piece at the given row and column to the specified piece	
    }
    
    private:
	// Chess board
    // Define the board variable as a double-dimensional dynamically generated string array.
    string **board;
};


// Define a new class 'ChessboardAndPiece' that inherits from the 'Chess' class.
class ChessboardAndPiece : public Chess
{

public:

    // Constructor
    // Read the file to set the view of chess board.
    ChessboardAndPiece(string fileName)
    {
        ifstream inputFile(fileName.c_str());	// Open the input file using the provided 'fileName'.
        string line;
        int i = 0;
    	// Loop to read 8 lines from the input file.
        while (i < 8)
        {
            int j = 0;

            // Read each line from the text file.
            getline(inputFile, line);
			  
			// Break the line to read chess pieces using a stringstream.
            stringstream p(line);

            // Store each piece in 'pieceName'.
            string pieceName;

            // Set the chess piece at the corresponding position on the chess board.
            while (p >> pieceName && j < 8)
            {
                setPiece(i, j, pieceName);	// Call the inherited 'setPiece()' to set the piece on the chess board.
                j++;
            }
            i++;
        }
        inputFile.close();     // Close the input file after reading.
    }

	// An array that holds the names of the chess pieces.
    string pieceNames[6] = {"p", "a", "f", "k", "v", "s"};

	// Arrays to count the number of white and black pieces of each type.
    int whitePieces[6] = {0};
    int blackPieces[6] = {0};
    
    // Arrays to track the number of times each white and black piece is under attack.
    int whiteUnderAttack[6] = {0};
    int blackUnderAttack[6] = {0};

	// A 2D array to track whether each square on the chessboard is threatened by any piece.
    bool threatened[8][8] = {};
    
	// Function prototypes for functions to determine which pieces are attacking a square.
    void attackedbyPawn();
    void attackedbyKnight();
    void attackedbyQueen();

    // Function prototypes for functions to count the number of pieces of each type.
    void countPieces(string color, string pieceNames[]);				
    void calculate();
    
    private:
    	
    // An array to store the scores associated with each chess piece type.
    // Piyon (Pawn) p=1, at (Knight) a=3, fil (Bishop) f=3, kale (Rook) k=5, vezir (Queen) v=9, sah (King) s=100.
    float pieceScores[6] = {1,3,3,5,9,100};
   
    // New scoring for the pieces that are under attack.
	float pieceUnderAttack[6] = {-0.5, -1.5, -1.5, -2.5, -4.5, -50};
    float whiteScore = 0;
    float blackScore = 0;

};

// Determine the squares that are attacked by pawns
void ChessboardAndPiece :: attackedbyPawn()
{
    for (int i = 0; i < 8; i++)
    {   
        for (int j = 0; j < 8; j++)
        {   
           // Define possible moves for white and black pawns
            int whitePawnMoves[2][2] = {{-1,-1}, {-1,1}};
            int blackPawnMoves[2][2] = {{1,-1}, {1,1}};
            string whitePiece = getPiece(i,j);	// Get the piece at the current position (i, j) on the chessboard
            // Check if it's a white pawn and it is not under threat
            if (whitePiece.find('b') != string::npos && threatened[i][j] == false) 
            {
                // Initialize a flag to check if the pawn is under attack
                bool isUnderAttack = false;

                // Check possible attacking positions for the white pawn
                for (int k = 0; k < 2; k++)
                {
                    int x = i + whitePawnMoves[k][0];
                    int y = j + whitePawnMoves[k][1];
                     
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is a black pawn at the attacking position
                        if (getPiece(x, y) == "ps")
                        {   
                        // Check if the current white piece type is under attack by the pawn
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {  
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                // If the white piece is under attack, update the threatened status and count
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (whitePiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            whiteUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
            // Get the piece at the current position (i, j) on the chessboard
            string blackPiece = getPiece(i,j);
            // Note that "sb" refers to white king, and 's' in "sb" will confuse the program since 's' refers to color black.
            if (blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false) 
            {
                // Flag to keep track of whether this piece is under attack
                bool isUnderAttack = false;

                // Check all 2 possibilities of pawn moves.
                for (int k = 0; k < 2; k++)
                {
                    int x = i + blackPawnMoves[k][0];
                    int y = j + blackPawnMoves[k][1];
                    
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is any rival (white) pawn that can be a threat.
                        if (getPiece(x, y) == "pb")
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {  
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                // If the piece is under attack, increase the count of the corresponding piece type in the array.
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (blackPiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            blackUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
            
        }
    }
}

void ChessboardAndPiece :: attackedbyKnight()
{
    for (int i = 0; i < 8; i++)
    {   for (int j = 0; j < 8; j++)
        {   
            // If there is a knight in the position of the piece that can move to that position, the piece is under threat.
            // Define knight moves.
            int knightMoves[8][2] = {{-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}};

            string whitePiece = getPiece(i,j);
            if (whitePiece.find('b') != string::npos && threatened[i][j] == false) 
            {
                bool isUnderAttack = false;
                
                // Check all 8 possibilities of knight moves.
                for (int k = 0; k < 8; k++)
                {
                    int x = i + knightMoves[k][0];
                    int y = j + knightMoves[k][1];
                    
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is any rival (black) knight that can be a threat.
                        if (getPiece(x, y) == "as") 
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (whitePiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            whiteUnderAttack[k]++;
                            break;
                        }
                    }
                }                
            }

            string blackPiece = getPiece(i,j);
            if (blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false) 
            {
                bool isUnderAttack = false;
                
                for (int k = 0; k < 8; k++) 
                {
                    int x = i + knightMoves[k][0];
                    int y = j + knightMoves[k][1];
                    
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is any rival (white) knight that can be a threat.
                        if (getPiece(x, y) == "ab") 
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    isUnderAttack = true;
                                    break;
                                }
                            }                            
                        }
                    }
                }
                
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (blackPiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            blackUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void ChessboardAndPiece :: attackedbyQueen()
{
    // Define a temporary board.
    string copyboard[8][8];

    // Copy the board to a temporary board.
    for  (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            copyboard[i][j] = getPiece(i,j); 
        }
    }

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            string whitePiece = copyboard[i][j];
            if ( whitePiece.find('b') != string::npos && threatened[i][j] == false )
            {
                // Check column-wise, lower side.
                for (int x = i+1; x < 8; x++)
                {   
                    // Find the first occurence of non-empty square.
                    if (copyboard[x][j] != "--")
                    {   
                        // Check if the piece is a black queen, if so, the piece is under threat.
                        if (copyboard[x][j] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check column-wise, upper side.
                for (int x = i-1; x >= 0; x--)
                {
                    if (copyboard[x][j] != "--")
                    {
                        if (copyboard[x][j] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                        
                    break;
                    }
                }

                // Check row-wise, right side.
                for (int y = j+1; y < 8; y++)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check row-wise, left side.
                for (int y = j-1; y >= 0; y--)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left upper diagonal.
                for (int x = i-1, y = j-1; x >= 0 && y >= 0; x--, y--) 
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right lower diagonal.
                for (int x = i+1, y = j+1; x < 8 && y < 8; x++, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right upper diagonal.
                for (int x = i-1, y = j+1; x >= 0 && y < 8; x--, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left lower diagonal.
                for (int x = i+1, y = j-1; x < 8 && y >= 0; x++, y--)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }   
            }

            string blackPiece = copyboard[i][j];
            if ( blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false )
            {
                // Check column-wise, lower side.
                for (int x = i+1; x < 8; x++)
                {   
                    // Find the first occurence of non-empty square.
                    if (copyboard[x][j] != "--")
                    {   
                        // Check if the piece is a white queen, if so, the piece is under threat.
                        if (copyboard[x][j] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check column-wise, upper side.
                for (int x = i-1; x >= 0; x--)
                {
                    if (copyboard[x][j] != "--")
                    {
                        if (copyboard[x][j] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                        
                    break;
                    }
                }

                // Check row-wise, right side.
                for (int y = j+1; y < 8; y++)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check row-wise, left side.
                for (int y = j-1; y >= 0 ; y--)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left upper diagonal.
                for (int x = i-1, y = j-1; x >= 0 && y >= 0; x--, y--) 
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right lower diagonal.
                for (int x = i+1, y = j+1; x < 8 && y < 8; x++, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right upper diagonal.
                for (int x = i-1, y = j+1; x >= 0 && y < 8; x--, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left lower diagonal.
                for (int x = i+1, y = j-1; x < 8 && y >= 0; x++, y--)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

            }
        }
    }
}


void ChessboardAndPiece :: countPieces(string color, string pieceNames[])
{
	string newPieceNames[6];	// Create an array to store the piece names for the specified player (black or white)
	
	// Generate the piece names for the specified player by appending the color suffix
	for (int pn = 0; pn < 6; pn++)
	{
		newPieceNames[pn] = pieceNames[pn] + color;
	    int count = 0;
	
	// Read the whole chess board and find how many pieces correspond to each type.
	// For example, at the beginning, 8 pb, 2 ab, 2 fk, 2 kb, 1 vb, and 1 sb for whites.
		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			{
		        if (getPiece(i,j) == newPieceNames[pn]) 
				{
		            count++;
		        }
		    }        
		}
		
		// Store the counts of each chess piece with a different name in the array while the color matches.
		// For example, whitePieces[0] = 8, whitePieces[1] = 2, whitePieces[2] = 2, whitePieces[3] = 1, whitePieces[4] = 1, whitePieces[5] = 1.
		if (color == "b")
			whitePieces[pn] = count;
		else if (color == "s")
			blackPieces[pn] = count;
	}
}

void ChessboardAndPiece::calculate()
{
    // Calculate the score for the white player
    for (int i = 0; i < 6; i++)
    {
        whiteScore += whitePieces[i] * pieceScores[i] + whiteUnderAttack[i] * pieceUnderAttack[i];
    }

    // Calculate the score for the black player
    for (int i = 0; i < 6; i++)
    {
        blackScore += blackPieces[i] * pieceScores[i] + blackUnderAttack[i] * pieceUnderAttack[i];
    }
    // Display the scores for both white and black players
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl << endl;
}

int main()
{
	string fileName;

    cout << "Please enter the name of the text-file: ";
    cin >> fileName;
    
    // Create an instance of the 'ChessboardAndPiece' class and pass the file name to its constructor
    ChessboardAndPiece chessGame(fileName + ".txt");
    // Analyze the chessboard for pawn attacks, knight attacks, and queen attacks
    chessGame.attackedbyPawn();
    chessGame.attackedbyKnight();
    chessGame.attackedbyQueen();
    // Count the number of each piece for both the black and white players
	chessGame.countPieces("b", chessGame.pieceNames);	// "b" represents white pieces
	chessGame.countPieces("s", chessGame.pieceNames);	// "s" represents black pieces

    // Calculate and display the final scores for both the white and black players
	cout << endl;
	chessGame.calculate();

    return 0;
}
