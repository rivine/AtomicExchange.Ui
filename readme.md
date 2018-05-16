# Jimber Atomic swap UI

## Startscreen

  - Overview of your open orders
        Coin, placed, amount, price and status information for each order.
  - Overview of your order history
        Coin, placed, amount, price and status information for each closed order.
  - Create a new order
        Button to create a new order. When you enter theis button, The "New Order" screen will appear.

![alt text](https://github.com/JimberSoftware/AtomicExchange.Ui/blob/master/moqups/startScreen.png?raw=true "Startscreen")

## New Order

In the "New Order" screen, you need to enter the form correctly :

- The amount of Coins which you want to order proceeded by the respective coin
- The source wallet where the coins are available ( )
- The price you want to pay / get for it proceeded by the respective coin
- The destination wallet where you will receive your coins 

When confirming this form, the order will be visible in the "Open orders" list.

![alt text](https://github.com/JimberSoftware/atomicSwapUI/blob/master/moqups/newOrder.png?raw=true "New order")

# Install
install Qt 5.10 or a newer version.

# Build / Run
```sh
qmake
make
./atomicExchange -platform webgl
```
# Tasks

 - Create Open order list
        - Create QML 
        - Create C++ models
 - Create Order history List
        - Create QML 
        - Create C++ models
 - Create "New order" page
    - Create QML
    - validate form
    - add new order to open order list
 - optimize UI
 - Testing with webgl
    - Browser
    - Mobile devices





