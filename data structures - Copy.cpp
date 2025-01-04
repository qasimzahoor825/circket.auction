#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Player {
public:
    string name;
    int basePrice;
    int currentBid;
    string teamName;

    Player(string name, int basePrice)
        : name(name), basePrice(basePrice), currentBid(0), teamName("None") {}
};

class Team {
public:
    string name;
    int budget;
    vector<Player> squad;

    Team(string name, int budget) : name(name), budget(budget) {}

    bool placeBid(Player& player, int bid) {
        if (budget >= bid) {
            budget -= bid;
            player.currentBid = bid;
            player.teamName = name;
            squad.push_back(player);
            return true;
        }
        return false;
    }
};

struct BSTNode {
    Player player;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Player p) : player(p), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    void insert(const Player& player) {
        root = insertRec(root, player);
    }

    void display() const {
        displayInOrder(root);
    }

private:
    BSTNode* insertRec(BSTNode* node, const Player& player) {
        if (node == nullptr) return new BSTNode(player);
        if (player.currentBid < node->player.currentBid)
            node->left = insertRec(node->left, player);
        else
            node->right = insertRec(node->right, player);
        return node;
    }

    void displayInOrder(BSTNode* node) const {
        if (node == nullptr) return;
        displayInOrder(node->left);
        cout << "Player: " << node->player.name << ", Bid: " << node->player.currentBid
            << ", Team: " << node->player.teamName << endl;
        displayInOrder(node->right);
    }
};

class Auction {
public:
    queue<Player> playerQueue;
    vector<Team> teams;
    vector<Player> unsoldPlayers;
    BST bst;

    void addPlayer(const string& name, int basePrice) {
        if (playerExists(name)) {
            cout << "Player with this name already exists. Skipping.\n";
            return;
        }
        playerQueue.push(Player(name, basePrice));
    }

    void addTeam(const string& name, int budget) {
        if (teamExists(name)) {
            cout << "Team with this name already exists. Skipping.\n";
            return;
        }
        teams.push_back(Team(name, budget));
    }

    void startAuction() {
        while (!playerQueue.empty()) {
            Player current = pla
