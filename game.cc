#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "blindboard.h"
#include "heavyboard.h"
#include "board.h"
#include "game.h"
using namespace std;

std::string Game::readFile(std::string filename) {
    std::ifstream inFile(filename); // Open the file for reading

    if (!inFile.is_open()) { // Check if the file was opened successfully
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf(); // Read the entire file into the buffer

    std::string content = buffer.str();
    std::string validChars = "IOJLSZT"; // Valid characters
    
    for (auto it = content.begin(); it != content.end();) {
        // If the current character is not in validChars, erase it
        if (validChars.find(*it) == std::string::npos) {
            it = content.erase(it);
        } else {
            ++it;
        }
    }

    return content; 
}

bool Game::cmdInterpreter(std::unique_ptr<AbstractBoard> &cur, std::istream &in, std::unique_ptr<AbstractBoard> &op) {
    std::string LEFT = "left";
    std::string RIGHT = "right";
    std::string DOWN = "down";
    std::string DROP = "drop";
    std::string CLOCKWISE = "clockwise";
    std::string COUNTERCLOCKWISE = "counterclockwise";
    std::string LEVELUP = "levelup";
    std::string LEVELDOWN = "leveldown";
    std::string RANDOM = "random";
    std::string RESTART = "restart";
    std::string I = "I";
    std::string O = "O";
    std::string J = "J";
    std::string L = "L";
    std::string Z = "Z";
    std::string S = "S";
    std::string T = "T";
    std::string NORANDOM = "norandom";
    std::string SEQUENCE = "sequence";

    int multiplier = -1;
    int tmp;
    string tmpLen;
    string cmd;
    in >> cmd;
    std::istringstream iss{cmd};


    if (iss >> tmp) { // reads all initial int chars and sets multiplier to int
        multiplier = tmp;
        int length = cur->getLength(multiplier);
        cmd = cmd.substr(length);
    }

    if (iss.fail()) {
        iss.clear();
    } 

    int len = cmd.length();
    if (multiplier == -1) { //unchanged, set to default
        multiplier = 1;
    }


    if (len >= 3 && len <= 4 && cmd == LEFT.substr(0,len)) {
        if (!(cur->moveBlock('l', multiplier))) {
            turn1 = !turn1;
            if (cur->getScore() > hScore) {
                hScore = cur->getScore();
            }
            render(board1, board2);
            return true;
        }
    }
    else if (len >= 2 && len <= 5 && cmd == RIGHT.substr(0, len)) {
        if (!(cur->moveBlock('r', multiplier))) {
            turn1 = !turn1;
            if (cur->getScore() > hScore) {
                hScore = cur->getScore();
            }
            render(board1, board2);
            return true;
        }
    }
    else if (len >= 2 && len <= 4 && cmd == DOWN.substr(0, len)) {
        cur->moveBlock('d', multiplier);
    }
    else if (len >= 2 && len <= 9 && cmd == CLOCKWISE.substr(0, len)) {
        cur->rotateBlock("cw",multiplier);
    }
    else if (len >= 2 && len <= 16 && cmd == COUNTERCLOCKWISE.substr(0,len)) {
        cur->rotateBlock("ccw",multiplier);
    }
    else if (len >= 6 && len <= 9 && cmd == LEVELDOWN.substr(0,len)) {
        for (int i = 0; i < multiplier; i++) {
            cur->levelDown();
        }
    }
    else if (len >= 6 && len <= 7 && cmd == LEVELUP.substr(0,len)) {
        for (int i = 0; i < multiplier; i++) {
            cur->levelUp();
        }
    }
    else if (len >= 2 && len <= 4 && cmd == DROP.substr(0,len)) {
        for (int i = 0; i < multiplier; i++) {
            int result = 0;
            try {
                result = cur->drop();
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (cur->getCell(i, j) != ' ') {
                            throw -1;
                        }
                    }
                }
            } catch (int error) {
                if (error == -1) {
                    display->graphicFill(0, 27*20, 30*20, 3*20, 0);
                    std::cout << "Game Over! Player " << op->getPlayer() << " Wins!" << endl;
                    cout << "If you want to restart, enter restart" << endl;
                    display->graphicMsg(180, 28*20, "Game Over! Player " + std::to_string(op->getPlayer()) + " Wins!");
                    display->graphicMsg(180, 29*20, "If you want to restart, enter restart.");
                    std::string command;
                    in >> command;
                    int leng = command.length();
                    if (cur->getScore() > hScore) {
                        hScore = cur->getScore();
                    }
                    if (leng >= 2 && leng <= 7 && command == RESTART.substr(0,leng)) {
                        restart();
                        render(board1, board2);
                        return false;
                    } else {
                        std::cout << "Thank you for playing. Bye!" << std::endl;
                        exit(0);
                    }
                }
            }
            
            if (result >= 2) {
                render(board1, board2);
                cout << "Well done , you have triggered a speical action, please make selection" << endl;
                display->graphicMsg(180, 29*20, "Well done , you have triggered a speical action, please make selection");
                std::string choice;
                in >> choice;
                if (choice == "blind") {
                    std::unique_ptr<BlindBoard> blindBoardPtr = std::make_unique<BlindBoard>(op);
                    op = std::move(blindBoardPtr);
                } else if (choice == "heavy") {
                    std::unique_ptr<HeavyBoard> heavyBoardPtr = std::make_unique<HeavyBoard>(op);
                    op = std::move(heavyBoardPtr);
                } else if (choice == "force") {
                    char blockType;
                    in >> blockType;
                    op->deleteCur();
                    try {
                        op->changeCur(blockType);
                    } catch (int error) {
                        if (error == 0) {
                            display->graphicFill(0, 27*20, 30*20, 3*20, 0);
                            std::cout << "Game Over! Player " << cur->getPlayer() << " Wins!" << endl;
                            cout << "If you want to restart, enter restart" << endl;
                            display->graphicMsg(180, 28*20, "Game Over! Player " + std::to_string(cur->getPlayer()) + " Wins!");
                            display->graphicMsg(180, 29*20, "If you want to restart, enter restart.");
                            std::string command;
                            in >> command;
                            int leng = command.length();
                            if (cur->getScore() > hScore) {
                                hScore = cur->getScore();
                            }
                            if (leng >= 2 && leng <= 7 && command == RESTART.substr(0,leng)) {
                                restart();
                                render(board1, board2);
                                return false;
                            } else {
                                std::cout << "Thank you for playing. Bye!" << std::endl;
                                exit(0);
                            }
                        }
                    }
                }
            }
            if (result > 0 && cur->whatBoard() != 'n') {
                while (cur->whatBoard() != 'n') {
                    cur = cur->releaseInnerComponent();
                }
            }
            try {
                cur->createNext();
            } catch (int error) {
                if (error == 0) {
                    display->graphicFill(0, 27*20, 30*20, 3*20, 0);
                    std::cout << "Game Over! Player " << op->getPlayer() << " Wins!" << endl;
                    cout << "If you want to restart, enter restart" << endl;
                    display->graphicMsg(180, 28*20, "Game Over! Player " + std::to_string(op->getPlayer()) + " Wins!");
                    display->graphicMsg(180, 29*20, "If you want to restart, enter restart.");
                    std::string command;
                    in >> command;
                    int leng = command.length();
                    if (cur->getScore() > hScore) {
                        hScore = cur->getScore();
                    }
                    if (leng >= 2 && leng <= 7 && command == RESTART.substr(0,leng)) {
                        restart();
                        render(board1, board2);
                        return false;
                    } else {
                        std::cout << "Thank you for playing. Bye!" << std::endl;
                        exit(0);
                    }
                }
            }
            turn1 = !turn1;
            if (cur->getScore() > hScore) {
                hScore = cur->getScore();
            }
            render(board1, board2);
            return true;
        }
    } 
    else if (cmd == "p") {
        std::cout <<  "level: " << cur->getLev() << std::endl;
        std::cout <<  "score: " << cur->getScore() << std::endl;
        for (int i = 0; i < 18; ++i) {
            std::cout << "row: " << i;
            if(i < 10) {
                std::cout << " ";
            }
            std::cout << "|";
            for (int j = 0; j < 11; ++j) {
                std::cout << cur->getCell(i, j) << "|";
            }
            std::cout << std::endl;
            for (int j = 0; j < 30; j++) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    } else if (len >= 2 && len <= 7 && cmd == RESTART.substr(0,len)) {
        restart();
    } else if (cmd == "I" || cmd == "J" || cmd == "O" || cmd == "L" || cmd == "Z" || cmd == "S" || cmd == "T") {
        char pattern = cmd[0];
        cur->deleteCur();
        try {
            cur->changeCur(pattern);
        } catch (int error) {
            if (error == 0) {
                display->graphicFill(0, 27*20, 30*20, 3*20, 0);
                std::cout << "Game Over! Player " << op->getPlayer() << " Wins!" << endl;
                cout << "If you want to restart, enter restart" << endl;
                display->graphicMsg(180, 28*20, "Game Over! Player " + std::to_string(op->getPlayer()) + " Wins!");
                display->graphicMsg(180, 29*20, "If you want to restart, enter restart.");
                std::string command;
                in >> command;
                int leng = command.length();
                if (cur->getScore() > hScore) {
                    hScore = cur->getScore();
                }
                if (leng >= 2 && leng <= 7 && command == RESTART.substr(0,leng)) {
                    restart();
                    render(board1, board2);
                    return false;
                } else {
                    std::cout << "Thank you for playing. Bye!" << std::endl;
                    exit(0);
                    
                }
            }
        }
    }
    else if (len >= 2 && len <= 6 && cmd == RANDOM.substr(0,len)) {
        cur->random();
    }
    else if (len >= 1 && len <= 8 && cmd == NORANDOM.substr(0,len)) {
        //take next string as file name
        std::string file;
        in >> file;
        std::string content = readFile(file);
        cur->noRandom(content);
    }
    else if (len >= 1 && len <= 8 && cmd == SEQUENCE.substr(0,len)) {
        // take next string as file name
        bool curTurn = true;
        std::string file;
        in >> file;
        std::ifstream inFile(file); // Open the file for reading
        if (!inFile.is_open()) { // Check if the file was opened successfully
            return false;
        }
        while (!inFile.eof()) {
            if (curTurn) {
                if (cmdInterpreter(cur, inFile, op)) {
                    curTurn = !curTurn;
                }
                if (cur->getScore() > hScore) {
                    hScore = cur->getScore();
                }
            } else {
                if (cmdInterpreter(op, inFile, cur)) {
                    curTurn = !curTurn;
                }
                if (op->getScore() > hScore) {
                    hScore = op->getScore();
                }
            }
        }
    } else {
        //std::cout << "Invalid Command!" << std::endl;
        return false;
    }
    if (!((len >= 1 && len <= 8 && cmd == SEQUENCE.substr(0,len)))) {
        render(board1, board2);
    }
    return false;
}

