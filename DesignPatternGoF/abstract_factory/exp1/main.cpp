#include <iostream>

using namespace std;
enum Direction{North, South, East, West};
class MapSite {
public:
    virtual void Enter() = 0;
};

class Room : public MapSite {
public:
    Room(int roomNo);
    MapSite* GetSide(Direction) const;
    void setSide(Direction, MapSite*);
    virtual void Enter();
private:
    MapSite* _sides[4];
    int _roomNumber;
};

class Wall : public MapSite {
public:
    Wall();
    virtual void Enter();
};

class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0);
    virtual void Enter();
    Room* OtherSideFrom(Room*);
private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class Maze {
public:
    Maze();
    void AddRoom(Room*);
    Room* RoomNo(int) const;
};

class MazeFactory {
public:
    MazeFactory();
    virtual Maze* MakeMaze() const {
        return new Maze;
    }
    virtual Wall* MakeWall() const {
        return new Wall;
    }
    virtual Room* MakeRoom(int n) const {
        return new Room(n);
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const {
        return new Door(r1, r2);
    }
};

class MazeGame {
public:
    MazeGame();
    Maze* CreatMaze(MazeFactory &);
};

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}

Maze *MazeGame::CreatMaze(MazeFactory &factory)
{
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);
    Door* aDoor = factory.MakeDoor(r1, r2);
    
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    r1->setSide(North, factory.MakeWall());
    r1->setSide(East, aDoor);
    r1->setSide(South, factory.MakeWall());
    r1->setSide(West, factory.MakeWall());

    r2->setSide(North, factory.MakeWall());
    r2->setSide(East, factory.MakeWall());
    r2->setSide(South, factory.MakeWall());
    r2->setSide(West, aDoor);

    return aMaze;
}
