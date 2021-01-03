package ca.cmpt213.asn4.tictactoe.game;

/**
 * TicTacToeBoard class maintains state of TicTacToe board, and contains methods for
 * placing pieces and checking for a winner.
 */

public class TicTacToeBoard {
    private int[][] boardState;
    private int pieceVal;

    public TicTacToeBoard() {
        boardState = new int[4][4];
        pieceVal = 1;
    }

    public void clearBoard() {
        boardState = new int[4][4];
        pieceVal = 1;
    }

    public void placePiece(int x, int y) {
        boardState[x][y] = pieceVal;
        if (checkWinner()) {
            if (pieceVal > 0) {
                System.out.println("X wins!");
            } else {
                System.out.println("O wins!");
            }
            return;
        }
        pieceVal = -pieceVal;
    }

    public boolean checkWinner() {
        for (int i = 0; i < boardState.length; i++) {
            int val = boardState[i][0];
            for (int j = 0; j < boardState.length; j++) {
                if (boardState[i][j] != val) {
                    break;
                }
                if (j == boardState.length-1) {
                    return true;
                }
            }
        }
        for (int j = 0; j < boardState.length; j++) {
            int val = boardState[0][j];
            for (int i = 0; i < boardState.length; i++) {
                if (boardState[i][j] != val) {
                    break;
                }
                if (i == boardState.length-1) {
                    return true;
                }
            }
        }
        return false;
    }
}
