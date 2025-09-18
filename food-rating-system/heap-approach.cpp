// Approach - 1 | Heap + Lazy Deletion
// Explanation - https://gist.github.com/Phaham/93e7c96b6b29e4625a4b1de4f5dc15d5
// Read Blog - 

#include <bits/stdc++.h>
using namespace std;

class Food {
public:
    int rating;
    string foodName;
    
    Food(int r, const string& name) : rating(r), foodName(name) {}
    
    // Custom comparator for priority queue
    bool operator<(const Food& other) const {
        if (rating == other.rating) {
            return foodName > other.foodName; // Lex smaller name has priority
        }
        return rating < other.rating; // Higher rating has priority
    }
};

class FoodRatings {
private:
    unordered_map<string, int> foodRatingMap;
    unordered_map<string, string> foodCuisineMap;
    unordered_map<string, priority_queue<Food>> cuisineFoodMap;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
            foodRatingMap[foods[i]] = ratings[i];
            foodCuisineMap[foods[i]] = cuisines[i];
            cuisineFoodMap[cuisines[i]].push(Food(ratings[i], foods[i]));
        }
    }
    
    void changeRating(string food, int newRating) {
        foodRatingMap[food] = newRating;
        string cuisine = foodCuisineMap[food];
        cuisineFoodMap[cuisine].push(Food(newRating, food));
    }
    
    string highestRated(string cuisine) {
        auto& pq = cuisineFoodMap[cuisine];
        
        // Clean up outdated ratings
        while (!pq.empty()) {
            Food topFood = pq.top();
            if (foodRatingMap[topFood.foodName] != topFood.rating) {
                pq.pop();
                continue;
            }
            return topFood.foodName;
        }
        
        return "";
    }
};

// Approach - 2 | Sorted Set
// Explanation - https://gist.github.com/Phaham/70b25dfbc8e59b70bb2b4282999e23ce

#include <bits/stdc++.h>
using namespace std;

class FoodRatings {
private:
    // Struct to represent a food item
    struct Food {
        string name;
        int rating;
        string cuisine;
        
        Food(const string& n, int r, const string& c) : name(n), rating(r), cuisine(c) {}
    };
    
    // Custom comparator for the set
    struct FoodComparator {
        bool operator()(const Food& a, const Food& b) const {
            if (a.rating != b.rating) {
                return a.rating > b.rating; // Higher rating comes first
            }
            return a.name < b.name; // Lexicographically smaller name comes first
        }
    };
    
    unordered_map<string, Food> foodMap;
    unordered_map<string, set<Food, FoodComparator>> cuisineMap;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); i++) {
            Food food(foods[i], ratings[i], cuisines[i]);
            foodMap[foods[i]] = food;
            cuisineMap[cuisines[i]].insert(food);
        }
    }
    
    void changeRating(string food, int newRating) {
        Food& curr = foodMap[food];
        string cuisine = curr.cuisine;
        
        // Remove the old entry from the set
        cuisineMap[cuisine].erase(curr);
        
        // Update the rating
        curr.rating = newRating;
        
        // Insert the updated entry
        cuisineMap[cuisine].insert(curr);
    }
    
    string highestRated(string cuisine) {
        return cuisineMap[cuisine].begin()->name;
    }
};