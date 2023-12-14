#include "game_position.h"

bool Position::is_correct_cell_id() const {
    return file >= 'a' && file <= 'h', rank >= 1 && rank <= 8;
}


string get_type_of_figure(char type, char color) {
    if (type == 'p' && color == 'W')
        return "white_pawn";
    if (type == 'p' && color == 'B')
        return "black_pawn";
    if (type == 'r' && color == 'W')
        return "white_rook";
    if (type == 'r' && color == 'B')
        return "black_rook";
    if (type == 'b' && color == 'W')
        return "white_bishop";
    if (type == 'b' && color == 'B')
        return "black_bishop";
    if (type == 'k' && color == 'W')
        return "white_knight";
    if (type == 'k' && color == 'B')
        return "white_knight";
    if (type == 'Q' && color == 'W')
        return "white_queen";
    if (type == 'Q' && color == 'B')
        return "black_queen";
    if (type == 'K' && color == 'W')
        return "white_king";
    if (type == 'K' && color == 'B')
        return "black_king";
    throw runtime_error("");
}

bool Game_Position::is_sell_vacant(Position &position) {
    for (Position &i: game_position)
        if (i.file == position.file && i.rank == position.rank)
            return false;

    return true;
}

void Game_Position::reading_game_position(const string &file_path) {
    char color;
    char type;
    short int rank;
    char file;
    try {
        ifstream in(file_path);
        while(in.is_open()) {
            in >> color;
            if(not in)
                break;
            in >> type >> file >> rank;
            if (not in)
                throw runtime_error("");
            string type_of_figure = get_type_of_figure(type, color);

            Position position = {file, rank, type_of_figure};
            if (!is_sell_vacant(position) || !position.is_correct_cell_id())
                throw runtime_error("");
            game_position.push_back(position);
        }
        in.close();
    }
    catch (exception &e) {
        cerr << "Something went wrong...";
        game_position.clear();
    }
}

void Game_Position::visualise_game_position(Chessboard &board) {
    for (Position &position : game_position) {
        if (position.type == "white_pawn") {
            Pawn *pw = new Pawn(board, "pieces.png", white_pawn, true);
            board.at(position.file, position.rank).attach_figure(*pw);
        }
        else if (position.type == "black_pawn") {
            Pawn *pw = new Pawn(board, "pieces.png", black_pawn, false);
            board.at(position.file, position.rank).attach_figure(*pw);
        }
        else if (position.type == "white_knight") {
            Knight kt_w{board, "pieces.png", white_knight, true};
            board.at(position.file, position.rank).attach_figure(kt_w);
        }
        else if (position.type == "black_knight") {
            Knight kt_b{board, "pieces.png", black_knight, false};
            board.at(position.file, position.rank).attach_figure(kt_b);
        }
        else if (position.type == "white_king") {
            King kg_w{board, "pieces.png", white_king, true};
            board.at(position.file, position.rank).attach_figure(kg_w);
        }
        else if (position.type == "black_king") {
            King kg_b{board, "pieces.png", black_king, false};
            board.at(position.file, position.rank).attach_figure(kg_b);
        }
        else if (position.type == "white_queen") {
            Queen qu_w{board, "pieces.png", white_queen, true};
            board.at(position.file, position.rank).attach_figure(qu_w);
        }
        else if (position.type == "black_queen") {
            Queen qu_b{board, "pieces.png", black_queen, false};
            board.at(position.file, position.rank).attach_figure(qu_b);;
        }
        else if (position.type == "white_bishop") {
            Bishop bp_w{board, "pieces.png", white_bishop, true};
            board.at(position.file, position.rank).attach_figure(bp_w);
        }
        else if (position.type == "black_bishop") {
            Bishop bp_b{board, "pieces.png", black_bishop, false};
            board.at(position.file, position.rank).attach_figure(bp_b);
        }
        else if (position.type == "white_rook") {
            Rook *rk_w = new Rook(board, "pieces.png", white_rook, true);
            board.at(position.file, position.rank).attach_figure(*rk_w);
        }
        else if (position.type == "black_rook") {
            Rook *rk_b = new Rook(board, "pieces.png", black_rook, false);
            board.at(position.file, position.rank).attach_figure(*rk_b);
        }
    }
}