Game::Game(int startlevel, bool isgraphic, int seed, std::string filename1, std::string filename2) :
    startlevel{startlevel}, isgraphic{isgraphic}, seed{seed}, turn1{true}, filename1{filename1}, filename2{filename2} {
    hScore = 0;
    try {
        file1 = readFile(filename1);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        file2 = readFile(filename2);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    srand(seed);
    board1 = make_unique<Board>(1, file1, startlevel, seed);
    board2 = make_unique<Board>(2, file2, startlevel, seed);
    display = make_unique<View>(isgraphic);
    board1->createNext();
    board2->createNext();
}

void Game::restart() {
    board1 = make_unique<Board>(1, file1, startlevel, seed);
    board2 = make_unique<Board>(2, file2, startlevel, seed);
    display = make_unique<View>(isgraphic);
    board1->createNext();
    board2->createNext();
    turn1 = true;
}

void Game::render(const unique_ptr<AbstractBoard> &p1, const unique_ptr<AbstractBoard> &p2) {
    std::cout << "highest Score Record: " << hScore << std::endl;
    //print level
    display->drawLevel(p1->getLev());
    std::cout << std::string(6,' ');
    display->drawLevel(p2->getLev());
    std::cout << std::endl;
    //print score
    display->drawScore(p1->getScore());
    std::cout << std::string(6,' ');
    display->drawScore(p2->getScore());
    std::cout << std::endl;
    //print board
    std::cout << std::string(11, '-') << std::string(6,' ') << std::string(11, '-') << std::endl;
    display->drawBoard(p1, p2);
    std::cout << std::string(11, '-') << std::string(6,' ') << std::string(11, '-') << std::endl;
    //print nextblocks
    if (turn1) {
        display->drawNext(p1);
    } else {
        display->drawNext(p2);
    }
    if (isgraphic) {
        display->graphicDisplay(p1, p2, turn1);
        display->graphicMsg(200, 30, "Highest Score Record:");
        display->graphicMsg(350, 30, std::to_string(hScore));
    }
}

void Game::startGame() {
    std::string command;
    render(board1, board2);
    while(1) {
        if (turn1) {
            std::cout << "It is player1's turn, please enter command" << std::endl;
        } else {
            std::cout << "It is player2's turn, please enter command" << std::endl;
        }
        if (cin.eof()) {
            break;
        } else {
            if (turn1) {
                cmdInterpreter(board1, cin, board2);
                if (board1->getScore() > hScore) {
                    hScore = board1->getScore();
                }
            } else {
                cmdInterpreter(board2, cin, board1);
                if (board2->getScore() > hScore) {
                    hScore = board2->getScore();
                }
            }
        }
    }
}

