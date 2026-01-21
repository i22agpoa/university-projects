# Item-Item Recommender (Cosine Similarity) — C++

Academic project implementing an item-item collaborative filtering recommender system using cosine similarity.

## Build
g++ -std=c++17 main.cpp -o app

## Run
./app

## Description
The program computes an item-item similarity matrix from a user–item rating matrix
and predicts missing ratings using a weighted average of similar items.

Ratings use values from 1 to 5, or 0 if the item has not been rated.
