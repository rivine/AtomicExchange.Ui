# Testplan Jimber Atomic swap

commit version tested : faa9e84 - local test 

## Sign in process

#### Empty credentials
- Login with empty username and password. => username = pw not correct
#### Wrong username
- Login with a user which is not assigned to the node. ( don't get env var local )
#### Wrong password
- Login with the valid user with a wrong password. ( wrong username / pw )
#### Special characters
- Try to login with a username/password with special characters. ( <\"% => username / pw not correct )
#### Valid credentials
- Login with a valid username and a valid password. ( text message => login )

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
- Progressbar working?
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
- Login screen centralized on schreen
- Application centralized on screen
- Username IYO on right top of screen
- Currencies next to eachother

#### Smartphone
### unable to login, keyboard not visible
- Login screen centralized on screen. ( ok )
- fixed with on the left, app fits on screen.
- Icon only on top of screen.
- Currencies below to eachother.
