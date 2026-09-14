# Bank Management System

This project is a simple console-based bank management system built to practice modular program design using Object-Oriented Programming, Login System, Bitmask-based permission design, file handling, data validation, and programming fundamentals.

> **Note**: This program uses Windows-specific console commands such as `cls` and `pause`, and Microsoft-specific `__declspec(property)` declarations, so it is intended to run on Windows with MSVC. To make it work on another operating system, replace those commands and property declarations with equivalent code for your environment.

## About

The program manages bank clients, system users, currencies, and transactions through a text-based menu. Client data is stored in Clients.txt, user data in Users.txt, currency data in Currencies.txt, transfer logs in TransferLog.txt, and login history in LoginRegister.txt. The application supports viewing, adding, deleting, updating, and finding client information, as well as performing deposits, withdrawals, transfers, balance checks, currency exchange, and user management with permission-based access.

Users must authenticate with a username and password before using the system; permissions attached to each user control which menu operations are available. A login register records successful logins, and the system locks after three failed login attempts.

## Features

- Login authentication (username/password) with per-user permission enforcement

- Permission bitmask design allowing granular access control

- Admin account with full permissions (-1) for managing users and all operations

- View the full list of bank clients

- Add new clients with account number, PIN, name, phone, and balance

- Delete existing client records

- Update client information

- Find a client by account number

- Perform deposit transactions

- Perform withdrawal transactions

- Transfer money between accounts with transfer logging

- View the total balances of all clients

- View transfer logs

- Manage users and assign permissions

- Show, add, update, delete, and find user records

- View login register (login history)

- Currency exchange: list currencies, find currency, update exchange rate, and convert between currencies

- Save and load client, user, currency, transfer log, and login register data from text files

- Simple console UI with menu navigation and validation prompts

- System lock after three failed login attempts

## Required data files

Before running the program, make sure the project folder contains a Data folder with these files (the program reads and writes them automatically, but they must exist or be created):

`Data/Clients.txt` – stores client records.

`Data/Users.txt` – stores user records and permissions.

`Data/Currencies.txt` – stores currency records.

`Data/TransferLog.txt` – stores transfer log records.

`Data/LoginRegister.txt` – stores login register records.

You can create these files as empty text files before the first run, except Users.txt which must contain at least one user with full permissions (-1) so that user management is accessible.

> **Note:** A complete `Currencies.txt` file is provided with this project for you to use. It contains a large list of countries and their currency codes, names, and exchange rates. You can use it as-is or modify it to suit your needs. The other data files (`Clients.txt`, `Users.txt`, `TransferLog.txt`, `LoginRegister.txt`) may need to be created or populated with your own data.

Example user record in `Users.txt`:

`Hilal#//#Ali#//#Hilal@Gmail.com#//#83983948#//#User1#//#33333#//#-1`

The format is:

`FirstName#//#LastName#//#Email#//#Phone#//#UserName#//#Password#//#Permissions`

Passwords are stored encrypted with a simple Caesar cipher (encryption key = 2). The `Permissions` value is an integer bitmask, and `-1` means full permissions.

## How to use

1. Ensure the Data folder contains the required text files.

2. Add at least one user with full permissions to Data/Users.txt.
   - Example: `User1#//#Hilal#//#Ali#//#Hilal@Gmail.com#//#83983948#//#33333#//#-1`

3. Run the program and log in with an existing user from Data/Users.txt.

4. After logging in, use the main menu. Options are enabled or disabled based on the logged-in user's permissions.

5. To manage users, use the Manage Users menu — only users with pManageUsers permission can access it.

6. For client management, enter the required account information.

7. For transactions, enter the account number and transaction amount.

8. For currency exchange, select the currency menu and follow the prompts.

9. Follow the on-screen prompts to confirm actions.

10. Use the menu to continue working or logout.

## How to run

### Using Visual Studio

1. Open `Bank-OOP.sln` in Visual Studio.
2. Build the solution.
3. Run the project.

## Programming topics covered

- Object-Oriented Programming: classes, inheritance, encapsulation

