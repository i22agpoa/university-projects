# Second Price Auction (Vickrey) — C++

Academic implementation of a **closed-bid second price auction**, a mechanism widely used
in online advertising and e-commerce platforms.

---

## Build

```bash
g++ main.cpp -o app
```

## Run
```bash
./app
```

## Description
The program receives a set of bidders and their bids, determines the highest and
second-highest bids, and assigns the winner according to the second price auction rule.

The winner pays the second-highest bid plus a small increment, ensuring truthful bidding.
