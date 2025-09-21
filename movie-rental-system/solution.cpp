// LeetCode Problem 1912 - https://leetcode.com/problems/design-movie-rental-system/description

// Read Blog - https://phaham.hashnode.dev/designing-a-movie-rental-system

#include<bits/stdc++.h>
using namespace std;

class MovieRentingSystem {
public:
    set<pair<int,pair<int,int>>>rented;
    map<int,set<pair<int,int>>>moviePrice;
    map<pair<int,int>,int>collections;
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for(auto v:entries){
            int shop = v[0];
            int movie = v[1];
            int price = v[2];
            collections[{shop,movie}] = price;
            moviePrice[movie].insert({price,shop});
        }
    }
    
    vector<int> search(int movie) {
        auto &s = moviePrice[movie];
        if(s.empty()) return {};
        vector<int>cheapest;
        for(auto it = s.begin();cheapest.size()<5 and it!=s.end();it++){
            cheapest.push_back(it->second);
        }
        return cheapest;
    }
    
    void rent(int shop, int movie) {
        int price = collections[{shop,movie}];
        moviePrice[movie].erase({price,shop});
        rented.insert({price,{shop,movie}});
    }
    
    void drop(int shop, int movie) {
        int price = collections[{shop,movie}];
        moviePrice[movie].insert({price,shop});
        rented.erase({price,{shop,movie}});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>>res;
        for(auto it = rented.begin();res.size()<5 and it!=rented.end();it++){
            res.push_back({it->second.first,it->second.second});
        }

        return res;
    }
};
