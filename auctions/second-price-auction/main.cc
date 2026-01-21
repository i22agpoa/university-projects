// ------------------------------------------------------------
// Closed Bid Second Price
// Author: Adrián Aguilar Porcel
// ------------------------------------------------------------

#include <iostream>
#include <vector>
#include <iomanip> // For setprecision

using namespace std;

struct Bidder // Structure representing a bidder
{
    int id; // Bidder id
    double bid; // Bid amount
};

int main()
{
    int n;
    cout << "Number of bidders: ";
    cin >> n;

    if(n < 2)
    {
        cerr << "At least two bidders are required for a second-price auction.\n";
        return 1;
    }

    vector<Bidder> bidders(n);

    // Read bidders information
    cout << "Enter each bidder's id and bid (example: 1 4.54): \n";
    for(int i=0; i<n; i++)
    {
        cin >> bidders[i].id >> bidders[i].bid;
    }

    // Find the highest and second-highest bids
    int winnerIndex = 0;
    int secondIndex = -1;
    double maxBid = bidders[0].bid;
    double secondBid = -1.0;
    
    for(int i=1; i<n; i++)
    {
        double current = bidders[i].bid;

        if(current > maxBid)
        {
            // Update both winner and second place
            secondBid = maxBid;
            secondIndex = winnerIndex;

            maxBid = current;
            winnerIndex = i;
        }
        else if(current > secondBid)
             {
                // Update only second place
                secondBid = current;
                secondIndex = i;
             }
    }

    // In real advertising auction: winner pays (second bid + 0.01)
    const double increment = 0.01;
    double finalPrice = secondBid + increment;

    // Display results
    cout << fixed << setprecision(2); // Format to 2 decimal places

    cout << "\n === SECOND PRICE AUCTION RESULT === \n";
    cout << "Winner ID: " << bidders[winnerIndex].id << "\n";
    cout << "Winning bid: " << maxBid << "€. \n";
    cout << "Second highest bid: " << secondBid << "€. \n";
    cout << "Final price to pay: " << finalPrice << "€. \n";

    return 0;
}