# Bank System Extension
This is an extension for the simple menu-driven banking system implemented in the original repository . The extension adds new features to the system, including a user subsystem for bank employees, a login screen for authentication, and a menu screen for managing users.

## Features
The extension includes the following features:

User System: The system now includes a user subsystem for bank employees. The user system provides abstraction by giving each user specific permissions on the system. This helps to create a separation of duties and improve security.  

Authentication: The system now includes a login screen for authentication. Users must enter a valid username and password to access the system. The login screen also enforces access controls based on the user's role and permissions.  

User Permissions: The user system allows the administrator to assign permissions to users based on their roles and responsibilities. The system includes a set of predefined roles, such as administrator, manager, and teller, and allows for custom roles to be created as well.  

Users File: The system now includes a users file, which is used to register users and assign permissions. The users file is read during system startup, and the information is used to authenticate users and enforce access controls.  

Manage Users Menu Screen: The system includes a new menu screen for managing users. The menu allows an administrator to perform the following user management tasks:  

List Users: Displays a list of all registered users in the system.  
Add New User: Allows an administrator to add a new user to the system.  
Delete User: Allows an administrator to delete an existing user from the system.  
Update User: Allows an administrator to update an existing user's information.  
Find User: Allows an administrator to search for a user.  

## Overall
The bank system extension provides additional functionality to the original banking system, and can be used to manage users and enforce access controls in the system. The authentication system adds an extra layer of security to the system by requiring users to enter valid credentials before accessing the system. However, the program does not include any input validation or error handling, so invalid user input or file read errors may cause the program to crash.



Main Menu: Returns the user to the main menu.
