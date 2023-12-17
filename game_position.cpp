#include "game_position.h"

bool Position::is_correct_cell_id() const {
    return file >= 'a' && file <= 'h' && rank >= 1 && rank <= 8;
}

bool Position::is_correct_type() const {
    return find(types_of_figure.begin(), types_of_figure.end(), type) != types_of_figure.end();
}

bool GamePosition::is_cell_vacant(Position &position) {
    for (Position &i: game_position)
        if (i.file == position.file && i.rank == position.rank)
            return false;
    return true;
}

void GamePosition::reading(const string &file_path) {
    string color;
    string type;
    short int rank;
    char file;
    try {
        ifstream in(file_path);
        while (in.is_open()) {
            in >> color;
            if (not in)
                break;
            in >> type >> file >> rank;
            if (not in)
                throw runtime_error("Read error");

            transform(color.begin(), color.end(), color.begin(), ::tolower);
            transform(type.begin(), type.end(), type.begin(), ::tolower);
            string type_of_figure = color.append("_").append(type);

            Position position = {file, rank, type_of_figure};

            if (!is_cell_vacant(position) || !position.is_correct_cell_id())
                throw runtime_error("Incorrect position of the figure");
            if (!position.is_correct_type())
                throw runtime_error("Incorrect body type");

            game_position.push_back(position);
        }
        if (not in.is_open())
            throw runtime_error("File not found");
    }
    catch (exception &e) {
        cerr << e.what();
        game_position.clear();
    }
}

void GamePosition::visualise(Chessboard &board) {
    for (Position &position: game_position) {
        if (position.type == "white_pawn") {
            auto *pw = new Pawn(board, "pieces.png", true);
            board.at(position.file, position.rank).attach_figure(*pw);
        } else if (position.type == "black_pawn") {
            auto *pw = new Pawn(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*pw);
        } else if (position.type == "white_knight") {
            auto *kt_w = new Knight(board, "pieces.png", true);
            board.at(position.file, position.rank).attach_figure(*kt_w);
        } else if (position.type == "black_knight") {
            auto *kt_b = new Knight(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*kt_b);
        } else if (position.type == "white_king") {
            auto *kg_w = new King(board, "pieces.png", true);
            board.at(position.file, position.rank).attach_figure(*kg_w);
        } else if (position.type == "black_king") {
            auto *kg_b = new King(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*kg_b);
        } else if (position.type == "white_queen") {
            auto *qu_w = new Queen{board, "pieces.png", true};
            board.at(position.file, position.rank).attach_figure(*qu_w);
        } else if (position.type == "black_queen") {
            auto *qu_b = new Queen(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*qu_b);
        } else if (position.type == "white_bishop") {
            auto *bp_w = new Bishop(board, "pieces.png", true);
            board.at(position.file, position.rank).attach_figure(*bp_w);
        } else if (position.type == "black_bishop") {
            auto *bp_b = new Bishop(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*bp_b);
        } else if (position.type == "white_rook") {
            auto *rk_w = new Rook(board, "pieces.png", true);
            board.at(position.file, position.rank).attach_figure(*rk_w);
        } else if (position.type == "black_rook") {
            auto *rk_b = new Rook(board, "pieces.png", false);
            board.at(position.file, position.rank).attach_figure(*rk_b);
        }
    }
    Text* t = new Text{Point{340,360},""};
    t->set_font_size(70);
    t->set_color(Color::invisible);

    board.check = t;
}