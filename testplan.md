# Testplan Jimber Atomic swap

commit version tested : 

## Sign in process

### Empty credentials
- Login with empty username and password.
### Wrong username
- Login with a user which is not assigned to the node.
### Wrong password
- Login with the valid user with a wrong password.
### Special characters
- Try to login with a username/password with special characters.
### Valid credentials
- Login with a valid username and a valid password.

## Confirm a new order
### Buy BTC / Sell TFT
#### Insufficient amount
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your BTC Balance.
- Enter in 'Sell' an amount of TFT.
- Press the "Confirm Order" Button.

#### Invalid IP Address
- Enter an unvalid IP address. ( 21, ab, "!, ... )
- Enter in 'Buy' a valid amount of BTC.
- Enter in 'Sell' an amount of TFT.
- Press the  "Confirm Order" Button.

#### Wrong IP Address
- Enter a wrong but valid IP address.
- Enter in 'Buy' a valid amount of BTC.
- Enter in 'Sell' an amount of TFT.
- Press the  "Confirm Order" Button.

#### Valid values
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your BTC Balance.
- Enter in 'Sell' an amount of TFT.
- Press the "Confirm Order" Button.

### Buy TFT / Sell BTC
#### Insufficient amount
- Select TFT next to 'Buy'.
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your TFT Balance.
- Enter in 'Sell' an amount of BTC.
- Press the "Confirm Order" Button.

#### Valid values
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your TFT Balance.
- Enter in 'Sell' an amount of BTC.
- Press the "Confirm Order" Button.

### Logging

## Responsiveness
- Resize application: smartphone format => currencies under each other
- Balance BTC loaded?
- Balance TFT loaded?
- Sync BTC -> 100?
- Sync TFT -> 100?
- Create BTC address
- Create TFT address
- Enter an invalid ip address
- Enter an invalid sell amount
- Enter an invalid confirm amount
- Confirm order

- Open exchange node b. 
- Change Sell -> BTC to TFT on node b
- Is buy coin changed from TFT tot BTC on node b?
- Enter a valid ip address on node a & b
- Enter a valid sell amount on node a & b
- Enter a valid buy amount on node a & b
- Confirm order

- Show log 
- Restart application
- Progressbar working?
- Flags working?
- Balance BTC updated when spap finished?
- Balance TFT updated when swap finished?

- Sign out
- Input fields login empty?
- Repeat these steps on a mobile device