- Authentication (login) and password verification

- Bitmask-based permission design and permission checks

- Simple role-like admin behavior and safe user management constraints

- Logging (transfer logs, login register)

- Permission-based user management

- Structures for grouping related data

- File handling with fstream

- String parsing and record conversion

- Input validation and range checking

- Basic menu-driven console application design

- Currency conversion and exchange rate management

- C++ input/output (cin, cout, getline)

- Control flow (if, switch, loops)

- Functions and methods for modular code organization

## Code organization

The project is organized into folders:

- `main.cpp`: entry point; handles login loop and main menu invocation.

- `Core/`: business classes
  - `clsPerson.h` – base person data

  - `clsBankClient.h` – bank client and transfer logs

  - `clsUser.h` – system user and permissions

  - `clsCurrency.h` – currency data and conversion

  - `clsLoginRegister.h` – login history records

- `Libs/:` utility classes
  - `clsDate.h` – date and time utilities

  - `clsFile.h` – file read/write helpers

  - `clsInputValidate.h` – input validation helpers

  - `clsString.h` – string manipulation utilities

  - `clsUtil.h` – general utilities (encryption, number-to-text, etc.)

- `Screens/`: console UI screens
  - `clsScreen.h` – base screen with header and access checks

  - `clsMainScreen.h` – main menu

  - `Client/` – client management screens

  - `User/` – user management screens

  - `Transaction/` – deposit, withdraw, transfer, total balances, transfer log

  - `Currency/` – currency list, find, update rate, calculator

  - `Login/` – login screen, login register screen

- `Data/`: text data files

- `Global.h`: global variables (current user, system lock, encryption key)

## Data storage

Data is stored in delimited text files using #//# as the separator.

- `Clients.txt`: `FirstName#//#LastName#//#Email#//#Phone#//#AccountNumber#//#PinCode#//#Balance`

- `Users.txt`: `FirstName#//#LastName#//#Email#//#Phone#//#UserName#//#Password(encrypted)#//#Permissions`

- `Currencies.txt`: `Country#//#CurrencyCode#//#CurrencyName#//#Rate`

- `TransferLog.txt`: `DateTime#//#SrcAccountNumber#//#DestAccountNumber#//#Amount#//#SrcBalance#//#DestBalance#//#UserName`

- `LoginRegister.txt`: `DateTime#//#UserName#//#Password(encrypted)#//#Permissions`

The `Permissions` field in `Users.txt` and `LoginRegister.txt` is an integer bitmask.

## Login and Permissions

This program requires users to authenticate before using the system. User records are stored in `Users.txt`. On startup the program shows a login prompt asking for a username and password. After successful login the application enforces permission checks for each menu option. Three failed login attempts will lock the system.

Users must exist in `Users.txt` before they can login. At least one user with full permissions (-1) must be present so an administrator can manage other users. Example admin user record (as used in the provided data):

`Hilal#//#Ali#//#Hilal@Gmail.com#//#83983948#//#User1#//#33333#//#-1`

The record fields are: `FirstName#//#LastName#//#Email#//#Phone#//#UserName#//#Password#//#Permissions.`

Permissions are stored as an integer bitmask. The program defines these permission flags (values shown):

- `pListClients` (1) — Show clients list

- `pAddNewClient` (2) — Add new clients

- `pDeleteClient` (4) — Delete clients

- `pUpdateClients` (8) — Update clients

- `pFindClient` (16) — Find clients

- `pTranactions` (32) — Deposit/Withdraw/Transfer/Total balances

- `pManageUsers` (64) — Show/Add/Delete/Update/Find users

- `pLoginRegister` (128) — Show login register list

You can combine permissions by summing flag values. For example, `1 + 2 + 32 = 35` gives read, add, and transaction permissions.

The special value `-1` means full permissions (administrator). When creating or updating a user through the program, the UI asks whether to grant full permissions; if not, it interactively asks which permissions to enable and builds the bitmask accordingly.

Successful logins are recorded in `LoginRegister.txt` with the date/time, username, encrypted password, and permissions.
