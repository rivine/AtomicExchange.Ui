# Testplan Jimber Atomic swap

commit version tested : 

## Sign in process

#### Empty credentials
- Login with empty username and password.
#### Wrong username
- Login with a user which is not assigned to the node.
#### Wrong password
- Login with the valid user with a wrong password.
#### Special characters
- Try to login with a username/password with special characters.
#### Valid credentials
- Login with a valid username and a valid password.

## Loading of "Currencies" information
- Balance BTC loaded?
- Balance TFT loaded?
- Sync BTC -> 100?
- Sync TFT -> 100?
#### Create BTC address
- Click button 'Create BTC address'

#### Create TFT address
- Click button 'Create TFT address'

## Confirm a new order
### Buy BTC / Sell TFT
#### Insufficient amount
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your BTC Balance.
- Enter in 'Sell' an amount of TFT.
- Press the 'Confirm Order' Button.

#### Invalid IP Address
- Enter an unvalid IP address. ( 21, ab, "!, ... )
- Enter in 'Buy' a valid amount of BTC.
- Enter in 'Sell' an amount of TFT.
- Press the 'Confirm Order' Button.

#### Wrong IP Address
- Enter a wrong but valid IP address.
- Enter in 'Buy' a valid amount of BTC.
- Enter in 'Sell' an amount of TFT.
- Press the 'Confirm Order' Button.

#### Valid values
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your BTC Balance.
- Enter in 'Sell' an amount of TFT.
- Press the 'Confirm Order' Button.

### Balances updated
- Balance BTC / TFT updated after redeem?

### Buy TFT / Sell BTC
#### Insufficient amount
- Select TFT next to 'Buy'.
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your TFT Balance.
- Enter in 'Sell' an amount of BTC.
- Press the 'Confirm Order' Button.

#### Valid values
- Enter the IP address of the peer.
- Enter in 'Buy' an amount that's higher than your TFT Balance.
- Enter in 'Sell' an amount of BTC.
- Press the 'Confirm Order' Button.

### Logging
- Checkboxes visible after sumbitting orders?
- Click show log in the menu on the right top.
- Log available?
- Log updated?

### Swap finished
- Balance BTC / TFT updated?
- Confirm button active?

### Sign out
- Click Sign out from the menu on the right top
- Fields on "login" form empty?
- Sign in
- Fields on "New Order" form empty?
- Confirm button active?

## Responsiveness
#### PC/Large screen
#### tablet
#### Smartphone

- Resize application: smartphone format => currencies under each other


- Restart application
- Progressbar working?
- Sign out
- Input fields login empty?
- Repeat these steps on a mobile device
