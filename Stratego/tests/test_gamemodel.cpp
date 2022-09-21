#include <catch.h>
#include <board.h>

TEST_CASE("Moving")
{

    Board board {};

    SECTION("Moving scout by more than one case - with obstacle") {
        Position initialPos{1, 1}, obstacle{6, 1}, nextPos{9, 1};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        board.addPiece(Piece(Pieces::EAU, -1, true), obstacle);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving scout by more than one case DOWN - without obstacle") {
        Position initialPos{1, 1}, nextPos{5, 1};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving scout by more than one case UP - without obstacle") {
        Position initialPos{5, 1}, nextPos{1, 1};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving scout by more than one case RIGHT - without obstacle") {
        Position initialPos{1, 1}, nextPos{1, 5};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving scout by more than one case LEFT - without obstacle") {
        Position initialPos{1, 5}, nextPos{1, 1};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving by more than one case") {
        Position initialPos{1, 1}, nextPos{3, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving a flag") {
        Position initialPos{1, 1}, nextPos{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving a bomb") {
        Position initialPos{1, 1}, nextPos{1, 2};
        board.addPiece(Piece(Pieces::BOMBE, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving a bomb by more than 1 case") {
        Position initialPos{1, 1}, nextPos{1, 3};
        board.addPiece(Piece(Pieces::BOMBE, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving a flag by more than by 1 case") {
        Position initialPos{1, 1}, nextPos{1, 3};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving outside the board - cols") {
        Position initialPos{1, 1}, nextPos{1, 11};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving outside the board - rows") {
        Position initialPos{1, 1}, nextPos{11, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving piece directly on water" ) {
        Position initialPos{1, 1}, water{2, 1};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), initialPos);
        board.addPiece(Piece(Pieces::EAU, -1, true), water);
        REQUIRE_THROWS(board.move(initialPos, water, 0));
    }
    SECTION("Moving piece by one case DOWN - without obstacle") {
        Position initialPos{1, 1}, nextPos{1, 2};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving piece by one case UP - without obstacle") {
        Position initialPos{1, 2}, nextPos{1, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving piece by one case RIGHT - without obstacle") {
        Position initialPos{1, 1}, nextPos{2, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Moving piece by one case LEFT - without obstacle") {
        Position initialPos{2, 1}, nextPos{1, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
    }
    SECTION("Move and check if previous position empty") {
        Position initialPos{1, 1}, nextPos{2, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE(board.move(initialPos, nextPos, 0));
        REQUIRE(!board.isPiece(initialPos));
    }
    SECTION("Moving piece on its own position") {
        Position initialPos{1, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), initialPos);
        REQUIRE_THROWS(board.move(initialPos, initialPos, 0));
    }
//    SECTION("Moving back and forth 4 times"){
//        Position initialPos{1,1}, nextPos{1,2};
//        board.addPiece(Piece(Pieces::GENERAL,0),initialPos);
//        REQUIRE(board.move(initialPos, nextPos, 0));
//        REQUIRE(board.move(nextPos, initialPos, 0));
//        REQUIRE(board.move(initialPos, nextPos, 0));
//        REQUIRE_FALSE(board.move(nextPos, initialPos, 0));
//    }
}

TEST_CASE("Fight")
{
    Board board{};

    SECTION("Fight between enemy pieces of the same value - check both empty") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(!board.isPiece(pos0));
        REQUIRE(!board.isPiece(pos1));
    }
    SECTION("Weak attacking strong - check empty") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::COLONEL, 0), pos0);
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Strong attacking weak downwards - check empty") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::COLONEL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Strong attacking weak upwards - check empty") {
        Position pos0{1, 2}, pos1{1, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::COLONEL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Strong attacking weak to the left - check empty") {
        Position pos0{2, 1}, pos1{1, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::COLONEL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Strong attacking weak to the right - check empty") {
        Position pos0{1, 1}, pos1{2, 1};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::COLONEL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Demineur attacking bomb - check empty") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::DEMINEUR, 0), pos0);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::DEMINEUR);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Non-Demineur attacking bomb - check empty") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::BOMBE);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Scout attacking weaker from the distance") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), pos0);
        board.addPiece(Piece(Pieces::ESPIONNE, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::ECLAIREUR);
        REQUIRE(!board.isPiece(pos0));
    }
    SECTION("Scout attacking stronger from the distance") {
        Position pos0{1, 1}, pos1{1, 2};
        board.addPiece(Piece(Pieces::ECLAIREUR, 0), pos0);
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1);
        REQUIRE(board.move(pos0, pos1, 0));
        REQUIRE(board.at(pos1)->getName() == Pieces::GENERAL);
        REQUIRE(!board.isPiece(pos0));
    }
}
TEST_CASE("isGameOver")
{

    Board board{};

    SECTION("One flag for each player - game not over") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1b);
        REQUIRE_FALSE(board.isGameOver());
    }
    SECTION("No flags for one player - game is over") {
        //player 0
        Position pos0{1, 1};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0);
        //player 1
        Position pos1{9, 1};
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1);
        REQUIRE(board.isGameOver());
    }
    SECTION("One player has no flags and can't move - game over") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.isGameOver());
    }
    // todo
    SECTION("One flag for each player but one can't move - game over") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.isGameOver());
    }
    SECTION("One flag for each player but both can't move - game over") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::BOMBE, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.isGameOver());
    }
}
TEST_CASE("getWinner")
{
    Board board{};

    SECTION("Player 0 wins, 1 flag remaining") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.getWinner() == 0);
    }

    SECTION("Player 1 wins,1 flag remaining") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.getWinner() == 1);
    }

    SECTION("Player 0 wins, Player 1 can't move") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::GENERAL, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.getWinner() == 0);
    }
    SECTION("Player 1 wins, Player 0 can't move") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::BOMBE, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::GENERAL, 1), pos1b);
        REQUIRE(board.getWinner() == 1);
    }
    SECTION("Game tied") {
        //player 0
        Position pos0a{1, 1}, pos0b{1, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 0), pos0a);
        board.addPiece(Piece(Pieces::BOMBE, 0), pos0b);
        //player 1
        Position pos1a{9, 1}, pos1b{9, 2};
        board.addPiece(Piece(Pieces::DRAPEAU, 1), pos1a);
        board.addPiece(Piece(Pieces::BOMBE, 1), pos1b);
        REQUIRE(board.getWinner() == -1);
    }
}
