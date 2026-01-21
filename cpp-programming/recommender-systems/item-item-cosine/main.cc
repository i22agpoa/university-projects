// ------------------------------------------------------------
// Recommender System: Item-Item 
// Author: Adrián Aguilar Porcel
// ------------------------------------------------------------

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Computes cosine similarity between two items (columns)
double cosineSimilarityItems(int itemA, int itemB,
                             const vector<vector<double>>& ratings) {
    int numUsers = ratings.size();

    double dot = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    for (int u = 0; u < numUsers; ++u) {
        double ra = ratings[u][itemA];
        double rb = ratings[u][itemB];

        // Only users who rated BOTH items (non-zero values) are considered
        if (ra != 0 && rb != 0) {
            dot   += ra * rb;
            normA += ra * ra;
            normB += rb * rb;
        }
    }

    // If no information is available, similarity is zero
    if (normA == 0.0 || normB == 0.0) {
        return 0.0;
    }

    return dot / (sqrt(normA) * sqrt(normB));
}

// Predicts the rating for (userIndex, itemIndex) using item–item CF
double predictRating(const vector<vector<double>>& ratings,
                     const vector<vector<double>>& similarity,
                     int userIndex, int itemIndex) {

    int numItems = ratings[0].size();

    double num = 0.0; // weighted sum of ratings
    double den = 0.0; // sum of absolute similarities

    for (int j = 0; j < numItems; ++j) {
        if (j == itemIndex) continue;

        double userRatingOnJ = ratings[userIndex][j];
        if (userRatingOnJ == 0) continue; // the user did not rate this item

        double sim = similarity[itemIndex][j];

        num += sim * userRatingOnJ;
        den += fabs(sim);
    }

    // If no similar items have been rated, return 0 (or could use user average)
    if (den == 0.0) {
        return 0.0;
    }

    double prediction = num / den;

    // Optional: clamp to a typical rating scale [1, 5]
    if (prediction < 1.0) prediction = 1.0;
    if (prediction > 5.0) prediction = 5.0;

    return prediction;
}

int main() {
    int numUsers, numItems;

    cout << "Item-Item Recommender\n\n";

    cout << "Enter number of users: ";
    cin >> numUsers;

    cout << "Enter number of items: ";
    cin >> numItems;

    if (numUsers <= 0 || numItems <= 0) {
        cout << "Invalid sizes.\n";
        return 0;
    }

    // Rating matrix: ratings[user][item]
    vector<vector<double>> ratings(numUsers, vector<double>(numItems, 0.0));

    cout << "\nEnter the rating matrix.\n";
    cout << "For each user, enter " << numItems << " values (1..5 or 0 if no rating).\n\n";

    for (int u = 0; u < numUsers; ++u) {
        cout << "User " << u << " ratings: ";
        for (int i = 0; i < numItems; ++i) {
            cin >> ratings[u][i];
        }
    }

    // Display the matrix
    cout << "\nRating matrix (" << numUsers << " x " << numItems << "):\n";
    for (int u = 0; u < numUsers; ++u) {
        cout << "User " << u << ": ";
        for (int i = 0; i < numItems; ++i) {
            cout << ratings[u][i] << " ";
        }
        cout << "\n";
    }

    // Compute item-item similarity matrix
    vector<vector<double>> similarity(numItems, vector<double>(numItems, 0.0));

    for (int i = 0; i < numItems; ++i) {
        similarity[i][i] = 1.0; // an item is fully similar to itself
        for (int j = i + 1; j < numItems; ++j) {
            double s = cosineSimilarityItems(i, j, ratings);
            similarity[i][j] = s;
            similarity[j][i] = s;
        }
    }

    // Display the similarity matrix
    cout << "\nItem-Item similarity matrix (cosine):\n";
    for (int i = 0; i < numItems; ++i) {
        for (int j = 0; j < numItems; ++j) {
            cout << similarity[i][j] << " ";
        }
        cout << "\n";
    }

    // User selects (uc, ic) to predict
    int uc, ic;
    cout << "\nEnter target user index uc (0.." << numUsers - 1 << "): ";
    cin >> uc;
    cout << "Enter target item index ic (0.." << numItems - 1 << "): ";
    cin >> ic;

    if (uc < 0 || uc >= numUsers || ic < 0 || ic >= numItems) {
        cout << "Invalid indices.\n";
        return 0;
    }

    if (ratings[uc][ic] != 0) {
        cout << "\nWarning: user already rated this item: " 
             << ratings[uc][ic] << "\n";
        cout << "Prediction is just for comparison.\n";
    }

    double predicted = predictRating(ratings, similarity, uc, ic);

    cout << "\nPredicted rating for user " << uc
         << " on item " << ic << " is: " << predicted << "\n";

    return 0;
}

