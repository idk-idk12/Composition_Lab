# BankAccount

A class representing a bank account. Serves as the base class for `CheckingAccount` and `SavingsAccount`, and keeps a history of every deposit and withdrawal.

## Data Dictionary

| Attribute    | Data Type    | Description|
|--------------|--------------|------------
| `accountNumber`      | `std::string` | Account ID for the user|
| `accountHolderName`  | `std::string` | The name to have the account under
| `balance`            | `double`      | The amount of money in the account; defaults to 0.0
| `transactionHistory` | `std::vector<Transaction>` | Every deposit and withdrawal made on the account, in order

All attributes are `protected`, so `CheckingAccount` and `SavingsAccount` can access them directly.


## Methods List

| Method Signature                                            | Return Type   | Description   |
|-------------------------------------------------------------|---------------|---------------|
| `BankAccount()`                                               | (Constructor)   | Default constructor |
| `BankAccount(accountNumber, accountHolderName, balance)`      | (Constructor)   | Parameterized constructor |
| `BankAccount(other)`                                          | (Constructor)   | Copy constructor; copies the account number, holder name, and balance of another account |
| `operator=(other)`                                            | `BankAccount&`  | copy assignment; copies the account number, holder name, and balance of another account |
| `~BankAccount()`                                              | (Destructor)    | virtual destructor, so derived accounts are destroyed correctly through a `BankAccount` pointer |
| `setAccountNumberName(accountNumberName)`                     | `void`          | sets the account holder's name |
| `getAccountNumber()`                                          | `string`        | gets the account's ID number |
| `getAccountNumberName()`                                      | `string`        | gets the account holder's name |
| `getBalance()`                                                | `double`        | gets the account's balance |
| `operator+=(amount)`                                          | `BankAccount&`  | adds the amount to the balance without validation or recording a transaction |
| `operator-=(amount)`                                          | `BankAccount&`  | subtracts the amount from the balance without validation or recording a transaction |
| `operator==(other)`                                           | `bool`          | returns true if both accounts have the same account number |
| `operator<(other)`                                            | `bool`          | returns true if this account's balance is less than the other's |
| `operator>(other)`                                            | `bool`          | returns true if this account's balance is greater than the other's |
| `print()`                                                     | `void`          | (virtual) prints the account number, holder name, and balance |
| `deposit(amount)`                                             | `void`          | (virtual) deposits the given amount into the account and records the transaction; prints an error if the amount is negative |
| `withdraw(amount)`                                            | `void`          | (virtual) withdraws the given amount and records the transaction; prints an error if the amount is negative or exceeds the balance |
| `calculateInterest()`                                         | `void`          | (virtual) prints a message that interest is not supported; overridden by `SavingsAccount` |
| `printHistory()`                                              | `void`          | prints every transaction's type, amount, and timestamp |
| `addTransaction(type, amount)`                                | `void`          | records a transaction with the given type and amount, stamped with the current time |
| `getTimeStamp()`                                              | `string`        | (private) returns the current local time as "YYYY-MM-DD HH:MM:SS" |


# Transaction

A struct representing a single deposit or withdrawal. Each `BankAccount` owns a list of these in `transactionHistory`.

## Data Dictionary

| Attribute    | Data Type    | Description|
|--------------|--------------|------------
| `type`               | `std::string` | The kind of transaction, e.g. "Deposit" or "Withdraw"
| `amount`             | `double`      | The amount of money involved in the transaction
| `timestamp`          | `std::string` | When the transaction happened, as "YYYY-MM-DD HH:MM:SS"

All attributes are public. `Transaction` has no methods.


# CheckingAccount

A class representing a checking account. Inherits from `BankAccount` and charges a fee on every withdrawal.

## Data Dictionary

| Attribute    | Data Type    | Description|
|--------------|--------------|------------
| `transactionFee`     | `double`      | The fee charged on every withdrawal

Also inherits `accountNumber`, `accountHolderName`, and `balance` from `BankAccount`.


## Methods List

| Method Signature                                            | Return Type   | Description   |
|-------------------------------------------------------------|---------------|---------------|
| `CheckingAccount()`                                                           | (Constructor)   | Default constructor |
| `CheckingAccount(accountNumber, accountHolderName, balance, transactionFee)`  | (Constructor)   | Parameterized constructor |
| `~CheckingAccount()`                                                          | (Destructor)    | Destructor; overrides `BankAccount`'s virtual destructor |
| `setTransactionFee(transactionFee)`                                           | `void`          | sets the withdrawal fee; prints an error if the fee is negative |
| `getTransactionFee()`                                                         | `double`        | gets the withdrawal fee |
| `withdraw(amount)`                                                            | `void`          | overrides `BankAccount::withdraw`; withdraws the amount plus the transaction fee and records the transaction |
| `print()`                                                                     | `void`          | overrides `BankAccount::print`; prints the account type, account details, and transaction fee |

Also inherits all other public methods from `BankAccount`.


# SavingsAccount

A class representing a savings account. Inherits from `BankAccount` and earns interest on its balance.

## Data Dictionary

| Attribute    | Data Type    | Description|
|--------------|--------------|------------
| `interestRate`       | `double`      | The interest rate as a decimal between 0 and 1 (e.g. 0.05 for 5%)

Also inherits `accountNumber`, `accountHolderName`, and `balance` from `BankAccount`.


## Methods List

| Method Signature                                            | Return Type   | Description   |
|-------------------------------------------------------------|---------------|---------------|
| `SavingsAccount()`                                                            | (Constructor)   | Default constructor |
| `SavingsAccount(accountNumber, accountHolderName, balance, interestRate)`     | (Constructor)   | Parameterized constructor |
| `~SavingsAccount()`                                                           | (Destructor)    | Destructor; overrides `BankAccount`'s virtual destructor |
| `setInterestRate(interestRate)`                                               | `void`          | sets the interest rate; prints an error if the rate is not between 0 and 1 |
| `getInterestRate()`                                                           | `double`        | gets the interest rate |
| `calculateInterest()`                                                         | `void`          | overrides `BankAccount::calculateInterest`; adds interest to the balance based on the interest rate |
| `print()`                                                                     | `void`          | overrides `BankAccount::print`; prints the account type, account details, and interest rate |

Also inherits all other public methods from `BankAccount`.
