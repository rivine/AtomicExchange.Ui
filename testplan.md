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
### Correct credentials
- Login with a valid username and a valid password.

## New Order process


- Surf to application "A"
- Resize application "A"
- Try to login with empty username and password
- Try to login with username / pw with special chars
- Try to login with wrong username / pw
- Login with valid username / pw

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
